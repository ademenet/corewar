/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_processor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 12:15:17 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/13 18:18:42 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Incrémente le PC de la size renvoyé par la fonction de l'instruction. Cette
** dernière calcule la size du saut de PC à partir de la taille attendue des
** paramètres donnés par l'OCP. S'il n'y en a pas, alors on a une taille
** définie.
** Si le visualiseur est activé, l'ancien PC en couleur est réinitialisé (mis
** en blanc et noir) et le nouveau hérite de la couleur en surbrillance.
*/

void		cw_exec_process_pcincrement(t_proc *proc, t_champion *tmp, int size)
{
	if (g_bon['v'])
		cw_vizualizer_pcprint(proc, tmp, (tmp->id + 10));
	tmp->pc = (tmp->pc + (unsigned short)size) % MEM_SIZE;
	if (g_bon['v'])
		cw_vizualizer_pcprint(proc, tmp, tmp->id);
}

/*
** Effectue l'instruction puis fait sauter le PC et réinitialise le cycles
** d'instruction avec la nouvelle valeur.
** Si une instruction n'était pas em cours (tmp->ins == NULL) alors on signale
** cette instruction et on charge le temps de l'instruction.
*/

void		cw_exec_process_instruct(t_proc *proc, t_champion *tmp, t_ocp *ocp)
{
	int		size;

	size = 0;
	if (tmp->ins == NULL)
	{
		tmp->ins = &proc->mem[tmp->pc];
		tmp->inst_c = g_op[proc->mem[tmp->pc] - 1].cycles_nb;
	}
	else
	{
		cw_ins_ocp(proc, tmp, ocp);
		size = g_op[proc->mem[tmp->pc] - 1].ptr(proc, tmp, ocp);
		cw_exec_process_pcincrement(proc, tmp, size);
		if (proc->mem[tmp->pc] > 0x00 && proc->mem[tmp->pc] < 0x11)
		{
			tmp->ins = &proc->mem[tmp->pc];
			tmp->inst_c = g_op[proc->mem[tmp->pc] - 1].cycles_nb;
		}
		else
			tmp->ins = NULL;
	}
}

/*
** cw_exec_process itère sur chaque processus pour savoir s'il y a
** quelque chose à faire ou pas. Si le temps d'une instruction est écoulé, alors
** elle va appeler la fonction qui exécute. Si non, elle incrémente le PC
** jusqu'à tomber sur une instruction.
*/

void		cw_exec_process(t_proc *proc)
{
	t_champion	*tmp;
	t_ocp		ocp;

	tmp = proc->champions;
	while (tmp)
	{
		if (tmp->is_champ != -1)
		{
			if (tmp->inst_c == 1)
			{
				if (proc->mem[tmp->pc] > 0x00 && proc->mem[tmp->pc] < 0x11)
					cw_exec_process_instruct(proc, tmp, &ocp);
				else
					cw_exec_process_pcincrement(proc, tmp, 1);
			}
			else
				tmp->inst_c--;
		}
		tmp = tmp->next;
	}
}

/*
** cw_processor mîme le processeur.
** Elle exécute les cycles, lit la mémoire tout en traitant les instructions.
*/

int			cw_processor(t_proc *proc)
{
	int		c_check;

	c_check = 1;
	cw_proc_init(proc);
	cw_load_ins_c(proc);
	while (cw_cycles(proc) && c_check)
	{
		cw_exec_process(proc);
		c_check = cw_cycles_checks(proc);
		proc->c++;
	}
	return (1);
}
