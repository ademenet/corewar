/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_instructions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 13:44:15 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/21 15:39:23 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** cw_instruct_init initialise le tableau de pointeurs sur fonction des
** instructions.
*/

void		cw_instruct_init(t_instruct *instruct)
{
	instruct[0] = cw_inst_live();
	instruct[1] = cw_inst_ld();
	instruct[2] = cw_inst_st();
	instruct[3] = cw_inst_add();
	instruct[4] = cw_inst_sub();
	instruct[5] = cw_inst_and();
	instruct[6] = cw_inst_or();
	instruct[7] = cw_inst_xor();
	instruct[8] = cw_inst_zjmp();
	instruct[9] = cw_inst_ldi();
	instruct[10] = cw_inst_sti();
	instruct[11] = cw_inst_fork();
	instruct[12] = cw_inst_lld();
	instruct[13] = cw_inst_lldi();
	instruct[14] = cw_inst_lfork();
	instruct[15] = cw_inst_aff();

}

/*
** Trouver et exécuter l'instruction demandée.
*/

int			cw_exec_instruction()
{

	return (0);
}
