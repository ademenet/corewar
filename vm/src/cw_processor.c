/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_processor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 12:15:17 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/14 15:53:13 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

int			process_nb = 0; // a ajouter a une structure contenant les processus

t_glob		glob;

/*
** Initialise la structure du processeur.
*/

void		cw_proc_init(t_proc *proc)
{
	proc->cyc_to_die = CYCLE_TO_DIE;
	proc->cyc = 0;
	proc->checks = 0;
	ft_bzero(glob->proc->live, 5);
}

/*
** cw_cycles vérifie si un nouveau cycle doit être exécuté.
** Si les conditions suivantes sont remplies alors les cycles s'arrêtent :
** - CYCLE_TO_DIE atteint 0 ;
** - depuis CYCLE_TO_DIE cycles un seul processus a été rapporté en vie.
*/

int			cw_cycles(t_proc *proc)
{
	if (proc->cyc % CYCLE_TO_DIE == 0)
	{
		proc->checks++:
		while ()
	}
		// TODO verifier que les processus ont bien fait au moins un live
		// TODO verifier que CYCLE_TO_DIE != 0
		// TODO renvoyer 0 sinon.
	if (proc->checks % MAX_CHECKS == 0) // Si on n’a pas décrémenté CYCLE_TO_DIE depuis MAX_CHECKS vérifications, on le décrémente
		proc->cyc_to_die -= CYCLE_DELTA; // ATTN ! En debut ou en fin de cycle ???
	return (1);
}

/*
** cw_processor mîme le processeur.
** Elle exécute les cycles, lit la mémoire tout en traitant les instructions.
*/

int			cw_processor()
{
	t_proc	proc;

	cw_proc_init(&proc); // initialise les variables de proc
	while (cw_cycles(&proc)) // cw_cycles doit renvoyer 1 si il y a encore des choses à faire
	{
		// on itère sur la liste de processus -> on vérifie que on a une instruction à faire ou pas
		proc.cyc++; // incremente le cycle de 1
	}
	return (1);
}
