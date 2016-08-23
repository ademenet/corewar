/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:50:23 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/23 10:44:09 by gseropia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

void	asm_init_global(void)
{
	g_line = 0;
	g_pos = 0;
	g_temp = 0;
}

int		main(int argc, char **argv)
{
	t_header	*head;
	int			index;

	index = 1;
	head = NULL;
	asm_init_global();
	if (argc > 1)
	{
		while (index < argc)
		{
			head = asm_header_init();
			asm_parsing(argv[index++], head);
			head = NULL;
			asm_init_global();
		}
	}
	else
		ft_printf("Put one champion, please !\n");
	return (0);
}
