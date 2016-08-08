/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_ldi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:15:25 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/08 15:12:54 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Cette opération modifie le carry. ldi 3,%4,r1 lit IND_SIZE octets a
** l’adresse : (PC + (3 % IDX_MOD)) ajoute 4 à cette valeur. On nommera S
** cette somme. On lit REG_SIZE octet à l’adresse (PC + (S % IDX_MOD))
** que l’on copie dans r1. Les paramètres 1 et 2 sont des index.
** T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG
*/

int			cw_ins_ldi_secondparamhandler(t_proc *proc, t_champion *tmp,
										char ocp, unsigned int p_sze)
{
	if (ocp == REG_CODE)
	{
		return (cw_get_data_reg(tmp,
				proc->mem[(tmp->pc + 2 + p_sze) % MEM_SIZE] - 1) % IDX_MOD);
	}
	else if (ocp == DIR_CODE)
	{
		return (cw_get_data_dir(proc, tmp,
				((tmp->pc + 2 + p_sze) % IDX_MOD) % MEM_SIZE, 2));
	}
	return (0);
}

int			cw_ins_ldi_firstparamhandler(t_proc *proc, t_champion *tmp,
										char ocp)
{
	if (ocp == REG_CODE)
		return (cw_get_data_reg(tmp,
				proc->mem[(tmp->pc + 2) % MEM_SIZE] - 1) % IDX_MOD);
	else if (ocp == DIR_CODE)
		return (cw_get_data_dir(proc, tmp,
				(((tmp->pc + 2) % MEM_SIZE) % IDX_MOD), 2));
	else if (ocp == IND_CODE)
	{
		return (cw_get_data_ind(proc, tmp,
			((tmp->pc + 2) % MEM_SIZE) % IDX_MOD));
	}
	return (0);
}

int			cw_ins_ldi(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	p[3];
	unsigned int	p_sze[3];
	unsigned int	ret;

	p_sze[0] = cw_ins_param_sze(ocp->first, 2);
	p_sze[1] = cw_ins_param_sze(ocp->second, 2);
	p_sze[2] = cw_ins_param_sze(ocp->third, 2);
	if (ocp->third != REG_CODE)
		return (2 + p_sze[0] + p_sze[1] + p_sze[2]);
	p[0] = cw_ins_ldi_firstparamhandler(proc, tmp, ocp->first);
	p[1] = cw_ins_ldi_secondparamhandler(proc, tmp, ocp->second, p_sze[0]);
	p[2] = proc->mem[(tmp->pc + 2 + p_sze[0] + p_sze[1]) % MEM_SIZE] % IDX_MOD;
	ret = cw_get_data_dir(proc, tmp,
		(tmp->pc + ((p[0] + p[1]) % IDX_MOD)) % MEM_SIZE, 4);
	tmp->reg[p[2] - 1][0] = ret >> 24;
	tmp->reg[p[2] - 1][1] = ret >> 16;
	tmp->reg[p[2] - 1][2] = ret >> 8;
	tmp->reg[p[2] - 1][3] = ret;
	tmp->carry = tmp->carry == 0 ? 1 : 0;
	return (2 + p_sze[0] + p_sze[1] + p_sze[2]);
}
