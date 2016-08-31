/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_manage_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/31 15:43:35 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void				cw_lst_new_init(t_champion *new)
{
	new->ins = 0;
	new->inst_c = 0;
	new->lives = 0;
	new->pc_origin = 0;
	new->pc = 0;
	new->inst_num = 0;
	new->idp = 0;
	new->carry = 0;
	new->id = 0;
}

t_champion			*cw_lst_new(t_header *header, int num)
{
	t_champion		*new;
	int				reg_sze;
	int				reg_nb;

	if ((new = malloc(sizeof(t_champion))) == NULL)
		return (NULL);
	reg_sze = -1;
	reg_nb = -1;
	new->header = header;
	new->num = num;
	new->next = NULL;
	new->prev = NULL;
	new->is_champ = 0;
	cw_lst_new_init(new);
	while (++reg_nb < REG_NUMBER)
	{
		while (++reg_sze < REG_SIZE)
			new->reg[reg_nb][reg_sze] = 0;
		reg_sze = -1;
	}
	return (new);
}

t_champion			*cw_lst_push(t_proc *proc, t_champion *new)
{
	if (new == NULL)
	{
		ft_printf("In - cw_lst_push - new is NULL\n");
		return (proc->champions);
	}
	if (proc->champions != NULL)
	{
		proc->champions->prev = new;
		new->next = proc->champions;
		new->prev = NULL;
	}
	proc->champions = new;
	return (proc->champions);
}

void				cw_lst_add(t_champion **begin, t_champion *new)
{
	t_champion		*tmp;

	if (new == NULL)
	{
		ft_printf("In - cw_lst_add - new is NULL\n");
		return ;
	}
	tmp = *begin;
	if (*begin)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	else
	{
		*begin = new;
		new->prev = NULL;
	}
	new->next = NULL;
}

int					cw_lst_sze(t_champion *begin)
{
	t_champion		*tmp;
	int				sze;

	sze = 0;
	tmp = begin;
	while (tmp)
	{
		tmp = tmp->next;
		sze++;
	}
	return (sze);
}
