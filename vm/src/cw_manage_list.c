/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_manage_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/11 15:54:35 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

t_champion			*cw_lst_new(header_t *header, int num)
{
	t_champion		*new;

	if((new = malloc(sizeof(t_champion))) == NULL)
		return (NULL);
	new->header = header;
	new->num = num;
	new->next = NULL;
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
		new->next = *begin;
		*begin = new;
	}
}

void				cw_lst_add(t_champion *begin, t_champion *new)
{
	t_champion		*tmp;

	tmp = begin;
	if (begin)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		begin = new;
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
