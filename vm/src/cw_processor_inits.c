/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_processor_inits.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 18:27:46 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/01 12:34:19 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Initialise la structure du processeur.
*/

void		cw_proc_init(t_proc *proc)
{
	// t_p		*tmp;

	proc->c_to_die = CYCLE_TO_DIE + CYCLE_DELTA;
	proc->c = 1;
	proc->lives_total = 0;
	proc->checks = 0;
	// 		L'initialisation des champions est faite avant normalement, plus
	// 		besoin de la faire, et les processus lors de leur creations
	// tmp = proc->champions;
	// while (tmp)
	// {
	// 	tmp->pc = tmp->pc_origin;
	// 	tmp->inst_c = 0;
	// 	tmp = tmp->next;
	// }
}

void		cw_get_opcode(t_proc *proc, t_p *tmp)
{
	if (proc->mem[tmp->pc] > 0x00 && proc->mem[tmp->pc] < 0x11)
	{
		tmp->opcode = proc->mem[tmp->pc];
		tmp->ins_c = g_op[proc->mem[tmp->pc] - 1].cycles_nb;
	}
	else
	{
		tmp->opcode = 0;
		tmp->ins_c = 0;
	}
}

/*
** Charge les premières instructions dans les processus avant le lancement à
** proprement parlé des cycles de la VM.
*/

void		cw_load_ins_c(t_proc *proc)
{
	t_p		*tmp;

	tmp = proc->process;
	while (tmp)
	{
		if (tmp->opcode == 0)
			cw_get_opcode(proc, tmp);
		tmp = tmp->next;
	}
}
