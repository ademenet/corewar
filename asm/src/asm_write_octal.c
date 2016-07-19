/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_write_octal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gseropia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 17:47:55 by gseropia          #+#    #+#             */
/*   Updated: 2016/07/19 17:48:16 by gseropia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"


int asm_write_dir(int fd, int size, t_label *label, int check)
{
	int i;

	i = 0;
	g_file++;
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
  if (check)
  	asm_check_virgule(&g_file);
  return (1);
}

int asm_write_ind(int fd, int check)
{
	int i;

	i = ft_atoi(g_file);
	i = cw_invert_endian(i);
	write(fd, &i, T_IND);
	g_pos = g_pos + T_IND;
	if (check)
    	asm_check_virgule(&g_file);
	return (1);
}

int asm_write_reg(int fd, int check)
{
	int i;

	i = ft_atoi(++g_file);
	ft_printf("char : %c", *g_file);
	write(fd, &i, T_REG);
	g_pos = g_pos + T_REG;
	if (check)
    	asm_check_virgule(&g_file);
	return (1);
}
