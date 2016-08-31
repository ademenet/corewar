/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_lfork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 16:07:20 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/31 14:05:24 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Comme fork sans le %IDX_MOD Cette opération modifie le carry.
*/

void		cw_ins_lfork_db(t_proc *proc, t_champion *tmp, t_ocp *ocp,
			short int p)
{
	if (g_bon['d'])
		ft_printf("P%5d | %s %d (%d)\n", tmp->idp,
		g_op[proc->mem[tmp->pc] - 1].name, p, (tmp->pc + p) % MEM_SIZE);
}

void		cw_ins_lfork_duplicate_reg(t_champion *new, t_champion *old)
{
	int		i;
	int		j;

	i = 0;
	while (i < REG_NUMBER)
	{
		j = 0;
		while (j < REG_SIZE)
		{
			new->reg[i][j] = old->reg[i][j];
			j++;
		}
		i++;
	}
}

void		cw_ins_lfork_init(t_proc *proc)
{
	if (proc->mem[proc->champions->pc] > 0x00 &&
		proc->mem[proc->champions->pc] < 0x11)
	{
		proc->champions->inst_c =
			g_op[proc->mem[proc->champions->pc] - 1].cycles_nb;
		proc->champions->inst_num =
			g_op[proc->mem[proc->champions->pc] - 1].opcode;
		proc->champions->ins = (unsigned char *)1;
	}
	else
	{
		proc->champions->inst_c = 0;
		proc->champions->inst_num = 0;
		proc->champions->ins = NULL;
	}
}

int			cw_ins_lfork(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	short int	p;
	t_champion	*new;

	p = (short int)cw_get_data_dir(proc, tmp, (tmp->pc + 1) % MEM_SIZE, 2);
	new = cw_lst_new(tmp->header, proc->champions->num);
	proc->champions = cw_lst_push(proc, new);
	cw_ins_lfork_duplicate_reg(proc->champions, tmp);
	proc->champions->pc_origin = tmp->pc_origin;
	proc->champions->pc = (tmp->pc + (unsigned short)p) % MEM_SIZE;
	proc->champions->carry = tmp->carry;
	cw_ins_lfork_init(proc);
	proc->champions->lives = 0;
	proc->champions->id = tmp->id;
	proc->champions->idp = proc->nb_proc;
	proc->champions->is_champ = 0;
	proc->nb_proc++;
	cw_ins_lfork_db(proc, tmp, ocp, p);
	return (3);
}
