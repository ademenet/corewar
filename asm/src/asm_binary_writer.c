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

int asm_check_opcode(int fct, int fd)
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

int asm_binary_creator(int fd)
{
  int fct;

  fct = 0;
  if (asm_check_label(g_file))
  {
    while(*g_file && *g_file != LABEL_CHAR)
      g_file++;
    g_file++;
    while(*g_file && (*g_file == '\n' || *g_file == ' ' || *g_file == '\t'))
      g_file++;
  }
  asm_check_opcode(fct = asm_instruct_name(&g_file), fd);
  printf("le file entier :\n%s\net 11 normalement : %d", g_file, fct);
  return(1);
}
