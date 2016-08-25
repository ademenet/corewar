/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 15:19:42 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/02 10:34:04 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

int		cw_error_msg(char *msg)
{
	ft_printf("%s%s%s\n",RED, msg, EOC);
	return (0);
}

int		cw_invert_endian(int x)
{
	x = ((x >> 24) & 0xff) | ((x >> 8) & 0xff00) | ((x << 8) & 0xff0000)
		| ((x << 24) & 0xff000000);
	return (x);
}

void			cw_init_champ_array(t_proc *proc)
{
	t_champion	*tmp;
	int			i;

	i = -1;
	while (++i < 5)
		proc->champ_by_id[i] = NULL;
	tmp = proc->champions;
	i = 0;
	while (tmp)
	{
		proc->champ_by_id[i] = tmp;
		i++;
		tmp = tmp->next;
	}
}
