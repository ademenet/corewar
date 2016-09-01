/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_load_instructions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/12 11:52:12 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

int				cw_biggest_num(t_proc *proc)
{
	int			i;
	int			num;
	int			ret;


	i = 0;
	num = proc->championsp[i].num;
	while (proc->championsp[i].num)
	{
		if (num < proc->championsp[i].num && proc->champions[i]->insert)
		{
			num = proc->championsp[i].num
			ret = i;
		}
		i++;
	}
	return (ret)
}

int				cw_load_ins_mem(t_proc *proc)
{
	int			cnt;
	int			i;
	int			cnt2;
	t_champion	tmp;
	t_p			*last;

	cnt = 0;
	i = 0;
	cnt2 = 0;
	while (++cnt2 < proc->nb_proc)
	{
		tmp = proc->champions[cw_biggest_num(proc)];
		lst_add(&proc->process, lst_new(tmp.id_champion));
		last = lst_last(proc->process);
		last->reg[0][0] = tmp->num >> 24;
		last->reg[0][1] = tmp->num >> 16;
		last->reg[0][2] = tmp->num >> 8;
		last->reg[0][3] = tmp->num;
		ft_memcpy(&(proc->mem[cnt * MEM_SIZE / proc.nb_proc]),
		tmp.ins, tmp.header->prog_size);
		tmp.pc_origin = cnt * MEM_SIZE / proc.nb_proc;
		free(tmp.insert);
		tmp.insert = NULL;
		i++;
		cnt++;
	}
	return (1);
}
