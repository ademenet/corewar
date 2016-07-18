/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 18:53:48 by tvisenti          #+#    #+#             */
/*   Updated: 2016/07/18 17:05:27 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** Récupére le nom et le comment et le stocke dans la struct(header)
*/

int		asm_copy_name_comment(char *line, t_header *head, int first, int last)
{
	if (ft_strncmp(NAME_CMD_STRING, line, first) == 0)
	{
		first = first + 2;
		last = ft_strlen(line) - first - 1;
		ft_strcpy(head->prog_name, ft_strsub(line, first, last));
		head->prog_name[PROG_NAME_LENGTH] = '\0';
	}
	else if (ft_strncmp(COMMENT_CMD_STRING, line, last) == 0)
	{
		first = last + 2;
		last = ft_strlen(line) - first - 1;
		ft_strcpy(head->comment, ft_strsub(line, first, last));
		head->comment[COMMENT_LENGTH] = '\0';
	}
	return (1);
}

/*
** Récupére le nom et le comment et le stocke dans la struct(header)
*/

int		asm_handler_name_comment(int fd, char *line, t_header *head)
{
	int	first;
	int	last;

	first = 0;
	last = 0;
	while (get_next_line(fd, &line) > 0)
	{
		g_line++;
		if (line[0] != COMMENT_CHAR && line[0] != '\0')
		{
			first = ft_strlen(NAME_CMD_STRING);
			last = ft_strlen(COMMENT_CMD_STRING);
			asm_copy_name_comment(line, head, first, last);
			if (head->comment[0] && head->prog_name[0])
				return (1);
		}
	}
	return (0);
}

/*
** Incrémente line selon l'instruction passé
*/

int		check_valid_line(char *line)
{
	int fct;

	fct = asm_instruct_name(&line);
	g_pos++;
	if (fct == 1 || fct == 9 || fct == 12 || fct == 14)
		line = line + 4;
	else if (fct == 2 || fct == 3 || fct == 7)
		line = line + 2;
	else if (fct == 15)
		line = line + 5;
	else
		line = line + 3;
	if (!asm_check_arg(line, fct))
		return(asm_error(8));
	line = NULL;
	return (1);
}

/*
** Récursive qui récupere le nom du label, position dans une liste chainée
*/

t_label		*asm_parse_line(char *line, int fd, int check)
{
	t_label		*new;
	int 		ret;

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
** Début du parsing
*/

int			asm_parsing(char *champion, t_header *head)
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
	// Verification de l'enregistrement des labels
	// while (label)
	// {
	// 	printf("Label : -%s-\t", label->name);
	// 	printf("Position : |%d|\n", label->pos);
	// 	label = label->next;
	// }
	// printf("G_file : \n%sEND", g_file);
	// Verification de l'enregistrement du nom et comment
	// printf("Name : |%s|\n", head->prog_name);
	// printf("Comment : |%s|\n", head->comment);
	return (0);
}
