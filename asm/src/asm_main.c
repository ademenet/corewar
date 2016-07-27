/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:50:23 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/27 10:24:57 by tvisenti         ###   ########.fr       */
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
		//while (index > argc)
		//{
			head = asm_header_init();
			asm_parsing(argv[index], head);
			g_pos = 0;
			//free(head);
		//}
	}
	else
		ft_printf("Put one champion, please !");
	asm_free_global();
	return (0);
}
