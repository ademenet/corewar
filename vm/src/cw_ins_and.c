/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_and.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:14:06 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/12 16:09:36 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** p1 & p2 -> p3. Le paramètre 3 est toujours un registre. Cette opération
** modifie le carry.
** T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG
*/

void	cw_exec_and(t_champion *tmp, unsigned int p[3], unsigned int p_sze[3])
{
	unsigned int	total;

	total = p[1] & p[0];
	if (p[2] > 0 && p[2] <= REG_NUMBER && p_sze[0] && p_sze[1] && p_sze[2])
	{
		tmp->reg[p[2] - 1][0] = total >> 24;
		tmp->reg[p[2] - 1][1] = total >> 16;
		tmp->reg[p[2] - 1][2] = total >> 8;
		tmp->reg[p[2] - 1][3] = total;
	}
	if (total == 0)
		tmp->carry = 1;
	else
		tmp->carry = 0;
}

int		cw_ins_and(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	p_sze[3];
	unsigned int	p[3];

	p_sze[0] = cw_ins_param_sze(ocp->first, 4);
	p_sze[1] = cw_ins_param_sze(ocp->second, 4);
	p_sze[2] = cw_ins_param_sze(ocp->third, 4);
	if (ocp->first == REG_CODE && proc->mem[(tmp->pc + 2) % MEM_SIZE] > 0 &&
		proc->mem[(tmp->pc + 2) % MEM_SIZE] <= REG_NUMBER)
		p[0] = cw_get_data_reg(tmp, proc->mem[(tmp->pc + 2) % MEM_SIZE] - 1);
	else if (ocp->first == DIR_CODE)
		p[0] = cw_get_data_dir(proc, tmp, (tmp->pc + 2) % MEM_SIZE, 4);
	else if (ocp->first == IND_CODE)
		p[0] = cw_get_data_ind(proc, tmp, (tmp->pc + 2) % MEM_SIZE);
	if (ocp->second == REG_CODE &&
		proc->mem[(tmp->pc + 2 + p_sze[0]) % MEM_SIZE] > 0 &&
		proc->mem[(tmp->pc + 2 + p_sze[0]) % MEM_SIZE] <= REG_NUMBER)
		p[1] = cw_get_data_reg(tmp,
			proc->mem[(tmp->pc + 2 + p_sze[0]) % MEM_SIZE] - 1);
	else if (ocp->second == DIR_CODE)
		p[1] = cw_get_data_dir(proc, tmp, tmp->pc + 2 + p_sze[0], 4);
	else if (ocp->second == IND_CODE)
		p[1] = cw_get_data_ind(proc, tmp, tmp->pc + 2 + p_sze[0]);
	p[2] = proc->mem[(tmp->pc + 2 + p_sze[0] + p_sze[1]) % MEM_SIZE];
	cw_exec_and(tmp, p, p_sze);
	return (2 + p_sze[0] + p_sze[1] + p_sze[2]);
}