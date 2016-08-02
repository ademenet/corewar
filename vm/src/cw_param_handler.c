/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_param_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/26 10:40:47 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

// void			*cw_lst_sort_by_num(t_champion **champions)
// {
// 	t_champion	*tmp;
// 	t_champion	bigest;
// 	int			max;
// 	int			sze;
// 	int i = 4;

// 	tmp = *champions;
// 	sorted_list = NULL;
// 	sze = cw_lst_sze(tmp);
// 	max = tmp->num;
// 	ft_printf("init : size : %d, max : %d\n", sze, max);
// 	while (cw_lst_sze(sorted_list) != sze && i-- )
// 	{

// 	}
// }

int				cw_param_fst_chk(int ac, int param, char **av, t_proc *proc)
{
	int			n;

	n = -1;
	if (ac < 2)
		return (cw_error_msg("Too few parameters"));
	if (ft_strcmp(av[param], "-dump") == 0)
	{
		if ((n = ft_atoi(av[++param])) <= 0)
			return (cw_error_msg("'dumb' must be a positive value"));
		proc->dump = n;
	}
	return (1);
}

long			cw_cnb_chk(long c_nb, t_proc *proc, char *str)
{
	t_champion	*tmp;
	int			cur;

	cur = -1;
	while (str[++cur])
		if (!isdigit(str[cur]) && str[0] != '-')
			return(cw_error_msg("The player number is invalid"));
	tmp = proc->champions;
	if (c_nb <= 0)
		return(cw_error_msg("The player number musn't be negative or nil"));
	while (tmp)
	{
		if (tmp->num == c_nb)
			return (cw_error_msg("Number already assigned to a player"));
		tmp = tmp->next;
	}
	return (1);
}

int				cw_creation_step(int n, int p, t_proc *proc, char **av, int c_nb)
{
	if (!n)
	{
		if (cw_create_champion(av[p], c_nb, proc, 0) <= 0)
			return (cw_error_msg("Wrong champion file !"));
	}
	else
		if (cw_create_champion(av[p], n, proc, 1) <= 0)
			return (cw_error_msg("Wrong champion file !"));
	if (cw_lst_sze(proc->champions) > 4)
		return (cw_error_msg("Too much players (4 max)"));
	return (1);
}

int				cw_param(char **av, int ac, t_proc *proc)
{
	long		n;
	int			param;
	int			c_nb;

	param = 0;
	c_nb = 0;
	n = 0;
	if (!cw_param_fst_chk(ac, 1, av, proc))
		return (0);
	while (++param < ac)
	{
		if (ft_strcmp(av[param], "-n") == 0)
		{
			param++;
			if (!cw_cnb_chk(n = ft_atoi(av[param]), proc, av[param]))
				return (0);
			param++;
		}
		else
			c_nb++;
		if (!cw_creation_step(n, param, proc, av, c_nb))
			return (0);
		n = 0;
	}
	//cw_lst_sort_by_num(&proc->champions);
	return (1);
}
