/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_binary_writer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gseropia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 14:26:25 by gseropia          #+#    #+#             */
/*   Updated: 2016/07/19 14:26:40 by gseropia         ###   ########.fr       */
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

int asm_call_good_function(int fct, int fd, t_label *label)
{
  asm_move_g_file(fct, fd);
  write(fd, &fct, 1);
  if (fct == 9 || fct == 12 || fct == 15)
    asm_write_dir(fd, 2, label, 0);
	if (fct == 1)
		asm_write_dir(fd, 4, label, 0);
	if (fct == 16)
	{
		write(fd,"@", 1);
		asm_write_reg(fd, 0);
	}

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
