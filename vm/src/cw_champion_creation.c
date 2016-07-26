/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_champion_creation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/26 10:41:01 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

int				cw_find_num(t_proc *proc, int c_nb)
{
	t_champion	*tmp;

	tmp = proc->champions;
	while (tmp)
	{
		if (tmp->num == c_nb)
		{
			c_nb++;
			tmp = proc->champions;
		}
		else
			tmp = tmp->next;
	}
	return (c_nb);
}

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

int				cw_get_header(t_proc *proc, int fd, int c_nb, int n)
{
	t_header	*header;

	if ((header = malloc(sizeof(t_header))) == NULL)
		return (cw_error_msg("failed to malloc the header"));
	if (read(fd, header, sizeof(t_header)) == -1)
		return (cw_error_msg("failed to read the header"));
	header->prog_size = cw_invert_endian(header->prog_size);
	header->magic = cw_invert_endian(header->magic);
	if (n)
		cw_lst_add(&(proc->champions), cw_lst_new(header, c_nb));
	else
		cw_lst_push(&(proc->champions), cw_lst_new(header, 0));
	return (cw_chk_champions(proc));
}

int				cw_create_champion(char *file, int c_nb, t_proc *proc, int n)
{
	int			fd;
	int			chk;
	t_champion	*c_in_load;

	if ((fd = open(file, O_RDONLY, 0555)) == -1)
		return (cw_error_msg("failed to open .cor"));
	chk = cw_get_header(proc, fd, c_nb, n);
	c_nb = n ? c_nb : cw_find_num(proc, c_nb);
	proc->champions->num = proc->champions->num ? proc->champions->num : c_nb;
	c_in_load = n ? cw_lst_last(proc->champions) : proc->champions;

	if (chk && (c_in_load->ins = malloc(c_in_load->header->prog_size)) == NULL)
		return (cw_error_msg("failed to malloc instruction failed"));

	if (read(fd, c_in_load->ins, c_in_load->header->prog_size) == -1)
		return (cw_error_msg("failed to load instructions"));
	return (chk);
}
