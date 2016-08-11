/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_st.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:12:38 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/11 15:52:22 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Cette instruction prend 2 paramètres. Elle store (REG_SIZE OCTET)la valeur
** du premier argument (toujours un registre) dans le second.
*/

void		cw_ins_st_display(t_proc *proc, t_champion *tmp, unsigned int p)
{
	unsigned int	i;

	i = -1;
	while (++i < REG_SIZE)
	{
		proc->mem[(tmp->pc + p + i) % MEM_SIZE] =
		tmp->reg[proc->mem[(tmp->pc + 2) % MEM_SIZE] - 1][i];
		if (g_bon['v'])
			cw_vizualizer_print(proc, tmp, (tmp->pc + p + i) % MEM_SIZE,
				tmp->reg[proc->mem[(tmp->pc + 2) % MEM_SIZE] - 1][i]);
	}
}

int			cw_ins_st(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	p_sze[2];
	unsigned int	p[2];

	p_sze[0] = 1;
	p_sze[1] = cw_ins_param_sze(ocp->second, 2);

	p[0] = proc->mem[(tmp->pc + 2) % MEM_SIZE];
	p[0] = cw_get_data_reg(tmp, p[0] - 1);
<<<<<<< HEAD


=======
>>>>>>> fa037fefe944a6271d8c11437d2dacec4502bf8c
	if (ocp->second == REG_CODE)
		p[1] = cw_get_data_reg(tmp, proc->mem[(tmp->pc + 2 + p_sze[0])
		% MEM_SIZE] - 1);
	else if (ocp->second == IND_CODE)
<<<<<<< HEAD
		p[1] = proc->mem[(tmp->pc + 2 + p_sze[0])] % IDX_MOD;


	while (++i < REG_SIZE)
		proc->mem[(p[1] + i) % MEM_SIZE] =
		tmp->reg[proc->mem[(tmp->pc + 2) % MEM_SIZE] - 1][i];



=======
		p[1] = cw_get_data_dir(proc, tmp, tmp->pc + 2 + p_sze[0], 2) %
		IDX_MOD;
	cw_ins_st_display(proc, tmp, p[1]);
>>>>>>> fa037fefe944a6271d8c11437d2dacec4502bf8c
	if (cw_get_data_reg(tmp, proc->mem[(tmp->pc + 2) % MEM_SIZE] - 1) == 0)
		tmp->carry = 1;
	else
		tmp->carry = 0;
	return (2 + p_sze[0] + p_sze[1]);
}
