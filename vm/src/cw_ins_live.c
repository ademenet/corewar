/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_live.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:05:56 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/27 19:46:47 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Suivie de 4 octets qui représente le numéro du joueur. Cette instruction
** indique que ce joueur est en vie. Pas d’octet de codage des paramètres.
*/

int			cw_ins_live(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	tmp->lives++;
	proc->lives_total++;
	proc->live[tmp->id - 1]++;
	ft_printf("%s fait un LIVE\n", tmp->header->prog_name);
	return (5);
}
