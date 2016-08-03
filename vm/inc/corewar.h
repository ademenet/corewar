/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 18:11:30 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/03 15:45:37 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _COREWAR_H_
# define _COREWAR_H_

# include <ncurses.h>
# include <panel.h>
# include "colors.h"
# include "../../libft/libft.h"
# include "../../libft/ft_printf/include/fpf_printf.h" // a remplacer par les chevrons et compilation

// # include <libft.h>
// # include <fpf_printf.h>

/*
** Toutes les tailles sont en octets.
*/

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE
# define REG_NUMBER				16
# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4 * 1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

/*
**
*/

typedef char		t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

/*
** Structure du header (imposé par le sujet) :
*/

typedef struct					s_header
{
	unsigned int				magic;
	char						prog_name[PROG_NAME_LENGTH + 1];
	unsigned int				prog_size;
	char						comment[COMMENT_LENGTH + 1];
}								t_header;

/*
** Structure d'un processus :
*/

typedef struct 					s_champion
{
	t_header					*header;
	char						reg[REG_NUMBER][REG_SIZE];
	unsigned char				*ins; // 1 sert a stocker les processus avant chargement puis 2 sert de flag pour savoir si une instruction est en attente de traitement
	unsigned short int			pc_origin;
	unsigned short int			pc; // le PC est codé sur 2 octets
	char						carry; // pas besoin de le stocker dans int, un char suffit : 0 ou 1
	unsigned int				inst_c; // nombre de cycles de l'instruction, se decremente a chaque cycle jusqu'a execution
	unsigned int				num; // numero du processus
	unsigned int				lives;
	char						is_champ;
	char						id;
	struct s_champion			*next;
	struct s_champion			*prev;
}								t_champion;

/*
** Structure du processeur :
*/

typedef struct 					s_proc
{
	t_champion					*champions;
	// memoire du processeur
	unsigned char				mem[MEM_SIZE];
	unsigned int				dump;
	unsigned int				nb_proc; // nombre de processus courants
	// c_to_die : valeur qui vaut CYCLE_TO_DIE au début et qui sera décrémenté de
	// CYCLE_DELTA tous les blablablas
	unsigned int				c_to_die;
	// c : index des cycles. Init à 0.
	unsigned int				c;
	// live[5] : enregistre le nombre de live émis sur la période CYCLE_TO_DIE par champions.
	unsigned int				live[MAX_PLAYERS + 1];
	unsigned int				lives_total; // nombre total de lives sur toute la partie
	unsigned int				checks;
}								t_proc;

/*
** Structure de récupération des paramètres d'instruction :
*/

typedef struct					s_ocp
{
	char						first;
	char						second;
	char						third;
}								t_ocp;

/*
** Structure de définition des instructions :
** - pointeur sur la fonction qui se charge de l'intruction,
** - nom,
** - nombre de paramètre,
** - opcode (de 1 à 16),
** - nombre de cycles,
** - description,
** - OCP (0 ou 1).
*/

typedef struct					s_op
{
	int							(*ptr)();
	char						name[5];
	unsigned short int			param_nb;
	unsigned char				opcode;
	unsigned short int			cycles_nb;
	char						desc[36];
	unsigned char				ocp;
}								t_op;

/*
** Tableau global des bonus initialisé à 0 - lorsqu'une option est implementée,
la case du tableau a l'index correspondant passe à 1.
ex avec -v : g_bon['v'] sera egale a 1.
*/

char							g_bon[256];

/*
** RECUPERATION ET INITIALISATION DES CHAMPIONS
*/

int								cw_error_msg(char *msg);
int								cw_invert_endian(int x);
int								cw_param(char **av, int ac, t_proc *proc);
int								cw_create_champion(char *file, int c_nb, t_proc
								*proc, int n);
int								cw_load_ins_mem(t_proc *proc);

/*
** GESTION DES LISTES DE CHAMPIONS
*/

t_champion						*cw_lst_new(t_header *header, int num);
void							cw_lst_push(t_champion **begin,
								t_champion *new);
void							cw_lst_add(t_champion **begin, t_champion *new);
int								cw_lst_sze(t_champion *begin);
t_champion						*cw_lst_last(t_champion *begin);
void							cw_lst_dsort_by_num(t_champion **champions);

/*
** PROCESSOR
*/

int								cw_processor(t_proc *proc);
void							cw_exec_process(t_proc *proc);
void							cw_exec_process_instruct(t_proc *proc,
								t_champion *tmp, t_ocp *ocp);
int								cw_cycles(t_proc *proc);
int								cw_check_live_process(t_proc *proc);

/*
** PROCESSOR : FONCTIONS OUTILS
*/

