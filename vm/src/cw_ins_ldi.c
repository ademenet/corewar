/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_ldi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:15:25 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/03 16:32:38 by ademenet         ###   ########.fr       */
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
	// unsigned int	p[2];
	unsigned int	psze[3];

	psze[0] = cw_ins_param_sze(ocp->first, 2);
	psze[1] = cw_ins_param_sze(ocp->second, 2);
	psze[2] = cw_ins_param_sze(ocp->third, 2);

	mvprintw(0, 210, "%u %u %u", psze[0], psze[1], psze[2]);
	// if (ocp->first == REG_CODE)
	// 	p[0] = cw_get_data_reg(tmp, proc->mem[(tmp->pc + 2) % MEM_SIZE])
	// 		% IDX_MOD;
	// else if (ocp->first == DIR_CODE)
	// 	p[0] = cw_get_data_dir();
	// else if (ocp->first == IND_CODE)
	// 	p[0] = cw_get_data_ind();
	// if (ocp->second == DIR_CODE)
	// 	p[1] = cw_get_data_dir()
	// else if (ocp->second == REG_CODE)
	// 	p[1] = cw_get_data_reg(tmp, )
	// if (ocp->third != REG_CODE) // gestion des erreurs

	tmp->carry = tmp->carry == 0 ? 1 : 0;
	return (1);
}
