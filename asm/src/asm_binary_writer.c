/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_binary_writer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gseropia <gseropia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 14:26:25 by gseropia          #+#    #+#             */
/*   Updated: 2016/07/27 18:46:06 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

int		asm_move_g_file(int fct)
{
	if (fct == 1 || fct == 9 || fct == 12 || fct == 14)
		g_file = g_file + 4;
	else if (fct == 2 || fct == 3 || fct == 7)
		g_file = g_file + 2;
	else if (fct == 15)
		g_file = g_file + 5;
	else
		g_file = g_file + 3;
	while (*g_file && (*g_file == '\n' || *g_file == ' ' || *g_file == '\t'))
		g_file++;
	return (1);
}

int		asm_move_separator(void)
{
	while (*g_file && *g_file != SEPARATOR_CHAR)
		g_file++;
	g_file++;
	while (*g_file && (*g_file == ' ' || *g_file == '\t'))
		g_file++;
	return (1);
}

int		asm_call_good_function_sec(int fct, int fd, t_label *label)
{
	if ((fct == 6 || fct == 7 || fct == 8) && asm_opcode(fd, 3, 0)
		&& ((asm_write_reg(fd, 1) || asm_write_dir(fd, 4, label, 1) ||
		asm_write_ind(fd, 1, label)) &&
		((asm_write_reg(fd, 1) || asm_write_dir(fd, 4, label, 1) ||
		asm_write_ind(fd, 1, label)))))
		return (asm_write_reg(fd, 0));
	else if (fct == 9 || fct == 12 || fct == 15)
		return (asm_write_dir(fd, 2, label, 0));
	else if ((fct == 10 || fct == 14) && asm_opcode(fd, 3, 0) &&
		(((asm_write_reg(fd, 1) || asm_write_dir(fd, 2, label, 1) ||
		asm_write_ind(fd, 1, label)) &&
		(asm_write_reg(fd, 1) || asm_write_dir(fd, 2, label, 1)))))
		return (asm_write_reg(fd, 0));
	else if (fct == 11 && asm_opcode(fd, 3, 0) && ((asm_write_reg(fd, 1) &&
		(asm_write_reg(fd, 1) || asm_write_dir(fd, 2, label, 1) ||
		asm_write_ind(fd, 1, label)) && (asm_write_reg(fd, 0) ||
		asm_write_dir(fd, 2, label, 0)))))
		return (1);
	else if (fct == 16 && write(fd, "@", 1))
		return (asm_write_reg(fd, 0));
	return (1);
}

int		asm_call_good_function(int fct, int fd, t_label *label)
{
	asm_move_g_file(fct);
	write(fd, &fct, 1);
	if (fct == 1)
		return (asm_write_dir(fd, 4, label, 0));
	else if ((fct == 2 || fct == 13) && asm_opcode(fd, 2, 0) &&
		((asm_write_dir(fd, 4, label, 1) || asm_write_ind(fd, 1, label))))
		return (asm_write_reg(fd, 0));
	else if (fct == 3 && asm_opcode(fd, 2, 0) && asm_write_reg(fd, 1) &&
		(asm_write_reg(fd, 0) || asm_write_ind(fd, 0, label)))
		return (1);
	else if ((fct == 4 || fct == 5) && write(fd, "T", 1) &&
	asm_write_reg(fd, 1) && asm_write_reg(fd, 1) && asm_write_reg(fd, 0))
		return (1);
	return (asm_call_good_function_sec(fct, fd, label));
}

int		asm_binary_creator(int fd, t_label *label)
{
	int fct;

	fct = 0;
	if (!(fct = asm_instruct_name(g_file)))
	{
		while (*g_file && *g_file != LABEL_CHAR)
			g_file++;
		g_file++;
		while (*g_file && (*g_file == '\n' || *g_file == ' ' ||
		*g_file == '\t'))
			g_file++;
		fct = asm_instruct_name(g_file);
	}
	if (fct != 1 && fct != 9 && fct != 12 && fct != 15)
		g_pos--;
	asm_call_good_function(fct, fd, label);
	//write(fd, "Z", 1);
	if (fct != 1 && fct != 9 && fct != 12 && fct != 15)
		g_pos++;
	g_pos = g_pos + g_temp + 1;
	while (!(g_temp = 0) && *g_file && *g_file != '\n')
		g_file++;
	g_file++;
	if (!*g_file)
		return (1);
	return (asm_binary_creator(fd, label));
}
