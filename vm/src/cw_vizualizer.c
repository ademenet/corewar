/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_vizualizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/10 11:16:50 by ademenet         ###   ########.fr       */
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
		if (*i == tmp->pc && tmp->is_champ != -1)
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
	// int			j;
	int			id;
	int			x;
	int			y;

	i = 0;
	// j = 2;
	id = 0;
	x = 1;
	y = 1;
	// wmove(win, 2, 2);
	// i < MEM_SIZE/
	while (y <= 65)
	{
		// if (i != 0)
		// 	i % 64 == 0 ? mvwprintw(win, y, x, "\n") : mvwprintw(win, y, x, " ");
		while (x <= 191)
		{
			mvwprintw(win, y, x, "%.2llx", proc->mem[i]);
			x += 3;
			i++;
		}
		y++;
		x = 1;
		// if ((id = cw_vizualizer_pcprint(proc, &i)))
		// {
		// 	wattron(win, COLOR_PAIR(id));
		// 	mvwprintw(win, 2, x, "%.2hhx", proc->mem[i]);
		// 	wattroff(win, COLOR_PAIR(id));
		// }
		// else
		// 	mvwprintw(win, 2, x, "%.2hhx", proc->mem[i]);
		// i++;
		// x++;
	}
}

void		cw_vizualizer_infos(t_proc *proc, WINDOW *win)
{
	t_champion	*tmp;
	int			x;

	mvwprintw(win, 196, 1, "Nombres de cycles : %d", proc->c);
	mvwprintw(win, 196, 2, "Cycle to die : %d", proc->c_to_die);
	tmp = proc->champions;
	x = 4;
	while (tmp)
	{
		if (tmp->is_champ == 1)
		{
			mvwprintw(win, 196, 1, "Player %d : %s", tmp->num,
				tmp->header->prog_name);
			x += 2;
		}
		tmp = tmp->next;
	}
}

/*
** À compiler avec "gcc -lncurses ..."
*/

void		cw_vizualizer(t_proc *proc, WINDOW *win)
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
	cw_vizualizer_memprint(proc, win);
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
	WINDOW	*win[3];
	int		c_check;

	c_check = 1;
	start_color();
	cw_proc_init(proc);
	cw_load_ins_c(proc);

	initscr();
	noecho();

	init_pair(21, COLOR_WHITE, COLOR_BLUE);
	init_pair(22, COLOR_WHITE, COLOR_WHITE);

	win[0] = newwin(66, 300, 0, 0);
	win[1] = subwin(win[0], 66, 196, 0, 0);
	win[2] = subwin(win[0], 66, 98, 200, 1);

	box(win[0], ACS_VLINE, ACS_HLINE);
	box(win[1], ACS_VLINE, ACS_HLINE);
	box(win[2], ACS_VLINE, ACS_HLINE);

	cbreak();
	nodelay(win[0], TRUE);

	wbkgd(win[2], COLOR_PAIR(21));
	wbkgd(win[1], COLOR_PAIR(22));

	mvwprintw(win[0], 100, 10, "COUCOU");
	refresh();
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
		cw_vizualizer(proc, win[1]); // fonction pour afficher la mem
		cw_vizualizer_infos(proc, win[2]); // fonction pour afficher les infos en dessous
		wrefresh(win[1]);
		wrefresh(win[2]);
		wrefresh(win[0]);
		refresh();
		getch();
		// getchar();
		cw_exec_process(proc); // fonction qui itere sur liste des process pour exec ou non
		c_check = cw_cycles_checks(proc);
		proc->c++;
	}
	delwin(win[0]);
	delwin(win[1]);
	delwin(win[2]);
	endwin();
	return (1);
}
