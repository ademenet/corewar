/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_sti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:16:01 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/20 18:17:55 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** sti r2,%4,%5 sti copie REG_SIZE octet de r2 a l’adresse (4 + 5)
** Les paramètres 2 et 3 sont des index. Si les paramètres 2 ou 3
** sont des registres, on utilisera leur contenu comme un index.
*/

void		cw_ins_sti_db(t_proc *proc, t_champion *tmp, t_ocp *ocp,
			unsigned int p[3])
{
	ft_printf("P%5d | %s ", tmp->idp, g_op[proc->mem[tmp->pc] - 1].name);
	ft_printf("r%d ", p[0]);
	if (ocp->second == REG_CODE)
		ft_printf("r%d ", p[1]);
	else
		ft_printf("%d ", p[1]);
	if (ocp->third == REG_CODE)
		ft_printf("r%d\n", p[2]);
	else
		ft_printf("%d\n", p[2]);
	ft_printf("%6s | -> store to %d + %d = %d (with pc and mod %d)\n",
		" ", p[1], p[2], p[1] + p[2], (tmp->pc + p[1] + p[2]) % MEM_SIZE);
}

void		cw_exec_sti(t_proc *proc, t_champion *tmp, unsigned int p[3])
{
	unsigned int	i;

	i = -1;
	while (++i < REG_SIZE)
	{
		proc->mem[(tmp->pc + p[1] + p[2] + i) % MEM_SIZE] =
		tmp->reg[p[0] - 1][i];
		if (g_bon['v'])
			cw_vizualizer_print(proc, tmp,
				(tmp->pc + p[1] + p[2] + i) % MEM_SIZE, tmp->reg[p[0] - 1][i]);
	}
}

int			cw_ins_sti(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	p_sze[3];
	unsigned int	p[3];

	p_sze[0] = cw_ins_param_sze(ocp->first, 2);
	p_sze[1] = cw_ins_param_sze(ocp->second, 2);
	p_sze[2] = cw_ins_param_sze(ocp->third, 2);
	p[0] = proc->mem[tmp->pc + 2];
	if (ocp->second == REG_CODE)
		p[1] = cw_get_data_reg(tmp, proc->mem[tmp->pc + 2 + p_sze[0]] - 1) % IDX_MOD;
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
	if (g_bon['d'] == 1)
		cw_ins_sti_db(proc, tmp, ocp, p);
	return (1 + 1 + p_sze[0] + p_sze[1] + p_sze[2]);
}
