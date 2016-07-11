/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 19:16:43 by tvisenti          #+#    #+#             */
/*   Updated: 2016/07/11 19:20:31 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

t_header	asm_header_init(void)
{
	t_header	*new;

	if (!(new = (t_lem*)malloc(sizeof(t_lem))))
		return (NULL);
	if (new != NULL)
	{
		new->magic = 0;
		new->prog_name = NULL;
		new->prog_size = 0;
		new->comment = NULL;
	}
	return (new);
}
