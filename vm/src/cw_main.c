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
	t_champion	*tmp;

	proc.champions = NULL;
	proc.nb_champ = 0;
	proc.dump = 0;
	if (cw_param(av, ac, &proc) <= 0)
		return (ft_printf("Fail !\n"));
	tmp = proc.champions;
	while(tmp)
	{
		ft_printf("%u %s %u %s -> %d\n", tmp->header->magic, tmp->header->prog_name,
		tmp->header->prog_size, tmp->header->comment, tmp->num);
		tmp = tmp->next;
	}
	return (0);
}