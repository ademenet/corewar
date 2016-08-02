/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_get_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:16:01 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/02 19:20:31 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Récupère le contenu d'un registre et retourne ce dernier dans un int.
*/

unsigned int		cw_get_data_reg(t_champion *champ, unsigned char reg)
{
	unsigned int	ret;

	ret = (champ->reg[reg][0] << 24 & 0xff000000) |
	(champ->reg[reg][1] << 16 & 0x00ff0000) |
	(champ->reg[reg][2] << 8 & 0x0000ff00) |
	(champ->reg[reg][3] & 0x000000ff);
	return (ret % MEM_SIZE);
}

unsigned int		cw_get_data_dir(t_proc *proc, t_champion *champ,
					unsigned int sze, int dir)
{
	unsigned int	ret;

	if (dir == 2)
		ret = proc->mem[sze] << 8 | proc->mem[sze + 1];
	else
		ret = proc->mem[sze] << 24 | proc->mem[sze + 1] << 16 |
		proc->mem[sze + 2] << 8 | proc->mem[sze + 3];
	return (ret % MEM_SIZE);
}

unsigned int		cw_get_data_ind(t_proc *proc, t_champion *champ,
					unsigned int sze)
{
	unsigned int	ret;
	unsigned int	ind;

	ind = (proc->mem[sze] << 8 | proc->mem[sze + 1]) % IDX_MOD;
	ret = proc->mem[champ->pc + ind] << 24
		| proc->mem[champ->pc + ind + 1] << 16
		| proc->mem[champ->pc + ind + 2] << 8
		| proc->mem[champ->pc + ind + 3];
	return (ret % MEM_SIZE);
}
