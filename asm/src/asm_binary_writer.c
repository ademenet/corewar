/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_binary_writer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DeSeropelly <DeSeropelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 14:26:25 by gseropia          #+#    #+#             */
/*   Updated: 2016/07/28 09:21:31 by DeSeropelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

char	*asm_move_file(int fct, char *file)
{
	if (fct == 1 || fct == 9 || fct == 12 || fct == 14)
		file = file + 4;
	else if (fct == 2 || fct == 3 || fct == 7)
		file = file + 2;
	else if (fct == 15)
		file = file + 5;
	else
		file = file + 3;
	while (*file && (*file == ' ' || *file == '\t'))
		file++;
	return (file);
}

int		asm_move_separator(char **file)
{
	while (**file && **file != SEPARATOR_CHAR && **file != '\n')
		(*file)++;
	if (**file == '\n')
	{
		(*file)++;
		return(1);
	}
	(*file)++;
	while (**file && (**file == ' ' || **file == '\t'))
		(*file)++;
	return (1);
}

int		asm_call_good_function_sec(int fct, int fd, t_label *label, char **file)
{
	if ((fct == 6 || fct == 7 || fct == 8) && asm_opcode(fd, 3, 0, *file)
		&& ((asm_write_reg(fd, file) || asm_write_dir(fd, 4, label, file) ||
		asm_write_ind(fd, label, file)) &&
		((asm_write_reg(fd, file) || asm_write_dir(fd, 4, label, file) ||
		asm_write_ind(fd, label, file)))))
		return (asm_write_reg(fd, file));
	else if (fct == 9 || fct == 12 || fct == 15)
		return (asm_write_dir(fd, 2, label, file));
	else if ((fct == 10 || fct == 14) && asm_opcode(fd, 3, 0, *file) &&
		(((asm_write_reg(fd, file) || asm_write_dir(fd, 2, label, file) ||
		asm_write_ind(fd, label, file)) &&
		(asm_write_reg(fd, file) || asm_write_dir(fd, 2, label, file)))))
		return (asm_write_reg(fd, file));
	else if (fct == 11 && asm_opcode(fd, 3, 0, *file) && ((asm_write_reg(fd, file) &&
		(asm_write_reg(fd, file) || asm_write_dir(fd, 2, label, file) ||
		asm_write_ind(fd, label, file)) && (asm_write_reg(fd, file) ||
		asm_write_dir(fd, 2, label, file)))))
		return (1);
	else if (fct == 16 && write(fd, "@", 1))
		return (asm_write_reg(fd, file));
	return (1);
}

int		asm_call_good_function(int fct, int fd, t_label *label, char **file)
{
	*file  = asm_move_file(fct, *file);
	write(fd, &fct, 1);
	if (fct == 1)
		return (asm_write_dir(fd, 4, label, file));
	else if ((fct == 2 || fct == 13) && asm_opcode(fd, 2, 0, *file) &&
		((asm_write_dir(fd, 4, label, file) || asm_write_ind(fd, label, file))))
		return (asm_write_reg(fd, file));
	else if (fct == 3 && asm_opcode(fd, 2, 0, *file) && asm_write_reg(fd, file) &&
		(asm_write_reg(fd, file) || asm_write_ind(fd, label, file)))
		return (1);
	else if ((fct == 4 || fct == 5) && write(fd, "T", 1) &&
	asm_write_reg(fd, file) && asm_write_reg(fd, file) && asm_write_reg(fd, file))
		return (1);
	return (asm_call_good_function_sec(fct, fd, label, file));
}

int		asm_binary_creator(int fd, t_label *label, char *file)
{
	int fct;

	fct = 0;
	while (*file)
	{
		fct = asm_instruct_name(file);
		
		if (fct != 1 && fct != 9 && fct != 12 && fct != 15)
			g_pos--;
		asm_call_good_function(fct, fd, label, &file);
		if (fct != 1 && fct != 9 && fct != 12 && fct != 15)
			g_pos++;
		g_pos = g_pos + g_temp + 1;
	}
	if (!*file)
		return (1);
	return (asm_binary_creator(fd, label, file));
}
