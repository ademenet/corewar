/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_lfork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 16:07:20 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/12 16:13:33 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Comme fork sans le %IDX_MOD Cette opération modifie le carry.
*/

int			cw_ins_lfork(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	p;

	p = (short)cw_get_data_dir(proc, tmp, (tmp->pc + 1) % MEM_SIZE, 2);
	cw_lst_push(&proc->champions, cw_lst_new(tmp->header, tmp->num));
	proc->champions->ins = NULL;
	proc->champions->pc_origin = tmp->pc_origin;
	proc->champions->pc = (tmp->pc + (unsigned short)p) % MEM_SIZE;
	proc->champions->carry = tmp->carry;
	proc->champions->inst_c = 0;
	proc->champions->lives = 0;
	proc->champions->id = tmp->id;
	return (3);
}
