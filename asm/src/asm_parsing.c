/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 18:53:48 by tvisenti          #+#    #+#             */
/*   Updated: 2016/07/13 15:50:02 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** Check si il y a un label et si celui-ci et le label_char sont bien formatés
*/

int			asm_check_label(char *str)
{
	int	i;
	int	space;
	int	label;

	i = ft_strlen(str);
	label = ft_strclen(str, LABEL_CHAR);
	space = ft_strclen(str, ' ');
	if (label + 1 != space && i != space)
		return (0);
	i = 0;
	if (str[label] != LABEL_CHAR)
		return(asm_error(4));
	while (str[i] && str[i] != '\n' && str[i] != LABEL_CHAR)
	{
		if (ft_strchr(LABEL_CHARS, str[i]) == NULL)
			return(asm_error(3));
		i++;
	}
	if (str[i] == LABEL_CHAR && i > 0)
		return (1);
	return (0);
}

/*
** Verifie les instructions
*/

int		asm_check_instruct(char *line)
{
	char	**tab;

	if (ft_strchr(line, '\t'))
		tab = ft_strsplit(line, '\t');
	else
		tab = ft_strsplit(line, ' ');
	if (tab[0])
		asm_check_label(tab[0]);
	return (1);
}

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
	}
	else if (ft_strncmp(COMMENT_CMD_STRING, line, last) == 0)
	{
		first = last + 2;
		last = ft_strlen(line) - first - 1;
		ft_strcpy(head->comment, ft_strsub(line, first, last));
	}
	if (g_line == 1 && !head->prog_name[0])
		return (asm_error(1));
	if (g_line > 1 && !head->comment[0])
		return (asm_error(2));
	return (1);
}

/*
** Récupére le nom et le comment et le stocke dans la struct(header)
*/

int		asm_handler_name_comment(int fd, char *line, t_header *head)
{
	int	first;
	int	last;

	while (get_next_line(fd, &line) > 0 && line[0] != '\0' &&
	line[0] != '\n')
	{
		g_line++;
		ft_printf("%s\n", line);
		first = ft_strlen(NAME_CMD_STRING);
		last = ft_strlen(COMMENT_CMD_STRING);
		if (asm_copy_name_comment(line, head, first, last) == 0)
			return (0);
	}
	return (1);
}

int		asm_parsing(char *champion, t_header *head)
{
	int fd;
	char *line;

	line = NULL;
	if ((fd = open(champion, O_RDONLY, 0555)) == -1)
		return (-1);
	if (asm_handler_name_comment(fd, line, head) == 0)
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		g_line++;
		ft_printf("%s\n", line);
		asm_check_instruct(line);
		free(line);
	}
	return (0);
}
