/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_live.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:05:56 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/09 13:51:06 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Suivie de 4 octets qui représente le numéro du joueur. Cette instruction
** indique que ce joueur est en vie. Pas d’octet de codage des paramètres.
*/

int			cw_ins_live(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	check;
	t_champion		*temp;

	temp = proc->champions;
	check = cw_get_data_dir(proc, tmp, tmp->pc + 1, 4);
	tmp->lives++;
	proc->lives_total++;
	while (temp)
	{
		if (temp->num == check && temp->is_champ == 1)
		{
			proc->live[tmp->id - 1]++;
			ft_printf("un processus dit que le joueur %d(%s) est en vie",
				tmp->num, tmp->header->prog_name);
			// mvprintw(0, 210,"un processus dit que le joueur %d(%s) est en vie",
			//	tmp->num, tmp->header->prog_name);
			proc->last_live_id = tmp->id;
			return(5);
		}
		temp = temp->next;
	}
	return (5);
}
