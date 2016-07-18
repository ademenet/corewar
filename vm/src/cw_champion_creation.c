/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_champion_creation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/11 15:54:35 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int				cw_invert_endian(int x)
{
	x = ((x >> 24) & 0xff) | ((x >> 8) & 0xff00) | ((x << 8) & 0xff0000)
      | ((x << 24) & 0xff000000);
      return (x);
}

int				cw_get_header(t_proc *proc, char *buf, int fd)
{
	header_t	*header;
	int			i;

	if ((header = malloc(sizeof(header_t))) == NULL)
		return (-1);
	if (read(fd, header, sizeof(header_t)) == -1)
		return (-2);
	i = -1;
	while (proc->champions[++i]);
	header->prog_size = cw_invert_endian(header->prog_size);
	proc->champions[i] = malloc(sizeof(t_champion));
	proc->champions[i]->header = header;
	ft_printf("%u %s %u %s\n", proc->champions[0]->header->magic, proc->champions[0]->header->prog_name,
		proc->champions[0]->header->prog_size, proc->champions[0]->header->comment);
	return (1);
}

int				cw_create_champion(char *file, int c_nb, t_proc *proc)
{
	int			fd;
	int			chk;
	char		*buf;

	if ((fd = open(file, O_RDONLY, 0555)) == -1)
		return (-1);
	chk = cw_get_header(proc, buf, fd);
	ft_printf("chk :%d\n", chk);
	return (1);
	//ne pas oublier le close !
}