/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_or.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 12:57:01 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/03 17:23:50 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Même que and mais avec le ou ( | du c).
*/

void	cw_exec_or(t_champion *tmp, unsigned int total, unsigned int p[3])
{
	tmp->reg[p[2] - 1][0] = total >> 24;
	tmp->reg[p[2] - 1][1] = total >> 16;
	tmp->reg[p[2] - 1][2] = total >> 8;
	tmp->reg[p[2] - 1][3] = total;
	if (total == (unsigned int)tmp->reg[p[2] - 1])
		tmp->carry = tmp->carry == 0 ? 1 : 0;
}

int			cw_ins_or(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	p_sze[3];
	unsigned int	p[3];
	unsigned int	total;

	p_sze[0] = cw_ins_param_sze(ocp->first, 4);
	p_sze[1] = cw_ins_param_sze(ocp->second, 4);
	p_sze[2] = cw_ins_param_sze(ocp->third, 4);
	if (ocp->first == REG_CODE)
		p[0] = cw_get_data_reg(tmp, proc->mem[(tmp->pc + 2) % MEM_SIZE] - 1);
	else if (ocp->first == DIR_CODE)
		p[0] = cw_get_data_dir(proc, tmp, tmp->pc + 2, 4);
	else if (ocp->first == IND_CODE)
		p[0] = cw_get_data_ind(proc, tmp, tmp->pc + 2);
	if (ocp->second == REG_CODE)
		p[1] = cw_get_data_reg(tmp,
			proc->mem[(tmp->pc + 2 + p_sze[0]) % MEM_SIZE] - 1);
	else if (ocp->second == DIR_CODE)
		p[1] = cw_get_data_dir(proc, tmp, tmp->pc + 2 + p_sze[0], 4);
	else if (ocp->second == IND_CODE)
		p[1] = cw_get_data_ind(proc, tmp, tmp->pc + 2 + p_sze[0]);
	p[2] = proc->mem[(tmp->pc + 2 + p_sze[0] + p_sze[1]) % MEM_SIZE];
	total = p[1] | p[0];
	cw_exec_or(tmp, total, p);
	return (2 + p_sze[0] + p_sze[1] + p_sze[2]);
}
