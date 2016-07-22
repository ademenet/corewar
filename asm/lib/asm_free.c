/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Transmet <Transmet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 16:13:52 by Transmet          #+#    #+#             */
/*   Updated: 2016/07/22 11:02:53 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** Free le tableau
*/

int		asm_free_tab(char **tab, int ret)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			i++;
			free(tab[i - 1]);
		}
		free(tab);
	}
	return (ret);
}

/*
** Fonction qui realloc la globale g_file
*/

void	asm_free_join(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == COMMENT_CHAR || asm_check_label(line) == 1)
		return ;
	if (asm_check_label(line) == 2)
	{
		while (*line != LABEL_CHAR)
			line++;
		line++;
	}
	if (*line)
	{
		if (!g_file)
		{
			g_file = ft_strdup(line);
			g_file = ft_strjoin(g_file, "\n");
		}
		else
		{
			g_file = realloc(g_file, ft_strlen(line) + ft_strlen(g_file) + 1);
			g_file = ft_strjoin(g_file, line);
			g_file = ft_strjoin(g_file, "\n");
		}
	}
}
