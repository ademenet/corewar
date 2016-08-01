/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_processor_cycles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 18:18:16 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/01 10:37:29 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** cw_check_live_process vérifie si un processus a bien fait un live en
** CYCLE_TO_DIE cycles.
*/

int			cw_check_live_process(t_proc *proc)
{
	t_champion	*tmp;

	tmp = proc->champions;
	while (tmp)
	{
		if (tmp->lives == 0)
			// kill le process en le retirant de la liste
		tmp = tmp->next;
	}
	proc->checks++; // incremente le checks car on a effectue un nouveau check
	return (1);
}

/*
** Affiche la mémoire selon la norme imposée dans le sujet : 32 octets par
** ligne.
*/

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
** cw_cycles_checks va vérifier en fin de cycle différentes choses, dont les
** condtions de victoires.
*/

int		cw_cycles_checks(t_proc *proc)
{
	if (proc->dump != 0 && proc->c == proc->dump) // vérifie si -dump
	{
		cw_dump_display(proc);
		return (0);
	}
	if (proc->c % CYCLE_TO_DIE == 0 && proc->c != 0)
	{
		if (proc->lives_total >= NBR_LIVE)
			proc->c_to_die -= CYCLE_DELTA;
	}
	if (proc->c % MAX_CHECKS == 0 && proc->c != 0)
		proc->c_to_die -= CYCLE_DELTA;
	return (1);
}
