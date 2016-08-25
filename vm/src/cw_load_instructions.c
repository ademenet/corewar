/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_load_instructions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/12 11:52:12 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

int				cw_load_ins_mem(t_proc *proc)
{
	int			nb_champ;
	int			cnt;
	t_champion	*tmp;

	cnt = 0;
	tmp = proc->champions;
	if ((nb_champ = cw_lst_sze(proc->champions)) > MAX_PLAYERS || !nb_champ)
		return (cw_error_msg("ERROR : wrong number of champ to load in mem"));
	while (tmp)
	{
		ft_memcpy(&(proc->mem[cnt * MEM_SIZE / nb_champ]),
		tmp->ins, tmp->header->prog_size);
		tmp->pc_origin = cnt * MEM_SIZE / nb_champ;
		free(tmp->ins);
		tmp->ins = NULL;
		tmp = tmp->next;
		cnt++;
	}
	return (1);
}
