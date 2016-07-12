/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_instruct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 13:44:15 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/12 17:48:42 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"
#include <stdio.h>

// struct		s_process
// {
// 	char	*PC;
// 	int		carry;
// 	struct s_process	*next;
// };

void		cw_instr_or(char one, char two, char three)
{
	three = one | two;
}

void		cw_instr_and(char one, char two, char three)
{
	three = one & two;
}

int			cw_instruct_read_mem(int cycle_ready, )
{
	// ici on parcourt la memoire de notre processus
	// on part de PC
	// on reconnait l'intruction et on attend le bon moment pour l'executer
	return (0);
}

int			main(void)
{
	char	mem[MEM_SIZE]; // notre memoire RAM/circulaire
	int		i = 0;

	mem[0] = 0x0b;
	mem[1] = 0x68;
	mem[2] = 0x01;
	mem[3] = 0x00;
	mem[4] = 0x0f;
	mem[5] = 0x00;
	mem[6] = 0x01;
	mem[7] = 0x06;
	mem[8] = 0x64;
	mem[9] = 0x01;
	mem[10] = 0x00;
	mem[11] = 0x00;
	mem[12] = 0x00;
	mem[13] = 0x00;
	mem[14] = 0x01;
	mem[15] = 0x01;
	mem[16] = 0x00;
	mem[17] = 0x00;
	mem[18] = 0x00;
	mem[19] = 0x01;
	mem[20] = 0x09;
	mem[21] = 0xff;
	mem[22] = 0xfb;
	while (mem[i] != '\0')
	{
	}
}
