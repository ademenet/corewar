/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_processor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 12:15:17 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/27 12:10:23 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

// TODO cw_check_live_process()
	// TODO verifier que les processus ont bien fait au moins un live
// TODO verifier que CYCLE_TO_DIE != 0
	// TODO renvoyer 0 sinon.
// TODO fonction pour calculer la taille de l'ensemble de l'instruction
// pour pouvoir faire sauter le PC a la prochaine instruction.

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

int			cw_exec_process(t_proc *proc)
{
	t_champion	*tmp;
	t_ocp		ocp;
	int			size;

	tmp = proc->champions;
	while (tmp)
	{
		size = 0;
		if (tmp->inst_c == 0)
		{
			// ICI fonction qui recupere les params s'il y a ! et retourne la taille dune instruction
			cw_ins_ocp(proc, tmp, &ocp); // size n'est plus donne par cette fonction mais par le retour de la fonction dinstruction
			size = g_op[proc->mem[tmp->pc] - 1].ptr(proc);
			// ICI on fait jumper le PC !!!
			tmp->pc = (tmp->pc + size) % MEM_SIZE;
		}
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
	WINDOW	*win;
	WINDOW	*win_g;
	WINDOW	*win_d;

	cw_proc_init(proc);
	cw_load_ins_c(proc);

	// while (cw_cycles(proc)) //	 cw_cycles doit renvoyer 1 si il y a encore des choses à faire
	// {
	// 	cw_exec_process(proc); // fonction qui itere sur liste des process pour exec ou non
	// 	proc->c++;
	// 	cw_vizualizer(proc);
	// 	getchar();
	// }

	initscr();
	cbreak();
	noecho();
	win = newwin(200, 350, 0, 0);
	win_g = subwin(win, HVIZ, WVIZ, 1, 1);
	win_d = subwin(win, HVIZ, 100, HVIZ + 1, 0);
	refresh();
	while (cw_cycles(proc))
	{
		cw_exec_process(proc); // fonction qui itere sur liste des process pour exec ou non
		cw_vizualizer(proc, win_g);
		wprintw(win_d, "Nombres de cycles : %d", proc->c);
		wrefresh(win);
		wrefresh(win_g);
		// wrefresh(win_d);
		refresh();
		getch();
		proc->c++;
	}
	delwin(win);
	endwin();
	return (1);
}
