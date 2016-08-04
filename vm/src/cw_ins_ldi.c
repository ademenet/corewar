/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_ldi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:15:25 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/04 17:11:52 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Cette opération modifie le carry. ldi 3,%4,r1 lit IND_SIZE octets a
** l’adresse : (PC + (3 % IDX_MOD)) ajoute 4 à cette valeur. On nommera S
** cette somme. On lit REG_SIZE octet à l’adresse (PC + (S % IDX_MOD))
** que l’on copie dans r1. Les paramètres 1 et 2 sont des index.
*/

int			cw_ins_ldi(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	p[3];
	unsigned int	p_sze[3];
	unsigned int	ret;

	p_sze[0] = cw_ins_param_sze(ocp->first, 2);
	p_sze[1] = cw_ins_param_sze(ocp->second, 2);
	p_sze[2] = cw_ins_param_sze(ocp->third, 2);
	mvprintw(0, 210, "%u %u %u", p_sze[0], p_sze[1], p_sze[2]);
	if (ocp->third != REG_CODE)
		return (2 + p_sze[0] + p_sze[1] + p_sze[2]);
	if (ocp->first == REG_CODE)
		p[0] = cw_get_data_reg(tmp, proc->mem[(tmp->pc + 2) % MEM_SIZE]) % IDX_MOD;
	else if (ocp->first == DIR_CODE)
		p[0] = cw_get_data_dir(proc, tmp, (tmp->pc + 2) % IDX_MOD, 2);
	else if (ocp->first == IND_CODE)
		p[0] = cw_get_data_ind(proc, tmp, (tmp->pc + 2) % IDX_MOD);
	if (ocp->second == REG_CODE)
		p[1] = cw_get_data_reg(tmp, proc->mem[(tmp->pc + 2 + p_sze[0]) % MEM_SIZE] % IDX_MOD);
	else if (ocp->second == DIR_CODE)
		p[1] = cw_get_data_dir(proc, tmp, (tmp->pc + 2 + p_sze[0]) % IDX_MOD, 2);
	p[2] = proc->mem[(tmp->pc + 2 + p_sze[0] + p_sze[1]) % MEM_SIZE] % IDX_MOD;
	ret = cw_get_data_ind(proc, tmp, proc->mem[(p[0] + p[1]) % MEM_SIZE]) % IDX_MOD;
	tmp->reg[p[2] - 1][0] = ret >> 24;
	tmp->reg[p[2] - 1][1] = ret >> 16;
	tmp->reg[p[2] - 1][2] = ret >> 8;
	tmp->reg[p[2] - 1][3] = ret;
	tmp->carry = tmp->carry == 0 ? 1 : 0;
	return (2 + p_sze[0] + p_sze[1] + p_sze[2]);
}
