/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 19:16:43 by tvisenti          #+#    #+#             */
/*   Updated: 2016/07/18 17:24:33 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

t_header	*asm_header_init(void)
{
	t_header	*new;

	if (!(new = (t_header*)malloc(sizeof(t_header))))
		return (NULL);
	if (new != NULL)
	{
		new->magic = COREWAR_EXEC_MAGIC;
		new->prog_size = 0;
		ft_bzero(new->prog_name, PROG_NAME_LENGTH);
		ft_bzero(new->comment, COMMENT_LENGTH);
	}
	return (new);
}

t_label		*asm_label_init(void)
{
	t_label		*new;

	if (!(new = malloc(sizeof(t_label))))
		return (NULL);
	new->name = NULL;
	new->next = NULL;
	new->pos = 0;
	return (new);
}
