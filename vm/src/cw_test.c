/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/25 14:35:35 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "../inc/corewar.h"

/*
** À compiler avec "gcc -lncurses ..."
*/

void		cw_mem_vizualizer(t_proc *proc)
{
	WINDOW	*win;
	int		i;

	initscr();
	win = newwin(80, 200, 0, 0);
	refresh();
	noecho();
	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			wprintw(win, "\n");
		wprintw(win, "%.2hhx ", proc->mem[i]);
		i++;
	}
	wrefresh(win);
	getch();
	delwin(win);
	endwin();
}

int			main(void)
{
	t_proc	proc;

	proc.mem[0] = 0x01;
	proc.mem[1] = 0xe0;
	proc.mem[2] = 0x00;
	proc.mem[3] = 0x00;
	proc.mem[4] = 0x00;
	proc.mem[5] = 0x02;

	cw_processor(&proc);
	return (0);
}
