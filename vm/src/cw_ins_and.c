/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_and.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:14:06 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/26 15:17:35 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** p1 & p2 -> p3. Le paramètre 3 est toujours un registre. Cette opération
** modifie le carry.
*/

int			cw_ins_and(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{

	unsigned int	p_sze[3];
	unsigned int	p[3];
	unsigned int	total;
	p_sze[0] = cw_ins_param_sze(ocp->first, 4);
	p_sze[1] = cw_ins_param_sze(ocp->second, 4);
	p_sze[2] = cw_ins_param_sze(ocp->third, 4);

	if (ocp->first == REG_CODE)
		p[0] = cw_get_data_reg(tmp, proc->mem[tmp->pc + 2] - 1);
	else if (ocp->first == DIR_CODE)
		p[0] = cw_get_data_dir(proc, tmp, tmp->pc + 2, 4);
	else if (ocp->first == IND_CODE)
		p[0] = cw_get_data_ind(proc, tmp, tmp->pc + 2);
	if (ocp->second == REG_CODE)
		p[1] = cw_get_data_reg(tmp, proc->mem[tmp->pc + 2 + p_sze[0]] - 1);
	else if (ocp->second == DIR_CODE)
		p[1] = cw_get_data_dir(proc, tmp, tmp->pc + 2 + p_sze[0], 4);
	else if (ocp->second == IND_CODE)
		p[1] = cw_get_data_ind(proc, tmp, tmp->pc + 2 + p_sze[0]);
	p[2] = proc->mem[tmp->pc + 2 + p_sze[0] + p_sze[1]];
	mvprintw(6, 210, "p0 : %d, p1 : %d et total :%d\n",p[0], p[1], total);
	total = p[1] & p[0];
	mvprintw(10, 210, "p0 : %d, p1 : %d et total :%d\n",p[0], p[1], total);
	ft_printf("reg avant stock : %s\n", tmp->reg[p[2] - 1]);
//
	tmp->reg[p[2] - 1][0] = total >> 24;
	tmp->reg[p[2] - 1][1] = (total << 8) >> 24;
	tmp->reg[p[2] - 1][2] = (total << 16) >> 24;
	tmp->reg[p[2] - 1][3] = (total << 24) >> 24;
	mvprintw(5, 210,"reg :%c, %c, %c, %c avant stockage\n", tmp->reg[p[2] - 1][0],tmp->reg[p[2] - 1][1],tmp->reg[p[2] - 1][2],tmp->reg[p[2] - 1][3]);
	//ft_printf("reg apres stock : %s\n", tmp->reg[p[2] - 1]);
	mvprintw(20, 210,"reg :%s apres stockage\n", tmp->reg[p[2] - 1]);
	return (2 + p_sze[0] + p_sze[1] + p_sze[2]);
}
