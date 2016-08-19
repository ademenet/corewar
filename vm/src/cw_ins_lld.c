/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_lld.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 16:07:31 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/19 10:23:28 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Comme ld sans le %IDX_MOD Cette opération modifie le carry.
*/

int			cw_ins_lld(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	p_sze[2];
	unsigned int    p;
	unsigned char	reg;

	p_sze[0] = cw_ins_param_sze(ocp->first, 4);
	p_sze[1] = cw_ins_param_sze(ocp->second, 4);
	if (ocp->first == DIR_CODE)
		p = cw_get_data_dir(proc, tmp, (tmp->pc + 2) % MEM_SIZE, 4);
	else if (ocp->first == IND_CODE)
		p = cw_get_data_ind(proc, tmp, (tmp->pc + 2));
	reg = proc->mem[(tmp->pc + 2 + p_sze[0]) % MEM_SIZE];
	if (ocp->first == REG_CODE || reg < 1 || reg > REG_NUMBER ||
		ocp->second != REG_CODE)
		return (2 + p_sze[0] + p_sze[1]);
	tmp->reg[reg - 1][0] = p >> 24;
	tmp->reg[reg - 1][1] = p >> 16;
	tmp->reg[reg - 1][2] = p >> 8;
	tmp->reg[reg - 1][3] = p;
	tmp->carry = p == 0 ? 1 : 0;
	return (2 + p_sze[0] + p_sze[1]);
}
