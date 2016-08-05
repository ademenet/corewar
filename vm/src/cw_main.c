/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 10:34:15 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/01 18:01:13 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

int				main(int ac, char **av)
{
	t_proc		proc;

	proc.champions = NULL;
	proc.nb_proc = 0;
	proc.dump = 0;
	proc.nb_proc = 0;
	ft_bzero(proc.mem, MEM_SIZE);
	if (cw_param(av, ac, &proc) <= 0)
		return (ft_printf("Fail !\n"));
	cw_load_ins_mem(&proc);
	if (g_bon['v'])
		cw_vizualizer_processor(&proc);
	else
		cw_processor(&proc);
	return (0);
}
