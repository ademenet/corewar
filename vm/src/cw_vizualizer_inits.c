/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_vizualizer_inits.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 11:44:29 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/10 15:35:15 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Initialisations du visualiseur.
*/

/*
** Affiche le PC de départ en couleur.
*/

void		cw_vizualizer_init_pc(t_proc *proc)
{
	t_champion	*tmp;

	tmp = proc->champions;
	while (tmp)
	{
		cw_vizualizer_pcprint(proc, tmp, tmp->id);
		tmp = tmp->next;
	}
}

/*
** Imprime la mémoire octet par octet avec des coordonnées précises selon les
** octets.
*/

void		cw_vizualizer_init_memprint(t_proc *proc)
{
	int			i;
	int			id;
	int			x;
	int			y;

	i = 0;
	id = 0;
	x = 1;
	y = 1;
	while (y < 65)
	{
		while (x <= 191)
		{
			mvwprintw(proc->win[0], y, x, "%.2hhx", proc->mem[i]);
			x += 3;
			i++;
		}
		y++;
		x = 1;
	}
	cw_vizualizer_init_pc(proc);
}

/*
** Initialise les couleurs pour chaque champions, selon leur id. Le 5 est une
** rénitialisation (blanc sur noir).
*/

void		cw_vizualizer_init_colors(t_proc *proc)
{
	t_champion	*tmp;

	tmp = proc->champions;
	while (tmp)
	{
		if (tmp->id == 1)
			init_pair(tmp->id, COLOR_BLACK, COLOR_GREEN);
		if (tmp->id == 2)
			init_pair(tmp->id, COLOR_WHITE, COLOR_BLUE);
		if (tmp->id == 3)
			init_pair(tmp->id, COLOR_WHITE, COLOR_RED);
		if (tmp->id == 4)
			init_pair(tmp->id, COLOR_BLACK, COLOR_CYAN);
		tmp = tmp->next;
	}
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
}

/*
** Initialise le visualiseur.
*/

void		cw_vizualizer_init(t_proc *proc)
{
	initscr();
	proc->win[0] = newwin(66, 194, 0, 0);
	proc->win[1] = newwin(66, 100, 195, 0);
	start_color();
	noecho();
	cbreak();
	nodelay(proc->win[0], TRUE);
	nodelay(proc->win[1], TRUE);
	box(proc->win[0], ACS_VLINE, ACS_HLINE);
	box(proc->win[1], ACS_VLINE, ACS_HLINE);
	refresh();
	cw_vizualizer_init_colors(proc);
}
