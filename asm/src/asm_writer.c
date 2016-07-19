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

int asm_header_creator(int fd, t_header *header)
{
  int i;

  i = 0;
  write(fd, &header->magic, 4);
  while(header->prog_name[i])
    write(fd, &header->prog_name[i++], 1);
  return (1);
}
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

int   asm_reader(t_label *label, t_header *header, char *champ)
{
  int fd;
  char *file_name;
  fd = 0;
  file_name = asm_morph_cor(champ);
  if ((fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC | O_APPEND ,0777)) > -1)
  {
    ft_printf("fichier.cor créé avec un fd de %d et un header de %s\n", fd, header->prog_name);
    asm_header_creator(fd, header);
  //  asm_binary_creator(fd);
  }
  close(fd);
  return (1);
}
