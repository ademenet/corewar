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
	int 	i;
	char	*temp;

	i = 0;
	temp = NULL;
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

			temp = ft_strsub(lin, i, ft_strlen(lin) - i);
			g_file = malloc(sizeof(char) * (ft_strlen(temp) + 1));
			g_file = ft_strcpy(g_file, temp);
			g_file[ft_strlen(lin)] = '\n';
			g_file[ft_strlen(lin) + 1] = '\0';
			free(temp);
			// g_file = ft_strjoin(g_file, "\n");

		}
		else
		{
			temp = ft_strsub(lin, i, ft_strlen(lin) - i);
			ft_printf("temp == --%s--\n", temp);
			// g_file[ft_strlen(g_file)] = '\n';
			g_file = realloc(g_file, (ft_strlen(g_file) + ft_strlen(temp) + 1));
			//g_file[ft_strlen(g_file) - ft_strlen(temp)] = '\n';
			//g_file[ft_strlen(g_file) - ft_strlen(temp) + 1] = '\0';
			//g_file = ft_strcpy(g_file, temp);
			g_file = ft_strcat(g_file, temp);
			g_file[ft_strlen(g_file)] = '\n';
			g_file[ft_strlen(g_file)+1] = '\0';
			free(temp);
		}
	}
}
