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

	g_line = 0;
	g_file = NULL;
	g_tmp_file = NULL;
	g_tmp_line = NULL;
	g_pos = 0;
	head = asm_header_init();
	if (argc == 2)
		asm_parsing(argv[1], head);
	else
		ft_printf("Put one champion, please !");
	asm_free_global();
	return (0);
}
