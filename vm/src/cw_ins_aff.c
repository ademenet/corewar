/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_aff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:17:16 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/02 19:23:22 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Cette instruction est suivie d’un octet de paramétrage pour décrire
** les paramètres. Elle prend en paramètre un registre et a che le
** caractère dont le code ascii est présent dans ce registre (base
** 10). (un modulo 256 est appliqué au code ascii, le caractère
** est affiché sur la sortie standard).
*/

int			cw_ins_aff(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	unsigned int	p;

	p = cw_get_data_reg(tmp, proc->mem[(tmp->pc + 2) % MEM_SIZE] - 1) % 256;
	ft_printf("%c", p);
	return (3);
}
