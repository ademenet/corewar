/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 15:19:42 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/26 13:42:22 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
**
*/

// TODO : trouver un moyen rapide et simple (pour toutes les fonctions
// d'instructions) de recuperer les types de params.

// PAS BON : mieux vaut faire retourner la taille de linstruction par
// les fonctions dinstructions elles memes

/*
** Repère et décode l'OCP :
*/

int			cw_ins_ocp(t_proc *proc, t_champion *champ, t_ocp *ocp)
{
	
	// if (proc->mem[champ->pc] == 0x01)
	// 	return (4);
	// else if (proc->mem[champ->pc] == 0x09 ||
	// 		proc->mem[champ->pc] == 0x0c ||
	// 		proc->mem[champ->pc] == 0x0f)
	// 	return (2);
	// else if ()
	return (1);
}
