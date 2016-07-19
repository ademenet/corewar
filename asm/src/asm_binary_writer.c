/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_binary_writer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gseropia <gseropia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 14:26:25 by gseropia          #+#    #+#             */
/*   Updated: 2016/07/19 18:05:47 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

int asm_move_g_file(int fct, int fd)
{
  if (fct == 1 || fct == 9 || fct == 12 || fct == 14)
		g_file = g_file + 4;
	else if (fct == 2 || fct == 3 || fct == 7)
		g_file = g_file + 2;
	else if (fct == 15)
		g_file = g_file + 5;
	else
		g_file = g_file + 3;
  while(*g_file && (*g_file == '\n' || *g_file == ' ' || *g_file == '\t'))
    g_file++;
  return (1);
}

int asm_write_dir(int fd, int size, t_label *label, int fct)
{
	int i;

	i = 0;
	g_file++;
	write(fd, &fct, 1);
	if (*g_file == LABEL_CHAR && g_file++)
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
	i = cw_invert_endian(i);
	write(fd, &i, size);
	g_pos = g_pos + size;
	return (1);
}

int asm_write_reg(int fd, int size, t_label *label, int fct)
{
	int i;

	i = 0;
	g_file++;
	write(fd, &fct, 1);
	if (*g_file == LABEL_CHAR && g_file++)
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
	i = cw_invert_endian(i);
	write(fd, &i, size);
	g_pos = g_pos + size;
	return (1);
}

int asm_call_good_function(int fct, int fd, t_label *label)
{
  asm_move_g_file(fct, fd);
  if (fct == 9 || fct == 12 || fct == 15)
    asm_write_dir(fd, 2, label, fct);
  if (fct == 1)
    asm_write_dir(fd, 4, label, fct);
  return (1);
}

int asm_binary_creator(int fd, t_label *label)
{
  int fct;

  fct = 0;
  if (!(fct = asm_instruct_name(&g_file)))
  {
    while (*g_file && *g_file != LABEL_CHAR)
      g_file++;
    g_file++;
    while (g_file && (*g_file == '\n' || *g_file == ' ' || *g_file == '\t'))
      g_file++;
    fct = asm_instruct_name(&g_file);
  }
  asm_call_good_function(fct, fd, label);
  while (*g_file && *g_file != '\n')
    g_file++;
  if (!*g_file)
    return (1);
  else
    g_file++;
  return(asm_binary_creator(fd, label));
  printf("ON EN EST LA:\n%s\net opcode normalement : %d", g_file, fct);
  return (1);
}
