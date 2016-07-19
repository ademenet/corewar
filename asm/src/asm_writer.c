/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_writer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gseropia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 10:38:48 by gseropia          #+#    #+#             */
/*   Updated: 2016/07/19 10:39:13 by gseropia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

char  *asm_morph_cor(char *champ)
{
  char *file;
  int i;

  i = 0;
  file = malloc(ft_strlen(champ) + 3);
  while (champ[i] != '.')
  {
    file[i] = champ[i];
    i++;
  }
  champ[i++] = '.';
  champ[i++] = 'c';
  champ[i++] = 'o';
  champ[i++] = 'r';
  champ[i] = '\0';
  return(champ);
}

int   asm_reader(char *g_file, t_label *label, t_header *header, char *champ)
{
  int fd;
  char *file_name;

  file_name = asm_morph_cor(champ);
  if ((fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY)) > 1)
    ft_printf("fichier.cor créé\n");

  close(fd);
  return (1);
}
