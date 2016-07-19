/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 18:53:48 by tvisenti          #+#    #+#             */
/*   Updated: 2016/07/19 15:18:04 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** Récupére le nom et le comment et le stocke dans la struct(header)
*/

int		asm_copy_name_comment(char *line, t_header *head, int name, int com)
{
	int	i;

	i = -1;
	if (ft_strncmp(NAME_CMD_STRING, line, name) == 0)
	{
		while (++i < name)
			line++;
		line = line + 2;
		ft_strcpy(head->prog_name, ft_strsub(line, 0, ft_strclen(line, '"')));
		i = ft_strlen(head->prog_name) - 1;
	}
	else if (ft_strncmp(COMMENT_CMD_STRING, line, com) == 0)
	{
		while (++i < com)
			line++;
		line = line + 2;
		ft_strcpy(head->comment, ft_strsub(line, 0, ft_strclen(line, '"')));
		i = ft_strlen(head->comment) - 1;
	}
	if (head->comment[0] && head->prog_name[0])
		return (1);
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
			name = ft_strlen(NAME_CMD_STRING);
			com = ft_strlen(COMMENT_CMD_STRING);
			if (asm_copy_name_comment(line, head, name, com) == 1)
				return (1);
		}
	}
	return (0);
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
		asm_free_join(line);
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
**
*/

int		asm_match_label(t_label *label, char *str)
{
	int len;

	len = 0;
	while (label)
	{
		while (str[len] && str[len] != ' ' && str[len] != '\t' &&
		str[len] != '\n' && str[len] != SEPARATOR_CHAR)
			len++;
		if (ft_strncmp(label->name, str, len) == 0)
			return (1);
		label = label->next;
	}
	return (asm_error(10));
}

/*
** Check si le label existe bien dans la struct(header)
*/

int		asm_check_label_exist(t_label *label, char *str)
{
	while (*str != DIRECT_CHAR && *str != '\0')
	{
		str++;
		if (*str == '%')
		{
			str++;
			if (*str == LABEL_CHAR)
			{
				str++;
				asm_match_label(label, str);
			}
		}
	}
	label = NULL;
	return (1);
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
	if (asm_handler_name_comment(fd, line, head) == 0)
		return (0);
	label = asm_parse_line(line, fd, 1);
	asm_check_double_label(label);
	asm_check_label_exist(label, g_file);
	asm_reader(label, head, champion);
	printf("-----NAME : -%s-\n", head->prog_name);
	printf("-----COMMENT : -%s-\n", head->comment);
	return (0);
}

/*
** 	while (label)
** 	{
** 		printf("Label : -%s-\t", label->name);
** 		printf("Position : |%d|\n", label->pos);
** 		label = label->next;
** 	}
** 	printf("G_file : \n%sEND", g_file);
** 	printf("Name : |%s|\n", head->prog_name);
** 	printf("Comment : |%s|\n", head->comment);
*/
