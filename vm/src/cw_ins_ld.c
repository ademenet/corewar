/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_ld.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:11:59 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/02 11:37:19 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Cette instruction prend 2 paramètres, le deuxième est forcément un
** registre (pas le PC). Elle load la valeur du premier paramètre dans
** le registre. Cette opération modifie le carry.
*/

int			cw_ins_ld_size(t_ocp *ocp)
{
	return (size);
}

int			cw_ins_ld(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{


	// Pour load la valeur dans le registre :
	tmp->reg[proc->mem[tmp->pc + 4] - 1][0] = param[2] >> 24;
	tmp->reg[proc->mem[tmp->pc + 4] - 1][1] = param[2] >> 16;
	tmp->reg[proc->mem[tmp->pc + 4] - 1][2] = param[2] >> 8;
	tmp->reg[proc->mem[tmp->pc + 4] - 1][3] = param[2];
	tmp->carry = tmp->carry == 0 ? 1 : 0;
	return (cw_ins_ld_size(ocp));
}
