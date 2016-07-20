/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 18:11:30 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/20 14:42:55 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "../../libft/libft.h"
# include "../../libft/ft_printf/include/fpf_printf.h" // a remplacer par les chevrons et compilation

/*
** Toutes les tailles sont en octets.
*/

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE
# define REG_NUMBER				16
# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct					s_header
{
  unsigned int					magic;
  char							prog_name[PROG_NAME_LENGTH + 1];
  unsigned int					prog_size;
  char							comment[COMMENT_LENGTH + 1];
}								t_header;

/*
** Définition de la structure pour un processus :
*/

typedef struct 					s_champion
{
	t_header					*header;
	char						reg[REG_NUMBER][REG_SIZE];
	long						pc;
	int							carry;
	int							cycle_cnt;
	int							num;
	struct s_champion			*next;
}								t_champion;

/*
** Structure du processeur :
*/

typedef struct 					s_proc
{
	t_champion					*champions;
	int							dump;
	int							big_nb;
}								t_proc;

/*
** Structure générale :
*/

typedef struct					s_glob
{
	t_champion					champions[5];
	t_proc						*proc;
}								t_glob;

// definir une structure permettant d'acceder aux variables du processeur et des processus

#endif
