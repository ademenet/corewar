/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 19:08:37 by tvisenti          #+#    #+#             */
/*   Updated: 2016/07/19 10:39:34 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** ERROR
*/

int		asm_error(int error)
{
	if (error == 1)
		printf("Wrong format name -> line: %d\n", g_line);
	if (error == 2)
		printf("Wrong format comment -> line: %d\n", g_line);
	if (error == 3)
		printf("Wrong format labels_char -> line: %d\n", g_line);
	if (error == 4)
		printf("Wrong format label_char -> line: %d\n", g_line);
	if (error == 5)
		printf("Wrong name of instruct -> line: %d\n", g_line);
	if (error == 6)
		printf("Wrong number of register -> line: %d\n", g_line);
	if (error == 7)
		printf("Not an indirect -> line: %d\n", g_line);
	if (error == 8)
		printf("Probleme d'arguments -> line: %d\n", g_line);
	if (error == 9)
		printf("There's same label\n");
	if (error == 10)
		printf("No match between label\n");
	exit(0);
	return (0);
}
