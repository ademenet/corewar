/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_manage_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/20 15:39:16 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

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
	while (++reg_nb < REG_NUMBER)
	{
		while (++reg_sze < REG_SIZE)
			new->reg[reg_nb][reg_sze] = 0;
		reg_sze = -1;
	}
	return (new);
}

void				cw_lst_push(t_champion **begin, t_champion *new)
{
	if (new == NULL)
	{
		ft_printf("In - cw_lst_push - new is NULL\n");
		return ;
	}
	if (*begin == NULL)
		*begin = new;
	else
	{
		(*begin)->prev = new;
		new->next = *begin;
		new->prev = NULL;
		*begin = new;
	}
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

t_champion			*cw_lst_last(t_champion *begin)
{
	t_champion		*tmp;

	tmp = begin;
	if (begin == NULL)
		return (begin);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}