/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 18:53:48 by tvisenti          #+#    #+#             */
/*   Updated: 2016/07/26 14:32:02 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** Bouge le pointeur juste avant le nom ou le commentaire
*/

char		*asm_header_pass(char *line, int name, int com, int one)
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

t_label		*asm_put_label(t_label *new, char *line, int fd, char *file)
{
	new = asm_label_init();
	new->name = ft_strsub(line, 0, ft_strclen(line, LABEL_CHAR));
	new->pos = g_pos;
	if (asm_check_label(line) == 1)
		new->next = asm_parse_line(line, fd, 1, file);
	else
		new->next = asm_parse_line(line +
			ft_strclen(line, LABEL_CHAR) + 1, fd, 0, file);
	return (new);
}

/*
** Récursive qui récupere le nom du label, position dans une liste chainée
*/

t_label		*asm_parse_line(char *line, int fd, int check, char *file)
{
	t_label	*new;
	int		r;

	r = 1;
	new = NULL;
	if (g_tmp_line)
		free(g_tmp_line);
	g_tmp_line = NULL;
	if (check == 1 && (r = get_next_line(fd, &line)) && g_line++ &&
	(g_tmp_line = line))
		file = asm_free_join(line, file);
	if (r > 0 && line && line[0] != COMMENT_CHAR && asm_check_label(line) >= 1)
		new = asm_put_label(new, line, fd, file);
	else if (r && line[0] != COMMENT_CHAR && line[0] != '\0' &&
	asm_check_label(line) == 0 && check_valid_line(line))
		return (asm_parse_line(line, fd, 1, file));
	else if (r > 0)
		return (asm_parse_line(line, fd, 1, file));
	else if (get_next_line(fd, &line) == 0)
	{
		g_file = ft_strdup(file);
		free(file);
	}
	return (new);
}

/*
** Début du parsing
*/

int			asm_parsing(char *champion, t_header *head)
{
	int			fd;
	int			pos;
	char		*line;
	char		*file;
	t_label		*label;

	pos = 0;
	line = NULL;
	file = NULL;
	if ((fd = open(champion, O_RDONLY, 0555)) == -1)
		return (-1);
	asm_handler_name_comment(fd, line, head);
	label = asm_parse_line(line, fd, 1, file);
	g_tmp_file = g_file;
	asm_check_double_label(label);
	if (asm_check_label_exist(label, g_file) == 0)
		return (asm_error(12));
	asm_reader(label, head, champion);
	free(g_tmp_file);
	return (0);
}
