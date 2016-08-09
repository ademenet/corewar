/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_bonus_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 10:34:15 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/01 18:01:13 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*	Pour ajouter la gestion d'une option, ajouter la lettre choisie dans la
	string de ft_cinstr
	/!\ ne pas ajouter la lettre 'n'
*/
void	cw_bon_handler(char **av, int ac, int param)
{
	arr_set(g_bon, 0, 256);
	while (param < ac)
	{
		if (av[param][0] == '-' && ft_cinstr(param[av][1], "v"))
			g_bon[av[param][1]] = 1;
		else
		{
			cw_error_msg("Wrong option format");
			ft_printf("%sOptions available :\n", GRE);
			ft_printf("-v : nCurse visualiser%s\n", EOC);
			exit(1);
		}
		param++;
	}
}
