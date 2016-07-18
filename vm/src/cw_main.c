/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/11 15:54:35 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int				main(int ac, char **av)
{
	t_proc		proc;
	int			i;

	i = -1;
	while(++i < 4)
		proc.champions[i] = NULL;
	if (!cw_param(av, ac, &proc))
		return (ft_printf("Fail !\n"));
	i = 4;
	while(proc.champions[--i] && i >= 0)
	ft_printf("%u %s %u %s\n", proc.champions[i]->header->magic, proc.champions[i]->header->prog_name,
		proc.champions[i]->header->prog_size, proc.champions[i]->header->comment);
	return (0);
}