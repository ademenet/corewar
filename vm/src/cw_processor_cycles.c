/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_processor_cycles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 18:18:16 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/28 18:39:02 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void		cw_dump_display(t_proc *proc)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i != 0)
			i % 32 == 0 ? ft_printf("\n") : ft_printf(" ");
		ft_printf("%.2hhx", proc->mem[i]);
		i++;
	}
}

/*
** cw_cycles vérifie si un nouveau cycle doit être exécuté.
** Si les conditions suivantes sont remplies alors les cycles s'arrêtent :
** - CYCLE_TO_DIE atteint 0 ;
** - depuis CYCLE_TO_DIE cycles un seul processus a été rapporté en vie.
*/

int			cw_cycles(t_proc *proc)
{
	// if (proc->checks % MAX_CHECKS == 0)
	// 	proc->c_to_die -= CYCLE_DELTA;
	// if (proc->c % CYCLE_TO_DIE == 0) // condition a verifier si on a decrementer ctd entre temps
	// 	cw_check_live_process(proc);
	// if (proc->lives_total >= NBR_LIVE)
	// 	proc->c_to_die -= CYCLE_DELTA;
	return (1);
}

/*
**
*/

int		cw_cycles_checks(t_proc *proc)
{
	if (proc->dump != 0 && proc->c == proc->dump)
	{
		cw_dump_display(proc);
		return (0);
	}
	return (1);
}
