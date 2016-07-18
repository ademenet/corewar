/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_instruction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gseropia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 14:57:05 by gseropia          #+#    #+#             */
/*   Updated: 2016/07/18 14:57:16 by gseropia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

int 	asm_check_virgule(char **line)
{
	while (**line == '\t' || **line == ' ')
		(*line)++;
	if (**line != SEPARATOR_CHAR)
		return(asm_error(8));
	(*line)++;
	while (**line == '\t' || **line == ' ')
		(*line)++;
//ft_printf("\nOn en est ici -> :%s:\n", *line);
	return(1);
}

int 	asm_check_dir(char **line, int op, int check)
{
	if (**line == DIRECT_CHAR)
	{
		if (op > 8 && op != 13)
			g_pos = g_pos + 2;
		else
			g_pos = g_pos + 4;
		(*line)++;
		//ft_printf("Alors on en est la : %s\n", *line);
		if(**line == LABEL_CHAR)
			(*line)++;
		while (**line && ft_strchr(LABEL_CHARS, **line))
			(*line)++;
		while (**line == ' ' || **line == '\t')
			(*line)++;
		if (check == 1)
			return(asm_check_virgule(line));
		return (1);
	}
	//else
	//	return(asm_error(4));
	return(0);
}

int 	asm_check_reg(char **line, int check)
{
	int reg;

	reg = 0;
	if (**line == 'r')
	{
		(*line)++;
		reg = ft_atoi(*line);
		if (reg > REG_NUMBER || reg < 0)
			return(asm_error(6));
		(*line)++;
		if (reg > 9)
			(*line)++;
		if (reg > 99)
			(*line)++;
		g_pos++;
		if (check == 1)
			return(asm_check_virgule(line));
		return (1);
	}
	return(0);
}

int asm_check_ind(char **line, int check)
{
	if (ft_isdigit(**line))
	{
		while(ft_isdigit(**line))
			(*line)++;
		if (**line != '\0' && **line != '\n' 
			&& **line != SEPARATOR_CHAR && **line != ' ' && **line != '\t')
			return(asm_error(7));
		g_pos = g_pos + 2;
		if (check == 1)
			return(asm_check_virgule(line));
		return (1);
	}
	return (0);
}

int		asm_check_arg(char *line, int instruct)
{
	int	i;

	i = 0;
	//ft_printf("instruct ::: %d", instruct);
	while (*line == ' ' || *line == '\t')
		line++;
	if (instruct == 1 || instruct == 9 || instruct == 12 || instruct == 15)
		 if (asm_check_dir(&line, instruct, 0))
		 	return (1);
	if (instruct == 2)
		if ((asm_check_dir(&line, instruct, 1) || asm_check_ind(&line, 1)) && asm_check_reg(&line, 0))
			return(1);
	if (instruct == 16 && asm_check_reg(&line, 0))
		return(1);
	if ((instruct == 6 || instruct == 7 || instruct == 8) && ((asm_check_dir(&line, instruct, 1) || asm_check_reg(&line, 1) || asm_check_ind(&line, 1))
		&& (asm_check_dir(&line, instruct, 1) || asm_check_reg(&line, 1) || asm_check_ind(&line, 1)) && asm_check_reg(&line, 0)))
		return(1);
	if (instruct == 11 && asm_check_reg(&line, 1)
		&& (asm_check_dir(&line, instruct, 1) || asm_check_reg(&line, 1) || asm_check_ind(&line, 1))
		&& (asm_check_dir(&line, instruct, 0) || asm_check_reg(&line, 0)))
		return (1);
	return (0);
}