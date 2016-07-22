/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_write_octal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gseropia <gseropia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 17:47:55 by gseropia          #+#    #+#             */
/*   Updated: 2016/07/22 11:22:23 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

void	asm_opcode_assign(int *octout, int i, int check)
{
	if (check == 1 && g_file[i] == 'r')
		*octout = 0x40;
	else if (check == 1 && g_file[i] == '%')
		*octout = 0x80;
	else if (check == 1)
		*octout = 0xC0;
	if (check == 2 && g_file[i] == 'r')
		*octout = 0x10;
	else if (check == 2 && g_file[i] == '%')
		*octout = 0x20;
	else if (check == 2)
		*octout = 0x30;
	if (check == 3 && g_file[i] == 'r')
		*octout = 0x4;
	else if (check == 3 && g_file[i] == '%')
		*octout = 0x8;
	else if (check == 3)
		*octout = 0xC;
}

int		asm_opcode(int fd, int arg, int i)
{
	int octout;
	int octin;

	octin = 0;
	octout = 0;
	asm_opcode_assign(&octout, i, 1);
	octin = (octin | octout);
	if (arg > 1)
	{
		i = asm_move_my_i(i);
		asm_opcode_assign(&octout, i, 2);
		octin = (octin | octout);
	}
	if (arg > 2)
	{
		i = asm_move_my_i(i);
		asm_opcode_assign(&octout, i, 3);
		octin = (octin | octout);
	}
	write(fd, &octin, 1);
	return (1);
}

int		asm_write_dir(int fd, int size, t_label *label, int check)
{
	int	i;

	if (!(i = 0) && *g_file != DIRECT_CHAR)
		return (0);
	if (++g_file && *g_file == LABEL_CHAR && g_file++)
		while (label)
		{
			if (!ft_strncmp(label->name, g_file, ft_strlen(label->name)))
			{
				i = label->pos - g_pos;
				break ;
			}
			label = label->next;
		}
	else
		i = ft_atoi(g_file);
	if (size == 4)
		i = cw_invert_endian(i);
	else
		i = cw_invert_endian2(i);
	write(fd, &i, size);
	g_temp = g_temp + size;
	if (check)
		asm_move_separator();
	return (1);
}

int		asm_write_ind(int fd, int check)
{
	int	i;

	i = ft_atoi(g_file);
	i = cw_invert_endian2(i);
	g_file = g_file + write(fd, &i, T_IND);
	g_temp = g_temp + T_IND;
	if (check)
		asm_move_separator();
	return (1);
}

int		asm_write_reg(int fd, int check)
{
	int	i;

	i = 0;
	if (*g_file != 'r')
		return (0);
	i = ft_atoi(++g_file);
	g_file = g_file + write(fd, &i, T_REG);
	g_temp = g_temp + T_REG;
	if (check)
		asm_move_separator();
	return (1);
}
