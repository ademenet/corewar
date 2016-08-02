/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_xor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 12:57:24 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/26 15:17:47 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Même que and mais avec le ou exclusif (^ du c).
*/

int			cw_ins_xor(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	p_sze[3];
	unsigned int	p[3];
	unsigned int	total;
	total = 0;
	p_sze[0] = cw_ins_param_sze(ocp->first, 4);
	p_sze[1] = cw_ins_param_sze(ocp->second, 4);
	p_sze[2] = cw_ins_param_sze(ocp->third, 4);

	if (ocp->first == REG_CODE)
		p[0] = cw_get_data_reg(tmp, proc->mem[tmp->pc + 2] - 1);
	else if (ocp->first == DIR_CODE)
		p[0] = cw_get_data_dir(proc, tmp, tmp->pc + 2, 4);
	else if (ocp->first == IND_CODE)
		p[0] = cw_get_data_ind(proc, tmp, tmp->pc + 2) % IDX_MOD;
	if (ocp->second == REG_CODE)
		p[1] = cw_get_data_reg(tmp, proc->mem[tmp->pc + 2 + p_sze[0]] - 1);
	else if (ocp->second == DIR_CODE)
		p[1] = cw_get_data_dir(proc, tmp, tmp->pc + 2 + p_sze[0], 4);
	else if (ocp->second == IND_CODE)
		p[1] = cw_get_data_ind(proc, tmp, tmp->pc + 2 + p_sze[0]) % IDX_MOD;

	p[2] = proc->mem[tmp->pc + 2 + p_sze[0] + p_sze[1]];
	total = p[1] ^ p[0];
	tmp->reg[p[2] - 1][0] = total >> 24;
	tmp->reg[p[2] - 1][1] = total >> 16;
	tmp->reg[p[2] - 1][2] = total >> 8;
	tmp->reg[p[2] - 1][3] = total;
	return (2 + p_sze[0] + p_sze[1] + p_sze[2]);
}
