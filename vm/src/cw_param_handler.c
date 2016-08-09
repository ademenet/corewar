/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_param_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/28 18:29:30 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"


int		cw_param_fst_chk(int ac, int param, char **av, t_proc *proc)
{
	unsigned int	n;

	n = -1;
	if (ac < 2)
		return (cw_error_msg("Too few parameters"));
	if (ft_strcmp(av[param], "-dump") == 0)
	{
		if ((n = ft_atoi(av[++param])) <= 0)
			return (cw_error_msg("'dump' must be a positive value"));
		proc->dump = n;
	}
	return (1);
}

long	cw_cnb_chk(long c_nb, t_proc *proc, char *str)
{
	t_champion		*tmp;
	int				cur;

	cur = -1;
	while (str[++cur])
		if (!isdigit(str[cur]) && str[0] != '-')
			return(cw_error_msg("The player number is not valid"));
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

int		cw_crea_step(int n, int p, t_proc *proc, char **av, int c_nb)
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

int		cw_param_loop(int param, int ac, char **av, t_proc *proc)
{
	long			n;
	unsigned int	c_nb;

	n = 0;
	c_nb = 0;
	while (++param < ac && !(av[param][0] == '-' && av[param][1] != 'n' &&
			ft_isalpha(av[param][1])))
	{
		if (ft_strcmp(av[param], "-n") == 0)
		{
			param++;
			if (param >= ac)
				return (cw_error_msg("The player number is not valid"));
			if (!cw_cnb_chk(n = ft_atoi(av[param]), proc, av[param]))
				return (0);
			param++;
			if (param >= ac)
				return (cw_error_msg("Wrong format"));
		}
		else
			c_nb++;
		if (!cw_crea_step(n, param, proc, av, c_nb))
			return (0);
		n = 0;
	}
	return (param);
}

int		cw_param(char **av, int ac, t_proc *proc)
{
	long			n;
	int				param;
	unsigned int	c_nb;

	param = 0;
	c_nb = 0;
	n = 0;
	if (!cw_param_fst_chk(ac, 1, av, proc))
		return (0);
	param = proc->dump ? param  + 2 : param;
	if (!(param = cw_param_loop(param, ac, av, proc)))
		return (0);
	cw_bon_handler(av, ac, param);
	cw_lst_dsort_by_num(&(proc->champions));
	return (1);
}
