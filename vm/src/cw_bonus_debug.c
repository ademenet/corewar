/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_bonus_debug.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 16:01:21 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/21 15:09:02 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void		cw_bonus_debug_begin(t_proc *proc)
{
	ft_printf("Introducing contestants...\n* Player 1, weighing 617 bytes, \"helltrain\" (\"choo-choo, motherf*****s !\") !\n");
}

void		cw_bonus_db_twoparams(t_proc *proc, t_champion *tmp, t_ocp *ocp,
			int p[2])
{
	ft_printf("P%5d | %s ", tmp->idp, g_op[proc->mem[tmp->pc] - 1].name);
	if (ocp->first == REG_CODE)
		ft_printf("r%d ", p[0]);
	else
		ft_printf("%d ", p[0]);
	if (ocp->second == REG_CODE)
		ft_printf("r%d\n", p[1]);
	else
		ft_printf("%d\n", p[1]);
}
