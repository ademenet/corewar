/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 18:53:48 by tvisenti          #+#    #+#             */
/*   Updated: 2016/07/22 16:36:48 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** Bouge le pointeur juste avant le nom ou le commentaire
*/

char	*asm_header_pass(char *line, int name, int com, int one)
{
	int	i;

	i = -1;
	if (one)
		while (++i < name)
			line++;
	else
		while (++i < com)
			line++;
	while (*line != '\n' && *line != '"' && *line != '\0')
		line++;
	if (*line != '"')
		return (NULL);
	line++;
	return (line);
}

/*
** Récupére le nom et le comment et le stocke dans la struct(header)
*/

int		asm_copy_name_comment(char *line, t_header *head, int name, int com)
{
	if (!head->prog_name[0] && ft_strncmp(NAME_CMD_STRING, line, name) == 0)
	{
		if ((line = asm_header_pass(line, name, com, 1)) == NULL)
			return (asm_error(1));
		ft_strncpy(head->prog_name, ft_strsub(line, 0, ft_strclen(line, '"')),
		PROG_NAME_LENGTH);
	}
	else if (!head->comment[0] &&
		ft_strncmp(COMMENT_CMD_STRING, line, com) == 0)
	{
		if ((line = asm_header_pass(line, name, com, 0)) == NULL)
			return (asm_error(11));
		else if (line[0] == '"')
			ft_strcpy(head->comment, "I don't need a comment to crush you");
		else
			ft_strncpy(head->comment, ft_strsub(line, 0, ft_strclen(line, '"')),
			COMMENT_LENGTH);
	}
	else
		return (asm_error(11));
	line = line + ft_strclen(line, '"');
	while (*line && *line != '\n' && line++)
		if (*line && *line != ' ' && *line != '\t')
			return (asm_error(1));
	return (0);
}

/*
** Récupére le nom et le comment et le stocke dans la struct(header)
*/

int		asm_handler_name_comment(int fd, char *line, t_header *head)
{
	int	name;
	int	com;

	name = 0;
	com = 0;
	while (get_next_line(fd, &line) > 0)
	{
		g_line++;
		if (line[0] != COMMENT_CHAR && line[0] != '\0')
		{
			while ((*line == ' ' || *line == '\t') && *line != '\0')
				line++;
			name = ft_strlen(NAME_CMD_STRING);
			com = ft_strlen(COMMENT_CMD_STRING);
			asm_copy_name_comment(line, head, name, com);
			free (line);
			if (head->comment[0] && head->prog_name[0])
				return (1);
		}
	}
	return (asm_error(11));
}

/*
** Récursive qui récupere le nom du label, position dans une liste chainée
*/

t_label	*asm_parse_line(char *line, int fd, int check)
{
	t_label	*new;
	int		ret;

	ret = 1;
	new = NULL;
	if (check == 1 && (ret = get_next_line(fd, &line)) && g_line++)
		asm_free_join(&line);
	if (ret > 0 && line[0] != COMMENT_CHAR && asm_check_label(line) >= 1)
	{
		new = asm_label_init();
		new->name = ft_strsub(line, 0, ft_strclen(line, LABEL_CHAR));
		new->pos = g_pos;
		if (asm_check_label(line) == 1)
			new->next = asm_parse_line(line, fd, 1);
		else
			new->next = asm_parse_line(line +
				ft_strclen(line, LABEL_CHAR) + 1, fd, 0);
	}
	else if (ret && line[0] != COMMENT_CHAR && line[0] != '\0' &&
	asm_check_label(line) == 0 && check_valid_line(line))
		return (asm_parse_line(line, fd, 1));
	else if (ret > 0)
		return (asm_parse_line(line, fd, 1));
	return (new);
}

/*
** Début du parsing
*/

int		asm_parsing(char *champion, t_header *head)
{
	int			fd;
	int			pos;
	char		*line;
	t_label		*label;

	pos = 0;
	line = NULL;
	if ((fd = open(champion, O_RDONLY, 0555)) == -1)
		return (-1);
	asm_handler_name_comment(fd, line, head);
	label = asm_parse_line(line, fd, 1);
	asm_check_double_label(label);
	if (asm_check_label_exist(label, g_file) == 0)
		return (asm_error(12));
	asm_reader(label, head, champion);
	return (0);
}
