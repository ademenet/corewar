/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_vizualizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/26 15:10:22 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
**
*/

int			cw_vizualizer_pcprint(t_proc *proc, int *i)
{
	t_champion	*tmp;

	tmp = proc->champions;
	while (tmp)
	{
		if (*i == tmp->pc)
			return (1);
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

	i = 0;
	while (i < MEM_SIZE)
	{
		i % 64 == 0 ? wprintw(win, "\n") : wprintw(win, " ");
		if (cw_vizualizer_pcprint(proc, &i)) // partiellement faux, car seulement pour un PC ! Marche pas :/
		{
			wattron(win, COLOR_PAIR(1));
			wprintw(win, "%.2hhx", proc->mem[i]);
			wattroff(win, COLOR_PAIR(1));
		}
		else
			wprintw(win, "%.2hhx", proc->mem[i]);
		refresh();
		i++;
	}
}

/*
** À compiler avec "gcc -lncurses ..."
*/

void		cw_vizualizer(t_proc *proc)
{
	WINDOW	*win;
	// int		ch; // pour le controle plus tard ==> il faut d'abord faire en sorte de l'appeler en params

	initscr();
	cbreak();
	win = newwin(80, 200, 0, 0);
	refresh();
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_GREEN);
	cw_vizualizer_memprint(proc, win);
	wrefresh(win);
	getch();
	delwin(win);
	endwin();
}
