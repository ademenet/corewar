/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 18:53:48 by tvisenti          #+#    #+#             */
/*   Updated: 2016/08/01 18:19:40 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

char		*asm_put_line_in_file(char *line, int i, char *file)
{
	while (line[i] == '\t' || line[i] == ' ')
		i++;
	if (line[i] && line[i] != COMMENT_CHAR && line[i] != ';' &&
	check_valid_line(&line[i]))
		file = asm_free_join(&line[i], file);
	free(line);
	line = NULL;
	return (file);
}

/*
** Récursive qui récupere le nom du label, position dans une liste chainée
*/

t_label		*asm_parse_line(int fd, char **file)
{
	t_label	*label;
	char	*line;
	int		i;

	label = NULL;
	line = NULL;
	while (!(i = 0) && get_next_line(fd, &line) > 0)
	{
		g_line++;
		while (line[i] == '\t' || line[i] == ' ')
			i++;
		if (line[i] && line[i] != COMMENT_CHAR && line[i] != ';' &&
		asm_check_label(line) >= 1)
		{
			label = asm_label_init(label, line);
			while (line[i] != LABEL_CHAR)
				i++;
			i++;
		}
		*file = asm_put_line_in_file(line, i, *file);
	}
	free(line);
	return (label);
}

/*
** Début du parsing
*/

int			asm_parsing(char *champion, t_header *head)
{
	int			fd;
	int			pos;
	char		*file;
	t_label		*label;

	pos = 0;
	label = NULL;
	file = NULL;
	if ((fd = open(champion, O_RDONLY, 0555)) == -1)
		return (-1);
	asm_handler_name_comment(fd, head);
	label = asm_parse_line(fd, &file);
	asm_check_double_label(label);
	if (asm_check_label_exist(label, file) == 0)
		return (asm_error(12));
	asm_reader(label, head, champion, file);
	if (file && file[0])
		free(file);
	if (label)
		asm_free_label(label);
	return (0);
}
