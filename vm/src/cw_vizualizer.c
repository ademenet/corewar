/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_vizualizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/10 15:26:52 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Permet de mettre en couleur le PC en cours.
*/

void		cw_vizualizer_pcprint(t_proc *proc, t_champion *tmp, char col)
{
	int		*coord;

	coord = (int*)malloc(sizeof(int) * 2);
	// coord = cw_vizualizer_getcoord(tmp->pc, coord);
	coord[0] = tmp->pc / 64 + 1;
	if (tmp->pc % 64 == 0)
		coord[1] = tmp->pc % 64 + 1;
	else
		coord[1] = tmp->pc % 64 * 3 + 1;

	wattron(proc->win[0], COLOR_PAIR(col));
	mvwprintw(proc->win[0], coord[0], coord[1], "%.2hhx", proc->mem[tmp->pc]);
	wattroff(proc->win[0], COLOR_PAIR(col));
	free(coord);
}

void		cw_vizualizer_infos(t_proc *proc)
{
	t_champion	*tmp;
	int			x;

	mvwprintw(proc->win[1], 1, 1, "Nombres de cycles : %d", proc->c);
	mvwprintw(proc->win[1], 1, 2, "Cycle to die : %d", proc->c_to_die);
	tmp = proc->champions;
	x = 4;
	while (tmp)
	{
		if (tmp->is_champ == 1)
		{
			mvwprintw(proc->win[1], 1, x, "Player %d : %s", tmp->num,
				tmp->header->prog_name);
			x += 2;
		}
		tmp = tmp->next;
	}
}


int			cw_vizualizer_control(char *play, int *ch)
{
	if (*play == 1 & *ch == 32)
		return (0);
	else if (*play == 0 & *ch == 32)
		return (1);
	return (0);
}

int			cw_vizualizer_speed(int *ch)
{
	return (1);
}


int			cw_vizualizer_processor(t_proc *proc)
{
	int		c_check;

	c_check = 1;
	cw_proc_init(proc);
	cw_load_ins_c(proc);
	cw_vizualizer_init(proc);
	cw_vizualizer_init_memprint(proc);
	// while (1)
	// {
	// 	ch = getch();
	// 	if (cw_vizualizer_control(&play, &ch))
	// 	{
	// 		while (cw_cycles(proc))
	// 		{
	// 			mvprintw(0, 200, "[%d]", ch);
	// 			ch = getch();
	// 			cw_exec_process(proc); // fonction qui itere sur liste des process pour exec ou non
	// 			cw_vizualizer(proc, win[1]); // fonction pour afficher la mem
	// 			cw_vizualizer_infos(proc, win[2]); // fonction pour afficher les infos en dessous
	// 			wrefresh(win[1]);
	// 			wrefresh(win[2]);
	// 			wrefresh(win[0]);
	// 			proc->c++;
	// 			usleep(300000000);
	// 		}
	// 	}
	while (cw_cycles(proc) && c_check)
	{
		cw_exec_process(proc); // fonction qui itere sur liste des process pour exec ou non
		cw_vizualizer_infos(proc); // fonction pour afficher les infos en dessous
		wrefresh(proc->win[1]);
		wrefresh(proc->win[0]);
		refresh();
		getch();
		c_check = cw_cycles_checks(proc);
		proc->c++;
	}
	delwin(proc->win[1]);
	delwin(proc->win[0]);
	endwin();
	return (1);
}
