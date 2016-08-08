/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_and.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:14:06 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/08 17:11:06 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** p1 & p2 -> p3. Le paramètre 3 est toujours un registre. Cette opération
** modifie le carry.
** T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG
*/

void	cw_exec_and(t_champion *tmp, unsigned int total, unsigned int p[3])
{
	tmp->reg[p[2] - 1][0] = total >> 24;
	tmp->reg[p[2] - 1][1] = total >> 16;
	tmp->reg[p[2] - 1][2] = total >> 8;
	tmp->reg[p[2] - 1][3] = total;

	mvprintw(22, 210, "total : %u", total);
	mvprintw(23, 210, "(unsigned int)tmp->reg[p[2] - 1] : %u", (unsigned int)tmp->reg[p[2] - 1]);
	// mvprintw(23, 210, "tmp->reg[p[2] - 1] : %.2llx", tmp->reg[p[2] - 1]);

	if (total == 0) // si le resultat = le contenu du reg ???
		tmp->carry = tmp->carry == 0 ? 1 : 0;
}

int			cw_ins_and(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	p_sze[3];
	unsigned int	p[3];
	unsigned int	total;

	total = 0;
	// on recup les tailles
	p_sze[0] = cw_ins_param_sze(ocp->first, 4);
	p_sze[1] = cw_ins_param_sze(ocp->second, 4);
	p_sze[2] = cw_ins_param_sze(ocp->third, 4);
	// convertit 1er param
	if (ocp->first == REG_CODE)
		p[0] = cw_get_data_reg(tmp, proc->mem[(tmp->pc + 2) % MEM_SIZE] - 1);
	else if (ocp->first == DIR_CODE)
		p[0] = cw_get_data_dir(proc, tmp, tmp->pc + 2, 4);
	else if (ocp->first == IND_CODE)
		p[0] = cw_get_data_ind(proc, tmp, tmp->pc + 2);
	// convertit le 2eme param
	if (ocp->second == REG_CODE)
		p[1] = cw_get_data_reg(tmp,
			proc->mem[(tmp->pc + 2 + p_sze[0]) % MEM_SIZE] - 1);
	else if (ocp->second == DIR_CODE)
		p[1] = cw_get_data_dir(proc, tmp, tmp->pc + 2 + p_sze[0], 4);
	else if (ocp->second == IND_CODE)
		p[1] = cw_get_data_ind(proc, tmp, tmp->pc + 2 + p_sze[0]);
	// le 3eme param est toujours un registre : p[2] = numero du registre
	p[2] = proc->mem[(tmp->pc + 2 + p_sze[0] + p_sze[1]) % MEM_SIZE];
	// total = p1 and p0
	total = p[1] & p[0];
	mvprintw(8, 210, "carry av : %d", tmp->carry);
	cw_exec_and(tmp, total, p);
	mvprintw(9, 210, "p0 : %u", p[0]);
	mvprintw(10, 210, "p1 : %u", p[1]);
	mvprintw(11, 210, "p2 : %u", p[2]);
	mvprintw(12, 210, "total : %u", total);
	mvprintw(13, 210, "reg : %u", tmp->reg[p[2] - 1][0]);
	mvprintw(14, 210, "reg : %u", tmp->reg[p[2] - 1][1]);
	mvprintw(15, 210, "reg : %u", tmp->reg[p[2] - 1][2]);
	mvprintw(16, 210, "reg : %u", tmp->reg[p[2] - 1][3]);
	mvprintw(20, 210, "carry ap : %d", tmp->carry);
	return (2 + p_sze[0] + p_sze[1] + p_sze[2]);
}
