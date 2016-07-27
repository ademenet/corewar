/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 15:19:42 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/26 14:34:19 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Repère et décode l'OCP : donne le mode à travers la structure t_ocp.
** Donne le type de paramètre attendu :
** - REG_CODE = 1 (0x01) ;
** - DIR_CODE = 2 (0x02) ;
** - IND_CODE = 3 (0x03).
*/

int					cw_ins_ocp(t_proc *proc, t_champion *champ, t_ocp *ocp)
{
	unsigned char	ocp_v;

	ocp->first = 0;
	ocp->second = 0;
	ocp->third = 0;
	ocp_v = 0;
	if (proc->mem[champ->pc] != 0x01 && proc->mem[champ->pc] != 0x09 &&
		proc->mem[champ->pc] != 0x0c && proc->mem[champ->pc] != 0x0f)
	{
		ocp_v = proc->mem[champ->pc + 1];
		ocp->first = ocp_v >> 6;
		ocp->second = (ocp_v >> 4) & 0x03;
		ocp->third = (ocp_v >>2) & 0x03;
	}
	return (1);
}

/*
** Renvoi la taille en octet de l'octet
*/

unsigned int		cw_ins_param_sze(char param, int dir)
{
	if (param == 1)
		return (1);
	if (param == 2)
		return (dir);
	if (param == 3)
		return (2);
	return (cw_error_msg("Wrong DIR_CODE ref passed to cw_ins_param_sze"));
}
