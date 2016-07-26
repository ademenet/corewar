/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_ldi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:15:25 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/26 13:42:32 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Cette opération modifie le carry. ldi 3,%4,r1 lit IND_SIZE octets a
** l’adresse : (PC + (3 % IDX_MOD)) ajoute 4 à cette valeur. On nommera S
** cette somme. On lit REG_SIZE octet à l’adresse (PC + (S % IDX_MOD))
** que l’on copie dans r1. Les paramètres 1 et 2 sont des index.
*/

int			cw_ins_ldi(t_proc *proc, t_ocp *ocp)
{
	return (1);
}
