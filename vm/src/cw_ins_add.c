/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 14:49:48 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/01 19:10:15 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Cette instruction prend 3 registres en paramètre, additionne le contenu des
** 2 premiers et met le résultat dans le troisième. Cette opération modifie le
** carry. add r2,r3,r5 additionne r2 et r3 et met le résultat dans r5.
*/

int			cw_ins_add(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	param[3];

	param[0] = cw_get_data_reg(tmp, 0);
	// param[0] = cw_invert_endian(param[0]);
	// mvprintw(0, 20, "reg%d == %d", proc->mem[tmp->pc + 2], param[0]);
	// cw_show_mem((char*)&param[0], sizeof(param[0]));

	param[1] = cw_get_data_reg(tmp, 1);
	// param[1] = cw_invert_endian(param[1]);
	// mvprintw(0, 60, "reg%d == %d", proc->mem[tmp->pc + 3], param[1]);
	cw_show_mem((char*)&param[1], sizeof(unsigned int));

	param[2] = param[0] + param[1];
	// mvprintw(0, 80, "reg%d == %d", proc->mem[tmp->pc + 4], param[2]);
	// cw_show_mem((char*)&param[2], sizeof(param[2]));


	// tmp->reg[proc->mem[tmp->pc + 4]][0] = (reg3 >> 24) & 0xff;
	// tmp->reg[proc->mem[tmp->pc + 4]][1] = (reg3 >> 16) & 0xff;
	// tmp->reg[proc->mem[tmp->pc + 4]][2] = (reg3 >> 8) & 0xff;
	// tmp->reg[proc->mem[tmp->pc + 4]][3] = reg3 & 0xff;
	tmp->carry = tmp->carry == 0 ? 1 : 0;
	return (5);
}
