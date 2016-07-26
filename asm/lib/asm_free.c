/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Transmet <Transmet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 16:13:52 by Transmet          #+#    #+#             */
/*   Updated: 2016/07/26 14:32:18 by tvisenti         ###   ########.fr       */
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

char	*asm_realloc(char *line, char *file, char *temp, int i)
{
	int	len;

	if (!(len = 0) && !file)
	{
		temp = ft_strsub(line, i, ft_strlen(line) - i);
		file = malloc(sizeof(char) * (ft_strlen(temp) + 1));
		file = ft_strcpy(file, temp);
		while (file[len])
			len++;
		file[len] = '\n';
		file[len + 1] = '\0';
		free(temp);
	}
	else
	{
		temp = ft_strsub(line, i, ft_strlen(line) - i);
		file = realloc(file, (ft_strlen(file) + ft_strlen(temp) + 1));
		file = ft_strcat(file, temp);
		while (file[len])
			len++;
		file[len] = '\n';
		file[len + 1] = '\0';
		free(temp);
	}
	return (file);
}

char	*asm_free_join(char *line, char *file)
{
	int		i;
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
		file = asm_realloc(line, file, temp, i);
	return (file);
}
