/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:16:29 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/12 15:41:21 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Cette instruction n’est pas suivie d’octet pour décrire les paramètres.
** Elle prend toujours un index et crée un nouveau programme qui s’exécute
** à partir de l’adresse : (PC + (premier paramètre % IDX_MOD)). Fork %34 crée
** un nouveau programme. Le nouveau programme hérite des di érents états
** du père.
*/

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

int			cw_ins_fork(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	short	p;

	p = (short)cw_get_data_dir(proc, tmp, (tmp->pc + 1) % MEM_SIZE, 2);
	cw_lst_push(&proc->champions, cw_lst_new(tmp->header, tmp->num));
	proc->champions->ins = NULL;
	proc->champions->pc_origin = tmp->pc_origin;
	proc->champions->pc = (tmp->pc + (unsigned short)(p % IDX_MOD)) % MEM_SIZE;
	proc->champions->inst_c = 0;
	proc->champions->lives = 0;
	proc->champions->id = tmp->id;
	return (3);
}
