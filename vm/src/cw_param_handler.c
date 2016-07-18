/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_param_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/11 15:54:35 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int			cw_error_msg(char *msg)
{
	ft_printf("%s\n", msg);
	return (0);
}

int			cw_param_fst_chk(int ac, int param, char **av)
{
	int		n;

	n = -1;
	if (ac < 2) // adapter s'il y a des options
		return (cw_error_msg("Too few parameters\n"));
	if (ft_strcmp(av[param], "-dump") == 0)
		if ((n = ft_atoi(av[++param])) <= 0)
			return (cw_error_msg("'dumb'must be a positive value\n"));
	return (-1);
}

int			cw_param(char **av, int ac, t_proc *proc)
{
	int		n;
	int		param;
	int		c_nb;

	n = -1;
	param = 1;
	c_nb = -1;
	if (!(n = cw_param_fst_chk(ac, param, av)))
		return (0);
	param = n == -1 ? 0 : 2;
	while (++param < ac)
	{
		//if (ft_strcmp(av[param], "-n") == 0)
			//if (cw_cnb_chk(c_nb = ft_atoi(av[++param]), champions))
			//	return (cw_error_msg("Number already assigned to a player\n")); // possibilité de faire cette verif dans create_champion
		if (!cw_create_champion(av[param], c_nb, proc))
			return (cw_error_msg("Wrong champion file !"));
	}
	return (1);
}
