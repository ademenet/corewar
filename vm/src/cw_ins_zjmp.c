/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_zjmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:14:38 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/20 18:44:57 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Cette instruction n’est pas suivie d’octet pour décrire les paramètres.
** Elle prend toujours un index (IND_SIZE) et fait un saut à cet index si
** le carry est à un. Si le carry est nul, zjmp ne fait rien mais
** consomme le même temps.
*/

int			cw_ins_zjmp(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	short int	p;

	p = (short int)cw_get_data_dir(proc, tmp, (tmp->pc + 1) % MEM_SIZE, 2);
	if (tmp->carry == 1)
	{
		if (g_bon['d'])
			ft_printf("P%5d | %s %d OK\n", tmp->idp,
			g_op[proc->mem[tmp->pc] - 1].name, p);
		return (p % IDX_MOD);
	}
	if (g_bon['d'])
		ft_printf("P%5d | %s %d FAILED\n", tmp->idp, "zjmp", p);
	return (3);
}
