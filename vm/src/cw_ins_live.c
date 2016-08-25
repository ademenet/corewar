/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_live.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:05:56 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/25 15:51:58 by ademenet         ###   ########.fr       */
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
		ft_printf("P%5d | %s %d\n", tmp->idp, "live", tmp->num);
	else if (proc->dump == 0)
		ft_printf("Un processus dit que le joueur %d(%s) est en vie\n",
			tmp->num, tmp->header->prog_name);
}

int			cw_ins_live(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	int				i;
	unsigned int	check;

	i = 0;
	check = cw_get_data_dir(proc, tmp, (tmp->pc + 1) % MEM_SIZE, 4);
	tmp->lives++;
	proc->lives_total++;
	while (proc->champ_by_id[i] != NULL)
	{
		if (proc->champ_by_id[i]->num == check)
		{
			proc->live[proc->champ_by_id[i]->id - 1] += 1;
			cw_ins_live_display(proc, proc->champ_by_id[i]);
			proc->last_live_id = proc->champ_by_id[i]->id;
			return (5);
		}
		i++;
	}
	if (g_bon['d'])
		ft_printf("P%5d | %s %d\n", tmp->idp, "live", check);
	return (5);
}
