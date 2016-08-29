/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_st.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:12:38 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/24 18:43:56 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Cette instruction prend 2 paramètres. Elle store (REG_SIZE OCTET)la valeur
** du premier argument (toujours un registre) dans le second.
*/

void		cw_ins_st_display(t_proc *proc, t_champion *tmp, unsigned int p,
			unsigned int ind_reg)
{
	unsigned int	i;

	i = -1;
	if (g_bon['v'])
	{
		while (++i < REG_SIZE)
		{
			cw_vizualizer_print(proc, tmp, (tmp->pc + p + i) % MEM_SIZE,
				tmp->reg[ind_reg][i]);
		}
	}
	else if (g_bon['d'])
		ft_printf("P%5d | %s r%d %d\n", tmp->idp, "st", ind_reg + 1, p);
}

int			cw_ins_st_pro(t_proc *proc, t_champion *tmp, t_ocp *ocp,
			unsigned int p_sze[2])
{
	if ((proc->mem[(tmp->pc + 2 + p_sze[0]) % MEM_SIZE] - 1 < 0 &&
		ocp->second == REG_CODE) || ocp->first == 0 || ocp->second == 0)
		return (1);
	return (0);
}

int			cw_ins_st(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	p_sze[2];
	short int		p[2];
	unsigned int	ind_reg;
	unsigned int	i;

	i = -1;
	p_sze[0] = 1;
	p_sze[1] = cw_ins_param_sze(ocp->second, 2);
	ind_reg = proc->mem[(tmp->pc + 2) % MEM_SIZE] - 1;
	if ((int)ind_reg < 0 || cw_ins_st_pro(proc, tmp, ocp, p_sze))
		return (2 + p_sze[0] + p_sze[1]);
	p[0] = cw_get_data_reg(tmp, ind_reg);
	if (ocp->second == REG_CODE)
		p[1] = proc->mem[(tmp->pc + 2 + p_sze[0]) % MEM_SIZE] - 1;
	else if (ocp->second == IND_CODE)
		p[1] = ((short)cw_get_data_dir(proc, tmp, tmp->pc + 3, 2)) % IDX_MOD;
	while (++i < REG_SIZE)
	{
		if (ocp->second == IND_CODE)
			proc->mem[(tmp->pc + p[1] + i) % MEM_SIZE] = tmp->reg[ind_reg][i];
		else if (ocp->second == REG_CODE)
			tmp->reg[p[1]][i] = tmp->reg[ind_reg][i];
	}
	cw_ins_st_display(proc, tmp, p[1], ind_reg);
	return (2 + p_sze[0] + p_sze[1]);
}