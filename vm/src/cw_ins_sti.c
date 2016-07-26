/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_sti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:16:01 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/26 15:17:45 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** sti r2,%4,%5 sti copie REG_SIZE octet de r2 a l’adresse (4 + 5)
** Les paramètres 2 et 3 sont des index. Si les paramètres 2 ou 3
** sont des registres, on utilisera leur contenu comme un index.
*/

int			cw_ins_sti(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	printf("Je fais sti\n");
	// Comment calculer la taille où jumper ?!
	proc->champions->pc = 6;
	cw_load_ins_c(proc);
	return (1);
}
