/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:16:29 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/31 14:04:59 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Cette instruction n’est pas suivie d’octet pour décrire les paramètres.
** Elle prend toujours un index et crée un nouveau programme qui s’exécute
** à partir de l’adresse : (PC + (premier paramètre % IDX_MOD)).
** Fork %34 crée un nouveau programme. Le nouveau programme
** hérite des différents états du père.
*/

void		cw_ins_fork_db(t_proc *proc, t_champion *tmp, t_ocp *ocp,
			short int p)
{
	ft_printf("P%5d | %s %d (%d)\n", tmp->idp,
		"fork", p, (tmp->pc + (p % IDX_MOD)) % MEM_SIZE);
}

void		cw_ins_fork_duplicate_reg(t_champion *new, t_champion *old)
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

void		cw_ins_fork_init(t_proc *proc)
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

int			cw_ins_fork(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	short int	p;
	t_champion	*new;

	p = (short int)cw_get_data_dir(proc, tmp, (tmp->pc + 1) % MEM_SIZE, 2);
	new = cw_lst_new(tmp->header, proc->champions->num);
	proc->champions = cw_lst_push(proc, new);
	cw_ins_fork_duplicate_reg(proc->champions, tmp);
	proc->champions->pc_origin = tmp->pc_origin;
	proc->champions->pc = (tmp->pc + (unsigned short)(p % IDX_MOD)) % MEM_SIZE;
	proc->champions->carry = tmp->carry;
	cw_ins_fork_init(proc);
	proc->champions->lives = 0;
	proc->champions->id = tmp->id;
	proc->nb_proc++;
	proc->champions->idp = proc->nb_proc;
	proc->champions->is_champ = 0;
	if (g_bon['d'] == 1)
		cw_ins_fork_db(proc, tmp, ocp, p);
	return (3);
}
