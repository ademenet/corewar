/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_instruct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 13:05:23 by tvisenti          #+#    #+#             */
/*   Updated: 2016/07/19 18:35:18 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** Verifie si le nom de l'instruction est correct et retourne
** l'int correspondant
*/

int			asm_instruct_name_sec(char **line)
{
	if (ft_strncmp("ldi", *line, 3) == 0 && ++g_pos)
		return (10);
	if (ft_strncmp("ld", *line, 2) == 0 && ++g_pos)
		return (2);
	if (ft_strncmp("fork", *line, 4) == 0)
		return (12);
	if (ft_strncmp("st", *line, 2) == 0 && ++g_pos)
		return (3);
	if (ft_strncmp("lldi", *line, 4) == 0 && ++g_pos)
		return (14);
	if (ft_strncmp("lld", *line, 3) == 0 && ++g_pos)
		return (13);
	if (ft_strncmp("lfork", *line, 5) == 0)
		return (15);
	if (ft_strncmp("aff", *line, 3) == 0 && ++g_pos)
		return (16);
	return (0);
}

int			asm_instruct_name(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (ft_strncmp("live", *line, 4) == 0)
		return (1);
	if (ft_strncmp("add", *line, 3) == 0 && ++g_pos)
		return (4);
	if (ft_strncmp("sub", *line, 3) == 0 && ++g_pos)
		return (5);
	if (ft_strncmp("and", *line, 3) == 0 && ++g_pos)
		return (6);
	if (ft_strncmp("or", *line, 2) == 0 && ++g_pos)
		return (7);
	if (ft_strncmp("xor", *line, 3) == 0 && ++g_pos)
		return (8);
	if (ft_strncmp("zjmp", *line, 4) == 0)
		return (9);
	if (ft_strncmp("sti", *line, 3) == 0 && ++g_pos)
		return (11);
	return (asm_instruct_name_sec(line));
}

/*
** Verifie les instructions
*/

int			asm_check_instruct(char *line)
{
	char	**tab;
	int		ret;

	ret = 0;
	if (ft_strchr(line, '\t'))
		tab = ft_strsplit(line, '\t');
	else
		tab = ft_strsplit(line, ' ');
	if (tab[0])
		if (!(ret = asm_instruct_name(&line)))
			return (asm_error(5));
	return (asm_free_tab(tab, 1));
}
