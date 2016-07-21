/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_instructions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 13:44:15 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/21 18:11:40 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** cw_instruct_init initialise le tableau de pointeurs sur fonction des
** instructions.
*/

void		cw_instruct_init(t_instruct *instruct, t_proc *proc)
{
	instruct[0] = (*cw_ins_live)(proc);
	// instruct[1] = cw_ins_ld();
	// instruct[2] = cw_ins_st();
	// instruct[3] = cw_ins_add();
	// instruct[4] = cw_ins_sub();
	// instruct[5] = cw_ins_and();
	// instruct[6] = cw_ins_or();
	// instruct[7] = cw_ins_xor();
	// instruct[8] = cw_ins_zjmp();
	// instruct[9] = cw_ins_ldi();
	// instruct[10] = cw_ins_sti();
	// instruct[11] = cw_ins_fork();
	// instruct[12] = cw_ins_lld();
	// instruct[13] = cw_ins_lldi();
	// instruct[14] = cw_ins_lfork();
	// instruct[15] = cw_ins_aff();
}

/*
** Trouver et exécuter l'instruction demandée.
*/

int			cw_exec_instruction(
)
{

	return (0);
}
