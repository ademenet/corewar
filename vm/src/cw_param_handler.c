/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_param_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/31 19:14:01 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

long	cw_cnb_chk(long c_nb, t_proc *proc, char *str)
{
	t_champion		*tmp;
	int				cur;

	cur = -1;
	while (str[++cur])
		if (!isdigit(str[cur]) && str[0] != '-')
			return (cw_error_msg("The player number is not valid"));
	tmp = proc->champions;
	if (c_nb <= 0)
		return (cw_error_msg("The player number musn't be negative or nil"));
	while (tmp)
	{
		if (tmp->num == c_nb)
			return (cw_error_msg("Number already assigned to a player"));
		tmp = tmp->next;
	}
	return (1);
}

int		cw_crea_step(int n[2], t_proc *proc, char **av, int c_nb)
{
	if (!n[0])
	{
		if (cw_create_champion(av[n[1]], c_nb, proc, 0) <= 0)
			return (cw_error_msg("Wrong champion file !"));
	}
	else if (cw_create_champion(av[n[1]], n[0], proc, 1) <= 0)
		return (cw_error_msg("Wrong champion file !"));
	if (cw_lst_sze(proc->champions) > 4)
		return (cw_error_msg("Too much players (4 max)"));
	return (1);
}

int		cw_param_loop(int param, int ac, char **av, t_proc *proc)
{
	long			n;
	unsigned int	c_nb;
	int				tab[2];

	c_nb = 0;
	while ((n = 0) || (++param < ac && !(av[param][0] == '-' &&
			av[param][1] != 'n' && ft_isalpha(av[param][1]))))
	{
		if (ft_strcmp(av[param], "-n") == 0)
		{
			if (++param >= ac)
				return (cw_error_msg("The player number is not valid"));
			if (!cw_cnb_chk(n = ft_atoi(av[param]), proc, av[param]))
				return (0);
			if (++param >= ac)
				return (cw_error_msg("Wrong format"));
		}
		else
			c_nb++;
		tab[0] = n;
		tab[1] = param;
		if (!cw_crea_step(tab, proc, av, c_nb))
			return (0);
	}
	return (proc->champions == NULL ? cw_error_msg("Wrong format") : param);
}

int		cw_param_fst_chk(int ac, int param, char **av, t_proc *proc)
{
	unsigned int	n;

	n = -1;
	if (ac < 2)
		return (cw_error_msg("Too few parameters"));
	if (ft_strcmp(av[param], "-dump") == 0)
	{
		if (av[++param] == NULL || (n = ft_atoi(av[param])) <= 0)
			return (cw_error_msg("'dump' must have a valid value"));
		proc->dump = n;
	}
	return (1);
}

int		cw_param(char **av, int ac, t_proc *proc)
{
	long			n;
	int				param;
	unsigned int	c_nb;

	n = 0;
	param = 0;
	c_nb = 0;
	if (!cw_param_fst_chk(ac, 1, av, proc))
		return (0);
	param = proc->dump ? param + 2 : param; // recupere dump
	if (!(param = cw_param_loop(param, ac, av, proc)))
		return (0);
	cw_bon_handler(av, ac, param);
	cw_lst_dsort_by_num(&(proc->champions));
	return (1);
}

void		cw_param_bonus_alert(void)
{
	cw_error_msg("Wrong option format");
	ft_printf("%sOptions available :\n", GRE);
	ft_printf("-v : nCurse visualiser\n");
	ft_printf("-d : debug mode\n");
	ft_printf("-c : display cycles\n");
	ft_printf("-s : play beep when process is killed\n");
	ft_printf("-z : dump zaz-like (use with dump option)\n");
	ft_printf("-m : mute live messages%s\n", EOC);
	exit(1);
}

int		cw_param_bonus(char *av)
{
	arr_set(g_bon, 0, 128);
	while (*av)
	{
		if (ft_cinstr(av[1], "vdzcms"))
			g_bon[(unsigned char)av] = 1;
		else
			cw_param_bonus_alert();
		av++;
	}
	if (g_bon['d'] || g_bon['z'] || g_bon['c'])
		g_bon['v'] = 0;
	return (0);
}

int		cw_param_file(unsigned int num;)
{
	if (num > 0)

	return (0);
}

int		cw_param_arguments(t_proc *proc, char **av, int i)
{
	int				ret;
	unsigned int	n;

	ret = 0;
	if (ft_strcmp(av[i], "-dump") == 0 && (av[i + 1] != NULL ||
		(n = ft_atoi(av[i + 1])) > 0))
		proc->dump = n;
	else if (av[i][1] == 'n' && (av[i + 1] != NULL ||
		(n = ft_atoi(av[i + 1])) > 0))
		cw_param_file(n);
	else
		cw_param_bonus(av[i]);
	return (ret);
}

int		cw_param(char **av, int ac, t_proc *proc)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (i < ac)
	{
		if (av[i][0] == '-' && (i + 1) < ac)
			ret = cw_param_arguments(proc, av, i);
		else
			ret = cw_param_file(0);
		if (ret != 0)
			return (0);
		i += ret;
	}
	return (0);
}
