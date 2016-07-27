/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_copy_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 10:20:25 by tvisenti          #+#    #+#             */
/*   Updated: 2016/07/27 10:28:40 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** Récupére le nom et le comment et le stocke dans la struct(header)
*/

int		asm_copy_name_comment(char *line, t_header *head, int name, int com)
{
	char	*tmp;

	tmp = NULL;
	if (!head->prog_name[0] && ft_strncmp(NAME_CMD_STRING, line, name) == 0)
	{
		if ((line = asm_header_pass(line, name, com, 1)) == NULL)
			return (asm_error(1));
		tmp = ft_strsub(line, 0, ft_strclen(line, '"'));
		ft_strncpy(head->prog_name, tmp, PROG_NAME_LENGTH);
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
			free(line);
			if (head->comment[0] && head->prog_name[0])
				return (1);
		}
	}
	return (asm_error(11));
}
