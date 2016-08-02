/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_vizualizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/02 11:11:29 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Permet de mettre en couleur le PC en cours.
*/

int			cw_vizualizer_pcprint(t_proc *proc, int *i)
{
	t_champion	*tmp;

	tmp = proc->champions;
	while (tmp)
	{
		if (*i == tmp->pc)
			return (tmp->num);
		tmp = tmp->next;
	}
	return (0);
}

/*
** Imprime la mémoire :
*/

void		cw_vizualizer_memprint(t_proc *proc, WINDOW *win)
{
	int			i;
	int			num;

	i = 0;
	num = 0;
	// wclear(win);
	wmove(win, 0, 0);
	while (i < MEM_SIZE)
	{
		if (i != 0)
			i % 64 == 0 ? wprintw(win, "\n") : wprintw(win, " ");
		if ((num = cw_vizualizer_pcprint(proc, &i)))
		{
			wattron(win, COLOR_PAIR(num));
			wprintw(win, "%.2hhx", proc->mem[i]);
			wattroff(win, COLOR_PAIR(num));
		}
		else
			wprintw(win, "%.2hhx", proc->mem[i]);
		i++;
		// wrefresh(win);
	}
}

void		cw_vizualizer_infos(t_proc *proc, WINDOW *win)
{
	t_champion	*tmp;
	int			y;

	tmp = proc->champions;
	y = 2;
	mvwprintw(win, 1, 1, "Nombres de cycles : %d", proc->c);
	while (tmp)
	{
		mvwprintw(win, y, 1, "Player %d : %s", tmp->num,
			tmp->header->prog_name);
		mvwprintw(win, y, 20, "inst_c = %.2hhx", tmp->inst_c); // pour debug
		mvwprintw(win, y, 35, "valeur au pc = %.2hhx", proc->mem[tmp->pc]); // pour debug
		tmp = tmp->next;
		y++;
	}
	mvwprintw(win, 1, 91, "Cycle to die : %d", proc->c_to_die);
}

/*
** À compiler avec "gcc -lncurses ..."
*/

void		cw_vizualizer(t_proc *proc, WINDOW *win)
{
	// WINDOW	*win;
	// int		ch; // pour le controle plus tard ==> il faut d'abord faire en sorte de l'appeler en params

	// initscr();
	// cbreak();
	// win = newwin(80, 200, 0, 0);
	// refresh();
	t_champion	*tmp;
	int			color;

	tmp = proc->champions;
	color = 1;
	start_color();
	while (tmp)
	{
		if (color == 1)
			init_pair(tmp->num, COLOR_BLACK, COLOR_GREEN);
		if (color == 2)
			init_pair(tmp->num, COLOR_WHITE, COLOR_BLUE);
		if (color == 3)
			init_pair(tmp->num, COLOR_WHITE, COLOR_RED);
		if (color == 4)
			init_pair(tmp->num, COLOR_BLACK, COLOR_CYAN);
		color++;
		tmp = tmp->next;
	}
	cw_vizualizer_memprint(proc, win);
	// wrefresh(win);
	// getch();
	// delwin(win);
	// endwin();
}

int			cw_vizualizer_processor(t_proc *proc)
{
	WINDOW	*win[3];


	cw_proc_init(proc);
	cw_load_ins_c(proc);
	initscr();
	cbreak();
	noecho();
	win[0] = newwin(76, 194, 0, 0);
	win[1] = subwin(win[0], 65, 192, 1, 1);
	win[2] = subwin(win[0], 10, 192, 66, 1);
	box(win[0], ACS_VLINE, ACS_HLINE);
	refresh();

	while (cw_cycles(proc))
	{
		cw_vizualizer(proc, win[1]); // fonction pour afficher la mem
		cw_vizualizer_infos(proc, win[2]); // fonction pour afficher les infos en dessous
		wrefresh(win[1]);
		wrefresh(win[2]);
		wrefresh(win[0]);
		refresh();
		// getch();
		getchar();
		cw_exec_process(proc); // fonction qui itere sur liste des process pour exec ou non
		proc->c++;
	}
	delwin(win[0]);
	delwin(win[1]);
	delwin(win[2]);
	endwin();
	return (1);
}
