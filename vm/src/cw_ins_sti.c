/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_sti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:16:01 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/26 13:42:41 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** sti r2,%4,%5 sti copie REG_SIZE octet de r2 a l’adresse (4 + 5)
** Les paramètres 2 et 3 sont des index. Si les paramètres 2 ou 3
** sont des registres, on utilisera leur contenu comme un index.
*/

//unsigned int		cw_get_ins_param(t_champion *champ, int ocp_code, )

unsigned int		cw_get_data_reg(t_champion *champ, unsigned int reg)
{
	unsigned int	ret;

	ret = champ->reg[reg][0] << 24;
	ret = champ->reg[reg][1] << 16;
	ret = champ->reg[reg][2] << 8;
	ret = champ->reg[reg][3];
	return (ret);
}

int					cw_ins_sti(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	p_sze[3];
	unsigned int	param[3];
	unsigned int	res = 0;
	unsigned int	i;
	int				j;
	i = -1;
	ft_printf("je rentre dans sti\n");
	p_sze[0] = cw_ins_param_sze(ocp->first, 2);
	p_sze[1] = cw_ins_param_sze(ocp->second, 2);
	p_sze[2] = cw_ins_param_sze(ocp->third, 2);

	param[0] = proc->mem[tmp->pc + 1 + 1];
	

	if (ocp->second == REG_CODE)
		param[1] = cw_get_data_reg(tmp, proc->mem[tmp->pc + 1 + 1 + p_sze[0]] - 1);
	else if (ocp->second == DIR_CODE)
		param[1] = (proc->mem[tmp->pc + 1 + 1 + p_sze[0]] << 8 | proc->mem[tmp->pc + 1 + 1 + p_sze[0] + 1]);
	else if (ocp->second == IND_CODE)
	{
		j = (proc->mem[tmp->pc + 1 + 1 + p_sze[0]] << 8 | proc->mem[tmp->pc + 1 + 1 + p_sze[0] + 1]) % IDX_MOD;
		param[1] = proc->mem[tmp->pc + j] << 24
		| proc->mem[tmp->pc + j + 1] << 16
		| proc->mem[tmp->pc + j + 2] << 8
		| proc->mem[tmp->pc + j + 3];
	}




	if (ocp->third == REG_CODE)
		param[2] = cw_get_data_reg(tmp, proc->mem[tmp->pc + 1 + 1 + p_sze[0] + p_sze[1]] - 1);
	else if (ocp->third == DIR_CODE)
		param[2] = (proc->mem[tmp->pc + 1 + 1 + p_sze[0] + p_sze[1]] << 8 | proc->mem[tmp->pc + 1 + 1 + p_sze[0] + p_sze[1] + 1]);





	if (ocp->second == REG_CODE && ocp->third == REG_CODE)
		res = param[1] + param[2];
	else
		res = (param[1] + param[2]) % IDX_MOD;
	if (param[0] < 1 || param[0] > REG_NUMBER)
		return (1 + 1 + p_sze[0] + p_sze[1] + p_sze[2]);
	while (++i < REG_SIZE)
		proc->mem[(tmp->pc + res + i) % MEM_SIZE] = tmp->reg[param[0] - 1][i];
	ft_printf("param 1 : %u, param 2 : %u, param 3 : %u, res : %u\n", param[0], param[1], param[2], res);
	return (1 + 1 + p_sze[0] + p_sze[1] + p_sze[2]);
}





















