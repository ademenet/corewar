/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_instruct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 13:05:23 by tvisenti          #+#    #+#             */
/*   Updated: 2016/07/17 15:10:04 by Transmetropolitan###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** Verifie si le nom de l'instruction est correct
*/

int			asm_instruct_name_sec(char **line)
{
	if (ft_strncmp("ldi", *line, 3) == 0)
		return (10);
	//printf("On pointe ici : --%c--\n", *line);
	if (ft_strncmp("sti", *line, 3) == 0)
		return (11);
	//printf("On pointe la : --%c--\n", *line);
	if (ft_strncmp("fork", *line, 4) == 0)
		return (12);
	if (ft_strncmp("lld", *line, 3) == 0)
		return (13);
	if (ft_strncmp("lldi", *line, 4) == 0)
		return (14);
	if (ft_strncmp("lfork", *line, 5) == 0)
		return (15);
	if (ft_strncmp("aff", *line, 3) == 0)
		return (16);
	return (asm_error(5));
}

int			asm_instruct_name(char **line)
{
	while (**line == ' ' || **line == '\t')
	{
		//printf("On pointe ici : --%c--\n",*line);
		(*line)++;
	}
	//printf("On pointe la : --%c--\n",*line);
	if (ft_strncmp("live", *line, 4) == 0)
		return (1);
	if (ft_strncmp("ld", *line, 2) == 0)
		return (2);
	if (ft_strncmp("st", *line, 2) == 0)
		return (3);
	if (ft_strncmp("add", *line, 3) == 0)
		return (4);
	if (ft_strncmp("sub", *line, 3) == 0)
		return (5);
	if (ft_strncmp("and", *line, 3) == 0)
		return (6);
	if (ft_strncmp("or", *line, 2) == 0)
		return (7);
	if (ft_strncmp("xor", *line, 3) == 0)
		return (8);
	if (ft_strncmp("zjmp", *line, 4) == 0)
		return (9);
	return (asm_instruct_name_sec(line));
}

/*
** Check si il y a un label et si celui-ci et le label_char sont bien formatés
*/

int			asm_check_label(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_strchr(LABEL_CHARS, str[i]))
		i++;
	if (str[i] == LABEL_CHAR && i > 0)
	{
		i++;
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '\n' || str[i] == '\0')
			return (1);
		return (2);
	}
	else if (str[i] && str[i] != ' ' && str[i] != '\0' &&
	str[i] != '\n' && str[i] != '\t')
	{
		if (str[i + 1] == ' ' || str[i + 1] == '\n' || str[i + 1] == '\0')
			return(asm_error(4));
		return(asm_error(3));
	}
	return (0);
}
