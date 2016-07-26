/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Transmet <Transmet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 16:13:52 by Transmet          #+#    #+#             */
/*   Updated: 2016/07/26 10:33:57 by tvisenti         ###   ########.fr       */
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
** Fonction qui realloc pour recuperer tout le fichier .s
*/

char	*asm_free_join(char *line, char *file)
{
	int 	i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == COMMENT_CHAR || asm_check_label(line) == 1)
		return (file);
	if (asm_check_label(line) == 2)
	{
		while (line[i] && line[i] != LABEL_CHAR)
			i++;
		i++;
	}
	if (line[i])
	{
		if (!file)
		{

			temp = ft_strsub(line, i, ft_strlen(line) - i);
			file = malloc(sizeof(char) * (ft_strlen(temp) + 1));
			file = ft_strcpy(file, temp);
			file[ft_strlen(line)] = '\n';
			file[ft_strlen(line) + 1] = '\0';
			free(temp);
			// file = ft_strjoin(file, "\n");

		}
		else
		{
			temp = ft_strsub(line, i, ft_strlen(line) - i);
			// ft_printf("--Temp == --%s--\n", temp);
			// file[ft_strlen(file)] = '\n';
			file = realloc(file, (ft_strlen(file) + ft_strlen(temp) + 1));
			//file[ft_strlen(file) - ft_strlen(temp)] = '\n';
			//file[ft_strlen(file) - ft_strlen(temp) + 1] = '\0';
			//file = ft_strcpy(file, temp);
			file = ft_strcat(file, temp);
			file[ft_strlen(file)] = '\n';
			file[ft_strlen(file) + 1] = '\0';
			free(temp);
		}
	}
	return (file);
}
