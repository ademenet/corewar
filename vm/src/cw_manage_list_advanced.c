/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_manage_list_advanced.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/31 15:46:25 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

t_champion		*cw_lst_swap(t_champion **champions, t_champion **next)
{
	t_champion	tmp;
	int			i;

	i = -1;
	tmp.header = (*next)->header;
	while (++i < REG_SIZE)
		tmp.reg[0][i] = (*next)->reg[0][i];
	tmp.ins = (*next)->ins;
	tmp.pc = (*next)->pc;
	tmp.num = (*next)->num;
	(*next)->header = (*champions)->header;
	i = -1;
	while (++i < REG_SIZE)
		(*next)->reg[0][i] = (*champions)->reg[0][i];
	(*next)->ins = (*champions)->ins;
	(*next)->pc = (*champions)->pc;
	(*next)->num = (*champions)->num;
	(*champions)->header = tmp.header;
	i = -1;
	while (++i < REG_SIZE)
		(*champions)->reg[0][i] = tmp.reg[0][i];
	(*champions)->ins = tmp.ins;
	(*champions)->pc = tmp.pc;
	(*champions)->num = tmp.num;
	return (*next);
}

void			cw_lst_dsort_by_num(t_champion **champions)
{
	t_champion	*tmp;
	int			id;

	id = 1;
	tmp = *champions;
	while (tmp->next)
	{
		if (tmp->num < tmp->next->num)
		{
			cw_lst_swap(&tmp, &tmp->next);
			tmp = *champions;
		}
		else
			tmp = tmp->next;
	}
	tmp = *champions;
	while (tmp)
	{
		tmp->id = id;
		tmp->idp = id;
		id++;
		tmp = tmp->next;
	}
}

t_champion		*cw_lst_last(t_champion *begin)
{
	t_champion		*tmp;

	tmp = begin;
	if (begin == NULL)
		return (begin);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
