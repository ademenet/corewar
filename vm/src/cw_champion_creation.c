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

int				cw_chk_champions(t_proc *proc, int i)
{
	if (proc->champions[i]->header->magic != COREWAR_EXEC_MAGIC)
	{
		ft_printf("%s : ", proc->champions[i]->header->prog_name);
		return (cw_error_msg("has a wrong magic number"));
	}
	if (proc->champions[i]->header->prog_size > CHAMP_MAX_SIZE)
	{
		ft_printf("%s : ", proc->champions[i]->header->prog_name);
		return (cw_error_msg("is too fat"));
	}
	return (1);
}

int				cw_invert_endian(int x)
{
	x = ((x >> 24) & 0xff) | ((x >> 8) & 0xff00) | ((x << 8) & 0xff0000)
      | ((x << 24) & 0xff000000);
      return (x);
}

int				cw_get_header(t_proc *proc, int fd, int c_nb)
{
	header_t	*header;
	int			i;

	if ((header = malloc(sizeof(header_t))) == NULL)
		return (-1);
	if (read(fd, header, sizeof(header_t)) == -1)
		return (-2);
	i = 4;
	header->prog_size = cw_invert_endian(header->prog_size);
	header->magic = cw_invert_endian(header->magic);
	while (proc->champions[--i] && i >= 0);
	proc->champions[i] = malloc(sizeof(t_champion));
	proc->champions[i]->header = header;
	proc->champions[i]->num = c_nb;
	return (cw_chk_champions(proc, i));
}

int				cw_create_champion(char *file, int c_nb, t_proc *proc)
{
	int			fd;
	int			chk;

	if ((fd = open(file, O_RDONLY, 0555)) == -1)
		return (-1);
	chk = cw_get_header(proc, fd, c_nb);
	return (chk);
	//ne pas oublier le close !
}