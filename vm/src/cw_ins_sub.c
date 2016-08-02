/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:13:18 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/02 11:11:43 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Cette instruction prend 3 registres en paramètre, soustrait
** le contenu des 2 premiers et met le résultat dans le troisième.
** Cette opération modifie le carry.
*/

int			cw_ins_sub(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	param[3];

	param[0] = cw_get_data_reg(tmp, proc->mem[tmp->pc + 2] - 1);
	param[1] = cw_get_data_reg(tmp, proc->mem[tmp->pc + 3] - 1);
	param[2] = param[0] - param[1];
	tmp->reg[proc->mem[tmp->pc + 4] - 1][0] = param[2] >> 24;
	tmp->reg[proc->mem[tmp->pc + 4] - 1][1] = param[2] >> 16;
	tmp->reg[proc->mem[tmp->pc + 4] - 1][2] = param[2] >> 8;
	tmp->reg[proc->mem[tmp->pc + 4] - 1][3] = param[2];
	tmp->carry = tmp->carry == 0 ? 1 : 0;
	return (5);
}
