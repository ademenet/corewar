/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_load_instructions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/01 18:08:19 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

int				cw_biggest_num(t_proc *proc)
{
	int			i;
	int			num;
	int			ret;


	i = 0;
	ret = 0;
	num = proc->champions[i].num;
	while (proc->champions[i].num)
	{
		printf("%d\n", proc->champions[i].num);
		if (num < proc->champions[i].num && proc->champions[i].insert)
		{
			num = proc->champions[i].num;
			ret = i;
		}
		i++;
	}
	printf("%d\n", ret);
	printf("%d\n", proc->champions[i].num);
	return (ret);
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
	cnt2 = -1;
	while (++cnt2 < proc->nb_proc)
	{
		tmp = proc->champions[cw_biggest_num(proc)];
		cw_lst_add(&proc->process, cw_lst_new(tmp.id_champion));
		last = cw_lst_last(proc->process);
		last->reg[0][0] = tmp.num >> 24;
		last->reg[0][1] = tmp.num >> 16;
		last->reg[0][2] = tmp.num >> 8;
		last->reg[0][3] = tmp.num;
		ft_memcpy(&(proc->mem[cnt * MEM_SIZE / proc->nb_proc]),
		tmp.insert, tmp.header->prog_size);
		free(tmp.insert);
		tmp.insert = NULL;
		i++;
		cnt++;
	}
	return (1);
}
