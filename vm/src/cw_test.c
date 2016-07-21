/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/21 17:55:43 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

int			main(void)
{
	t_proc		proc;

	proc.mem[0] = 0x01;
	proc.mem[1] = 0x00;
	proc.mem[2] = 0x00;
	proc.mem[3] = 0x00;
	proc.mem[4] = 0x00;

	cw_processor(&proc);
	return (0);
}
