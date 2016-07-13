/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 18:53:48 by tvisenti          #+#    #+#             */
/*   Updated: 2016/07/13 19:26:11 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** Check si il y a un label et si celui-ci et le label_char sont bien formatés
*/

int			asm_check_label(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_strchr(LABEL_CHARS, str[i]))
		i++;
	if (str[i] == LABEL_CHAR && i > 0)
		return (1);
	else if (str[i] && str[i] != ' ' && str[i] != '\0' && str[i] != '\n')
	{
		if (str[i + 1] == ' ' || str[i + 1] == '\n' || str[i + 1] == '\0')
			return(asm_error(4));
		return(asm_error(3));
	}
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
	{
		if (asm_check_label(tab[0]) == 0)
		{
			printf("GO INSTRUCT\n");
			// asm_check_instruct()
		}
	}
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
		head->prog_name[PROG_NAME_LENGTH] = '\0';
	}
	else if (ft_strncmp(COMMENT_CMD_STRING, line, last) == 0)
	{
		first = last + 2;
		last = ft_strlen(line) - first - 1;
		ft_strcpy(head->comment, ft_strsub(line, first, last));
		head->comment[COMMENT_LENGTH] = '\0';
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
		if (line[0] != COMMENT_CHAR)
			asm_check_instruct(line);
		free(line);
	}
	return (0);
}
