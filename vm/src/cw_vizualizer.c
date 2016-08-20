/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_vizualizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/20 16:18:48 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Permet d'imprimer un octet dans la représentation de la mémoire du
** visualiseur.
*/

void		cw_vizualizer_print(t_proc *proc, t_champion *tmp, int where,
			unsigned char what)
{
	int		*coord;

	coord = (int*)malloc(sizeof(int) * 2);
	coord[0] = where / 64 + 1;
	if (where % 64 == 0)
		coord[1] = where % 64 + 1;
	else
		coord[1] = where % 64 * 3 + 1;
	wattron(proc->win[0], COLOR_PAIR(tmp->id + 10));
	mvwprintw(proc->win[0], coord[0], coord[1], "%.2hhx", what);
	wattroff(proc->win[0], COLOR_PAIR(tmp->id + 10));
	free(coord);
}

/*
** Permet de mettre en couleur le PC en cours. Prend un paramètre col, pour
** couleur, qui permet de sélectionner quel COLOR_PAIR choisir. Ce qui permet
** une plus grande souplesse pour "allumer" ou "éteindre" un PC. Le COLOR_PAIR
** 5 permet de réinitialiser la couleur.
*/

void		cw_vizualizer_pcprint(t_proc *proc, t_champion *tmp, char col)
{
	int		*coord;

	coord = (int*)malloc(sizeof(int) * 2);
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

/*
** Affiche les informations se trouvant sur le côté de la VM.
*/

void		cw_vizualizer_infos_side(t_proc *proc, int y)
{
	mvwprintw(proc->win[1], (y = y + 1), 2, "lives total\t: %8d",
		proc->lives_total);
	mvwprintw(proc->win[1], (y = y + 1), 2, "CYCLE_TO_DIE\t: %8d",
		proc->c_to_die);
	mvwprintw(proc->win[1], (y = y + 1), 2, "CYCLE_DELTA\t: %8d", CYCLE_DELTA);
	mvwprintw(proc->win[1], (y = y + 1), 2, "NBR_LIVE\t: %8d", NBR_LIVE);
	mvwprintw(proc->win[1], (y = y + 1), 2, "MAX_CHECKS\t: %8d", MAX_CHECKS);
}

/*
** Affiche les informations qui se trouvent à côté du visualiseur de mémoire.
*/

void		cw_vizualizer_infos(t_proc *proc)
{
	t_champion	*tmp;
	int			y;

	mvwprintw(proc->win[1], 1, 2, "Cycle\t: %8d", proc->c);
	tmp = proc->champions;
	y = 4;
	while (tmp)
	{
		if (tmp->is_champ != 0)
		{
			wattron(proc->win[1], COLOR_PAIR(tmp->id + 10) | A_BOLD);
			mvwprintw(proc->win[1], y, 2, "Player %d : %s", tmp->num,
				tmp->header->prog_name);
			wattroff(proc->win[1], COLOR_PAIR(tmp->id + 10) | A_BOLD);
			mvwprintw(proc->win[1], (y = y + 1), 4, "lives : %u",
				proc->live[tmp->id - 1]);
			y += 2;
		}
		tmp = tmp->next;
	}
	cw_vizualizer_infos_side(proc, y);
}

/*
** TODO fonction en cours de travail pour gérer le start/pause.
*/

int			cw_vizualizer_control(char *play, int *ch)
{
	if (*play == 1 & *ch == 32)
		return (0);
	else if (*play == 0 & *ch == 32)
		return (1);
	return (0);
}

/*
** TODO fonction qui permet de gérer la vitesse en gérant le paramétre de la
** fonction usleep().
*/

int			cw_vizualizer_speed(int *ch)
{
	return (1);
}

/*
** Le processeur du Corewar équipé du visualiseur.
*/

int			cw_vizualizer_processor(t_proc *proc)
{
	int		c_check;
	int i = 0;
	int ch;

	c_check = 1;
	cw_proc_init(proc);
	cw_load_ins_c(proc);
	cw_vizualizer_init(proc);
	cw_vizualizer_init_memprint(proc);
	keypad(stdscr, TRUE);
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
	while (c_check)
	{
		cw_exec_process(proc); // fonction qui itere sur liste des process pour exec ou non
		cw_vizualizer_infos(proc); // fonction pour afficher les infos en dessous
		if (i == 0)
		{
			wrefresh(proc->win[1]);
			wrefresh(proc->win[0]);
			refresh();
			ch = getch();
			if (ch == 32)
				i = 10;
			else if (ch == 127)
				i = 100;
			else
				i = 1;
		}
		i--;
		c_check = cw_cycles_checks(proc);
		proc->c++;
	}
	delwin(proc->win[1]);
	delwin(proc->win[0]);
	endwin();
	return (1);
}
