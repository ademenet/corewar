/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_ld.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:11:59 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/02 18:00:39 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Cette instruction prend 2 paramètres, le deuxième est forcément un
** registre (pas le PC). Elle load la valeur du premier paramètre dans
** le registre. Cette opération modifie le carry.
*/

int			cw_ins_ld(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	param;
	unsigned char	reg;


	if (ocp->first == IND_CODE)
	{
		param = cw_get_data_ind(proc, tmp, (tmp->pc + 2) % MEM_SIZE);
		reg = proc->mem[(tmp->pc + 4) % MEM_SIZE];
	}
	else
	{
		param = cw_get_data_dir(proc, tmp, (tmp->pc + 2) % MEM_SIZE, 4);
		reg = proc->mem[(tmp->pc + 6) % MEM_SIZE];
	}

	mvprintw(0, 0, "%.8x & %.2hhx", param, reg);
	// Pour load la valeur dans le registre :
	tmp->reg[reg - 1][0] = param >> 24;
	tmp->reg[reg - 1][1] = param >> 16;
	tmp->reg[reg - 1][2] = param >> 8;
	tmp->reg[reg - 1][3] = param;
	tmp->carry = tmp->carry == 0 ? 1 : 0;
	return (ocp->first == IND_CODE ? 5 : 7);
}

// int            cw_ins_ld(t_proc *proc, t_champion *tmp, t_ocp *ocp)
// {
//     unsigned int    p_sze[2];
//     unsigned int    p[2];
//
//     p_sze[0] = cw_ins_param_sze(ocp->first, 4);
//     p_sze[1] = cw_ins_param_sze(ocp->second, 1);
//     if (ocp->first == DIR_CODE)
//         p[0] = cw_get_data_dir(proc, tmp, tmp->pc + 2, 4) % IDX_MOD;
//     else if (ocp->first == IND_CODE)
//         p[0] = cw_get_data_ind(proc, tmp, tmp->pc + 2) % IDX_MOD;
//     p[1] = cw_get_data_reg(tmp, proc->mem[tmp->pc + 2 + p_sze[0]] - 1);
//     if (p[1] < 1 || p[1] > REG_NUMBER || ocp->first == REG_CODE)
//         return (1 + 1 + p_sze[0] + p_sze[1]);
//     tmp->reg[proc->mem[tmp->pc + 4] - 1][0] = p[0] >> 24;
//     tmp->reg[proc->mem[tmp->pc + 4] - 1][1] = p[0] >> 16;
//     tmp->reg[proc->mem[tmp->pc + 4] - 1][2] = p[0] >> 8;
//     tmp->reg[proc->mem[tmp->pc + 4] - 1][3] = p[0];
//     tmp->carry = tmp->carry == 0 ? 1 : 0;
//     return (1 + 1 + p_sze[0] + p_sze[1]);
// }
