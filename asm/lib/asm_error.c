/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 19:08:37 by tvisenti          #+#    #+#             */
/*   Updated: 2016/07/26 14:52:32 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** Error
*/

int		asm_error(int error)
{
	asm_free_global();
	if (error == 1)
		ft_printf("Wrong format name -> line: %d\n", g_line);
	if (error == 2)
		ft_printf("Wrong format comment -> line: %d\n", g_line);
	if (error == 3)
		ft_printf("Wrong format labels_char -> line: %d\n", g_line);
	if (error == 4)
		ft_printf("Wrong format label_char -> line: %d\n", g_line);
	if (error == 5)
		ft_printf("Wrong name of instruct -> line: %d\n", g_line);
	if (error == 7)
		ft_printf("Not an indirect -> line: %d\n", g_line);
	if (error == 8)
		ft_printf("Arguments Problem, Bro -> line: %d\n", g_line);
	if (error == 9)
		ft_printf("There's same label\n");
	if (error == 10)
		ft_printf("No match between label\n");
	if (error == 11)
		ft_printf("Impossible to find name or comment\n");
	if (error == 12)
		ft_printf("No instructions in label -> line: %d\n", g_line);
	exit(0);
	return (0);
}
