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

int				cw_chk_champions(t_proc *proc)
{
	t_champion	*champ;

	champ = cw_lst_last(proc->champions);
	if (champ->header->magic != COREWAR_EXEC_MAGIC)
	{
		ft_printf("%s : ", champ->header->prog_name);
		return (cw_error_msg("has a wrong magic number"));
	}
	if (champ->header->prog_size > CHAMP_MAX_SIZE)
	{
		ft_printf("%s : ", champ->header->prog_name);
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

	if ((header = malloc(sizeof(header_t))) == NULL)
		return (-1);
	if (read(fd, header, sizeof(header_t)) == -1)
		return (-2);
	header->prog_size = cw_invert_endian(header->prog_size);
	header->magic = cw_invert_endian(header->magic);
	cw_lst_push(&(proc->champions), cw_lst_new(header, c_nb));
	return (cw_chk_champions(proc));
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