/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 18:53:48 by tvisenti          #+#    #+#             */
/*   Updated: 2016/07/11 19:21:16 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

int		asm_name_comment(char *line, t_header *head)
{
	if (ft_strcmp(".name", line) == 0)
		head->prog_name = ft_strdup(line);
	else if (ft_strcmp(".comment", line) == 0)
		head->comment = ft_strdup(line);
	return (0);
}

int		asm_parsing(char *line, t_header *head)
{
	while (get_next_line(0, &line) > 0)
	{
		if (line[0] == '.')
			asm_name_comment(line, head);
		// free(line);
	}
	return (0);
}
