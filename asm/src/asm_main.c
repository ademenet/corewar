/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:50:23 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/28 14:57:16 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

int		main(int argc, char **argv)
{
	t_header	*head;
	int			index;

	index = 1;
	g_line = 0;
	g_file = NULL;
	g_tmp_file = NULL;
	g_tmp_line = NULL;
	if (argc == 2)
	{
		head = asm_header_init();
		asm_parsing(argv[index], head);
		g_pos = 0;
	}
	else
	{
		ft_printf("Put one champion, please !");
		return (0);
	}
	asm_free_global();
	// while (1);
	return (0);
}
