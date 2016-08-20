/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_processor_inits.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 18:27:46 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/06 16:52:45 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Initialise la structure du processeur.
*/

void		cw_proc_init(t_proc *proc)
{
	t_champion	*tmp;

	proc->c_to_die = CYCLE_TO_DIE;
	proc->c = 1;
	ft_bzero(proc->live, MAX_PLAYERS + 1);
	proc->lives_total = 0;
	proc->checks = 0;
	tmp = proc->champions;
	while (tmp)
	{
		tmp->pc = tmp->pc_origin;
		tmp->ins = &proc->mem[tmp->pc];
		tmp = tmp->next;
	}
}

/*
** Fonction qui permet de "recharger" le compteur de cycles pour une nouvelle
** instruction.
** Pas très malin pour le moment car reparcourt la liste à chaque fois !
** TODO : mettre en param le processus pour charger que celui là plutot que de
** boucler.
*/

void		cw_load_ins_c(t_proc *proc)
{
	t_champion	*tmp;

	tmp = proc->champions;
	while (tmp)
	{
		if (tmp->inst_c == 0)
			tmp->inst_c = g_op[proc->mem[tmp->pc] - 1].cycles_nb;
		tmp = tmp->next;
	}
}
