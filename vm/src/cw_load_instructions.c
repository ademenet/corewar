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

int				cw_load_ins_mem(t_proc *proc)
{
	int			cnt;
	int			i;
	t_p			*tmp;

	cnt = 0;
	i = 0;
	tmp = 
	while (tmp)
	{
		ft_memcpy(&(proc->mem[cnt * MEM_SIZE / proc.nb_proc]),
		tmp.ins, tmp.header->prog_size);
		tmp.pc_origin = cnt * MEM_SIZE / nb_champ;
		free(tmp.ins);
		tmp.ins = NULL;
		tmp = tmp.next;
		cnt++;
	}
	return (1);
}
