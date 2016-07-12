/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 18:53:48 by tvisenti          #+#    #+#             */
/*   Updated: 2016/07/12 19:01:07 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

// int		asm_check_instruct(char *line)
// {
//
// }

/*
** Récupére le nom et le comment et le stocke dans la struct(header)
*/

int		asm_name_comment(char *line, t_header *head)
{
	int	first;
	int	last;

	first = ft_strlen(NAME_CMD_STRING);
	last = ft_strlen(COMMENT_CMD_STRING);
	if (ft_strncmp(NAME_CMD_STRING, line, first) == 0)
	{
		if (first != ft_strclen(line, ' '))
			return (0);
		first = first + 2;
		last = ft_strlen(line) - first - 1;
		ft_strcpy(head->prog_name, ft_strsub(line, first, last));
	}
	else if (ft_strncmp(COMMENT_CMD_STRING, line, last) == 0)
	{
		if (last != ft_strclen(line, ' '))
			return (0);
		first = last + 2;
		last = ft_strlen(line) - first - 1;
		ft_strcpy(head->comment, ft_strsub(line, first, last));
	}
	else
		return (0);
	return (1);
}

int		asm_parsing(char *champion, t_header *head)
{
	int fd;
	char *line;

	line = NULL;
	if ((fd = open(champion, O_RDONLY, 0555)) == -1)
		return (-1);
	while (get_next_line(fd, &line) > 0)
	{
		ft_printf("%s\n", line);
		if (line[0] == '.')
		{
		 if (asm_name_comment(line, head) == 0)
		 	printf("Wrong name or comment\n");
		}
		// else if (line[0] != '\n')
		// 	asm_check_instruct(line);
		free(line);
	}
	ft_printf("name : %s\n", head->prog_name);
	ft_printf("comment : %s\n", head->comment);
	return (0);
}
