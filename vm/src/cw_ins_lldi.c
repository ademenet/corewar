/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_lldi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 16:07:34 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/12 16:15:50 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Comme ldi sans le %IDX_MOD Cette opération modifie le carry.
*/

int			cw_ins_lldi_secondparamhandler(t_proc *proc, t_champion *tmp,
										char ocp, unsigned int p_sze)
{
	if (ocp == REG_CODE && proc->mem[(tmp->pc + 2 + p_sze) % MEM_SIZE] > 0 &&
		proc->mem[(tmp->pc + 2 + p_sze) % MEM_SIZE] <= REG_NUMBER)
		return (cw_get_data_reg(tmp,
				proc->mem[(tmp->pc + 2 + p_sze) % MEM_SIZE] - 1));
	else if (ocp == DIR_CODE)
	{
		return (cw_get_data_dir(proc, tmp,
				((tmp->pc + 2 + p_sze)) % MEM_SIZE, 2));
	}
	return (0);
}

int			cw_ins_lldi_firstparamhandler(t_proc *proc, t_champion *tmp,
										char ocp)
{
	if (ocp == REG_CODE && proc->mem[(tmp->pc + 2) % MEM_SIZE] > 0 &&
		proc->mem[(tmp->pc + 2) % MEM_SIZE] <= REG_NUMBER)
		return (cw_get_data_reg(tmp,
				proc->mem[(tmp->pc + 2) % MEM_SIZE] - 1));
	else if (ocp == DIR_CODE)
		return (cw_get_data_dir(proc, tmp,
				(((tmp->pc + 2) % MEM_SIZE)), 2));
	else if (ocp == IND_CODE)
	{
		return (cw_get_data_ind(proc, tmp,
				((tmp->pc + 2) % MEM_SIZE)));
	}
	return (0);
}

int			cw_ins_lldi(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	p[3];
	unsigned int	p_sze[3];
	unsigned int	ret;

	p_sze[0] = cw_ins_param_sze(ocp->first, 2);
	p_sze[1] = cw_ins_param_sze(ocp->second, 2);
	p_sze[2] = cw_ins_param_sze(ocp->third, 2);
	if (ocp->third != REG_CODE)
		return (2 + p_sze[0] + p_sze[1] + p_sze[2]);
	p[0] = cw_ins_lldi_firstparamhandler(proc, tmp, ocp->first);
	p[1] = cw_ins_lldi_secondparamhandler(proc, tmp, ocp->second, p_sze[0]);
	p[2] = proc->mem[(tmp->pc + 2 + p_sze[0] + p_sze[1]) % MEM_SIZE];
	ret = cw_get_data_dir(proc, tmp,
		(tmp->pc + (p[0] + p[1])) % MEM_SIZE, 4);
	if (p[2] > 0 && p[2] <= REG_NUMBER)
	{
		tmp->reg[p[2] - 1][0] = ret >> 24;
		tmp->reg[p[2] - 1][1] = ret >> 16;
		tmp->reg[p[2] - 1][2] = ret >> 8;
		tmp->reg[p[2] - 1][3] = ret;
	}
	tmp->carry = tmp->carry == 0 ? 1 : 0;
	return (2 + p_sze[0] + p_sze[1] + p_sze[2]);
}
