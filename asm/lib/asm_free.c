/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Transmet <Transmet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 16:13:52 by Transmet          #+#    #+#             */
/*   Updated: 2016/07/26 15:06:15 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** Free les pointeurs sur GNL
*/

void	asm_free_global(void)
{
	if (g_tmp_line)
		free(g_tmp_line);
	if (g_tmp_file)
		free(g_tmp_file);
}

/*
** Free la liste label
*/

int		asm_free_label(t_label *label)
{
	t_label	*nxt;
	nxt = label->next;
	while (nxt)
	{
		free(label->name);
		free(label);
		label = nxt;
		nxt = label->next;
	}
	if (label)
	{
		free(label->name);
		free(label);
	}
	return (1);
}

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
** Fonction qui realloc pour recuperer tout le fichier .s k
*/

char	*asm_realloc(char *line, char *file, char *temp, int i)
{
	int	len;
	char *temp2;

	temp2 = NULL;
	if (!(len = 0) && !file)
	{
		temp = ft_strsub(line, i, ft_strlen(line) - i);
		file = malloc(sizeof(char) * (ft_strlen(temp) + 1));
		file = ft_strcpy(file, temp);
		while (file[len])
			len++;
		file[len] = '\n';
		file[len + 1] = '\0';
		// ft_printf("gfile = %s\n", file);
	}
	else
	{
		// ft_printf("LINE : %s\n", line);
		temp = ft_strsub(line, i, ft_strlen(line) - i);
		// ft_printf("Juste temp : %s\n", temp);
		temp2 = malloc(sizeof(char) * (ft_strlen(file) + ft_strlen(temp) + 1));
		// ft_printf("file avant le cpy : %s\n", file);
		temp2 = ft_strcpy(temp2, file);
		// ft_printf("temp2 : %s\n", temp2);
		// ft_printf(" francis la linetemp : %s\n", temp);
		temp2 = ft_strcat(temp2, temp);
		// ft_printf(" francis la line2 : %s\n", temp2);
		free(file);
		while (temp2[len])
			len++;
		temp2[len] = '\n';
		temp2[len + 1] = '\0';
		file = ft_strdup(temp2);
		//if (temp2)
		//{
		//	free(temp2);
		//	temp2 = NULL;
		//}
	}
	return (file);
}

char	*asm_free_join(char *line, char *file)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	//ft_printf("FILE DEBUT : %s\n", file);
	//while (line[i] == ' ' || line[i] == '\t')
	//	i++;
	//{
	//	while (line[i] && line[i] != LABEL_CHAR)
	//		i++;
	//	i++;
	//}
	if (line[i])
		file = asm_realloc(line, file, temp, i);
	// if (temp)
	// {
	// 	ft_printf("AVANT LE FREE\n");
	// 	free(temp);
	// 	ft_printf("I WANT YPU BREAK FREE\n");
	// }
	return (file);
}
