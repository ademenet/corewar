/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_processor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 12:15:17 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/21 15:39:31 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

// TODO cw_check_live_process()
	// TODO verifier que les processus ont bien fait au moins un live
// TODO verifier que CYCLE_TO_DIE != 0
	// TODO renvoyer 0 sinon.

/*
** Initialise la structure du processeur.
*/

void		cw_proc_init(t_proc *proc)
{
	ft_bzero(proc->mem, MEM_SIZE);
	proc->c_to_die = CYCLE_TO_DIE;
	proc->c = 0;
	ft_bzero(proc->live, 5);
	proc->lives_total = 0;
	proc->checks = 0;
}

/*
** cw_check_live_process checke si un processus a bien fait un live en
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
** cw_cycles vérifie si un nouveau cycle doit être exécuté.
** Si les conditions suivantes sont remplies alors les cycles s'arrêtent :
** - CYCLE_TO_DIE atteint 0 ;
** - depuis CYCLE_TO_DIE cycles un seul processus a été rapporté en vie.
*/

int			cw_cycles(t_proc *proc)
{
	if (proc->checks % MAX_CHECKS == 0)
		proc->c_to_die -= CYCLE_DELTA;
	if (proc->c % CYCLE_TO_DIE == 0) // condition a verifier si on a decrementer ctd entre temps
		cw_check_live_process(proc);
	if (proc->lives_total >= NBR_LIVE)
		proc->c_to_die -= CYCLE_DELTA;
	return (1);
}

/*
** cw_exec_process itère sur chaque processus pour savoir s'il y a
** quelque chose à faire ou pas.
*/

int			cw_exec_process(t_proc *proc, t_instruct *instruct)
{
	t_champion	*tmp;

	tmp = proc->champions;
	while (tmp)
	{
		if (proc->champions->inst_c == 0)
			instruct[proc->mem[proc->champions->pc] - 1]; // a tester !
		else
			proc->champions->inst_c--; // sinon on decremente le cycle de linstruction
		tmp = tmp->next;
	}
	return (1);
}

/*
** cw_processor mîme le processeur.
** Elle exécute les cycles, lit la mémoire tout en traitant les instructions.
*/

int			cw_processor(t_proc *proc)
{
	t_instruct	instruct[16];

	cw_proc_init(proc);
	cw_instruct_init(instruct);
	while (cw_cycles(proc)) //	 cw_cycles doit renvoyer 1 si il y a encore des choses à faire
	{
		cw_exec_process(proc, instruct); // fonction qui itere sur liste des process pour exec ou non
		proc->c++;
	}
	return (1);
}