void							cw_proc_init(t_proc *proc);
void							cw_load_ins_c(t_proc *proc);
unsigned int					cw_ins_param_sze(char param, int dir);

/*
** INSTRUCTIONS
*/

int								cw_ins_add(t_proc *proc, t_champion *tmp,
								t_ocp *ocp);
int								cw_ins_aff(t_proc *proc, t_champion *tmp,
								t_ocp *ocp);
int								cw_ins_and(t_proc *proc, t_champion *tmp,
								t_ocp *ocp);
void							cw_ins_fork_duplicate_reg(t_champion *new,
								t_champion *old);
int								cw_ins_fork(t_proc *proc, t_champion *tmp,
								t_ocp *ocp);
int								cw_ins_ld(t_proc *proc, t_champion *tmp,
								t_ocp *ocp);
int								cw_ins_ldi(t_proc *proc, t_champion *tmp,
								t_ocp *ocp);
int								cw_ins_lfork(t_proc *proc, t_champion *tmp,
								t_ocp *ocp);
int								cw_ins_live(t_proc *proc, t_champion *tmp,
								t_ocp *ocp);
int								cw_ins_lld(t_proc *proc, t_champion *tmp,
								t_ocp *ocp);
int								cw_ins_lldi(t_proc *proc, t_champion *tmp,
								t_ocp *ocp);
int								cw_ins_or(t_proc *proc, t_champion *tmp,
								t_ocp *ocp);
int								cw_ins_st(t_proc *proc, t_champion *tmp,
								t_ocp *ocp);
int								cw_ins_sti(t_proc *proc, t_champion *tmp,
								t_ocp *ocp);
int								cw_ins_sub(t_proc *proc, t_champion *tmp,
								t_ocp *ocp);
int								cw_ins_xor(t_proc *proc, t_champion *tmp,
								t_ocp *ocp);
int								cw_ins_zjmp(t_proc *proc, t_champion *tmp,
	 							t_ocp *ocp);

/*
** INSTRUCTIONS : FONCTIONS OUTILS
*/

int								cw_ins_ocp(t_proc *proc, t_champion *champ,
								t_ocp *ocp);
unsigned int					cw_get_data_reg(t_champion *champ,
								unsigned char reg);

/*
** INSTRUCTIONS : FONCTIONS GET DATA
*/

unsigned int					cw_get_data_reg(t_champion *champ,
								unsigned char reg);
unsigned int					cw_get_data_dir(t_proc *proc, t_champion *champ,
								unsigned int sze, int dir);
unsigned int					cw_get_data_ind(t_proc *proc, t_champion *champ,
								unsigned int sze);
/*
** BONUS : VISUALISEUR
*/

// void							cw_vizualizer(t_proc *proc);
int								cw_vizualizer_processor(t_proc *proc);
void							cw_vizualizer(t_proc *proc, WINDOW *win);
void							cw_vizualizer_memprint(t_proc *proc,
								WINDOW *win);
void							cw_vizualizer_infos(t_proc *proc, WINDOW *win);

void							cw_show_mem(char *start, int n);


/*
** Structure de définition des instructions :
** - pointeur sur la fonction qui se charge de l'intruction,
** - nom,
** - nombre de paramètre,
** - opcode (de 1 à 16),
** - nombre de cycles,
** - description,
** - OCP (0 ou 1).
*/

static const t_op				g_op[17] =
{
	{&cw_ins_live, "live", 1, 1, 10, "alive", 0},
	{&cw_ins_ld, "ld", 2, 2, 5, "load", 1},
	{&cw_ins_st, "st", 2, 3, 5, "store", 1},
	{&cw_ins_add, "add", 3, 4, 10, "addition", 1},
	{&cw_ins_sub, "sub", 3, 5, 10, "soustraction", 1},
	{&cw_ins_and, "and", 3, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1},
	{&cw_ins_or, "or", 3, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1},
	{&cw_ins_xor, "xor", 3, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1},
	{&cw_ins_zjmp, "zjmp", 1, 9, 20, "jump if zero", 0},
	{&cw_ins_ldi, "ldi", 3, 10, 25, "load index", 1},
	{&cw_ins_sti, "sti", 3, 11, 25, "store index", 1},
	{&cw_ins_fork, "fork", 1, 12, 800, "fork", 0},
	{&cw_ins_lld, "lld", 2, 13, 10, "long load", 1},
	{&cw_ins_lldi, "lldi", 3, 14, 50, "long load index", 1},
	{&cw_ins_lfork, "lfork", 1, 15, 1000, "long fork", 0},
	{&cw_ins_aff, "aff", 1, 16, 2, "aff", 1},
	{0, {0}, 0, 0, 0, {0}, 0}
};

#endif
