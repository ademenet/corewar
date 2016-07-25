/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Transmet <Transmet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 16:13:52 by Transmet          #+#    #+#             */
/*   Updated: 2016/07/25 11:48:20 by tvisenti         ###   ########.fr       */
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

void	asm_free_join(char *lin)
{
	int i;

	i = 0;
	while (lin[i] == ' ' || lin[i] == '\t')
		i++;
	if (lin[i] == COMMENT_CHAR || asm_check_label(lin) == 1)
		return ;
	if (asm_check_label(lin) == 2)
	{
		while (lin[i] && lin[i] != LABEL_CHAR)
			i++;
		i++;
	}
	if (lin[i])
	{
		if (!g_file)
		{
			g_file = ft_strsub(lin, i, ft_strlen(lin) - i);
			g_file = ft_strjoin(g_file, "\n");
		}
		else
		{
			g_file = realloc(g_file, ft_strlen(lin) + ft_strlen(g_file) + 1);
			g_file = ft_strjoin(g_file, ft_strsub(lin, i, ft_strlen(lin) - i));
			g_file = ft_strjoin(g_file, "\n");
		}
	}
}
