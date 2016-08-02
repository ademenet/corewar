/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_sti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:16:01 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/02 16:53:33 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** sti r2,%4,%5 sti copie REG_SIZE octet de r2 a l’adresse (4 + 5)
** Les paramètres 2 et 3 sont des index. Si les paramètres 2 ou 3
** sont des registres, on utilisera leur contenu comme un index.
*/

void	cw_exec_sti(t_proc *proc, t_champion *tmp, unsigned int p[3])
{
	unsigned int	i;

	i = -1;
	while (++i < REG_SIZE)
		proc->mem[(tmp->pc + p[1] + p[2] + i) % MEM_SIZE] =
		tmp->reg[p[0] - 1][i];
}

int		cw_ins_sti(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	p_sze[3];
	unsigned int	p[3];

	p_sze[0] = cw_ins_param_sze(ocp->first, 2);
	p_sze[1] = cw_ins_param_sze(ocp->second, 2);
	p_sze[2] = cw_ins_param_sze(ocp->third, 2);

	p[0] = proc->mem[tmp->pc + 2];
	if (ocp->second == REG_CODE)
		p[1] = cw_get_data_reg(tmp, proc->mem[tmp->pc + 2 + p_sze[0]] - 1);
	else if (ocp->second == DIR_CODE)
		p[1] = cw_get_data_dir(proc, tmp, tmp->pc + 2 + p_sze[0], 2) %IDX_MOD;
	else if (ocp->second == IND_CODE)
		p[1] = cw_get_data_ind(proc, tmp, tmp->pc + 2 + p_sze[0]) % IDX_MOD;
	if (ocp->third == REG_CODE)
		p[2] = cw_get_data_reg(
		tmp, proc->mem[tmp->pc + 2 + p_sze[0] + p_sze[1]] - 1);
	else if (ocp->third == DIR_CODE)
		p[2] = cw_get_data_dir(
		proc, tmp, tmp->pc + 2 + p_sze[0] + p_sze[1], 2) % IDX_MOD;
	if (p[0] < 1 || p[0] > REG_NUMBER || ocp->third == IND_CODE)
		return (1 + 1 + p_sze[0] + p_sze[1] + p_sze[2]);
	cw_exec_sti(proc, tmp, p);
	return (1 + 1 + p_sze[0] + p_sze[1] + p_sze[2]);
}
