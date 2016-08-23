/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_live.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:05:56 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/22 13:03:11 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Suivie de 4 octets qui représente le numéro du joueur. Cette instruction
** indique que ce joueur est en vie. Pas d’octet de codage des paramètres.
*/

static void	cw_ins_live_display(t_proc *proc, t_champion *tmp)
{
	if (g_bon['v'])
	{
		werase(proc->win[1]);
		mvwprintw(proc->win[1], 60, 2,
			"Un processus dit que le joueur %d(%s) est en vie\n",
			tmp->num, tmp->header->prog_name);
	}
	else if (g_bon['d'])
		ft_printf("P%5d | %s %d\n", tmp->idp, g_op[proc->mem[tmp->pc] - 1].name,
		tmp->num);

		// ft_printf("lives_total == %u\n", proc->lives_total); // pour debug
		// ft_printf("lives de P%d == %u\n", tmp->idp, tmp->lives); // pour debug
		// int i = 0;
		// while (i < 4)
		// {
		// 	ft_printf("lives de champ%d == %u\n", i + 1, proc->live[i]); // pour debug
		// 	i++;
		// }

	}
	else if (proc->dump == 0)
		ft_printf("un processus dit que le joueur %d(%s) est en vie\n",
			tmp->num, tmp->header->prog_name);
}

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
		if (temp->num == check && (temp->is_champ == 1 || temp->is_champ == -1))
		{
			proc->live[tmp->id - 1] += 1;
			cw_ins_live_display(proc, tmp);
			proc->last_live_id = tmp->id;
			return(5);
		}
		temp = temp->next;
	}
	if (g_bon['d'])
		ft_printf("P%5d | %s %d\n", tmp->idp, g_op[proc->mem[tmp->pc] - 1].name,
		check);
	return (5);
}
