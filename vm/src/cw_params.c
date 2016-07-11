/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_params.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 19:31:33 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/11 19:55:31 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

// -dump nbr_cycles
// Au bout de nbr_cycles cycles d’exécution, dump la mémoire sur la sortie stan-
// dard, puis quitte la partie. La mémoire doit être dumpée au format hexadécimal,
//  avec 32 octets par ligne.
// • -n number
// Fixe le numéro du prochain joueur. Si absent, le joueur aura le prochain numéro
// libre dans l’ordre des paramètres. Le dernier joueur aura le premier processus
// dans l’ordre d’exécution.

void		cw_params_handler(int argc, char **argv)
{
	int		j;

	j = 1;
	while (j < argc)
	{
		cw_params_recognize(argv[j]);
	}
}

int			cw_param_recognize(char *param)
{
	if (param[0] == '-')
	{
		if (ft_strcmp(param, "-dump"))
			cw_nbr_cycles();
		if (ft_strcmp(param, "-n"))
			cw_nbr_champion();
	}
	else
	{
		return (-1);
	}
}
