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
		return (ft_printf("Success\n"));
	return (0);
}