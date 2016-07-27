/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 10:34:15 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/27 16:56:28 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

int			cw_error_msg(char *msg)
{
	ft_printf("%s\n", msg);
	return (0);
}

int				cw_invert_endian(int x)
{
	x = ((x >> 24) & 0xff) | ((x >> 8) & 0xff00) | ((x << 8) & 0xff0000)
		| ((x << 24) & 0xff000000);
	return (x);
}

int				main(int ac, char **av)
{
	t_proc		proc;

	proc.champions = NULL;
	proc.nb_proc = 0;
	proc.dump = 0;
	ft_bzero(proc.mem, MEM_SIZE);
	if (cw_param(av, ac, &proc) <= 0)
		return (ft_printf("Fail !\n"));
	cw_load_ins_mem(&proc);
	cw_vizualizer_processor(&proc);
	return (0);
}
