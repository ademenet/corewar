/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_zjmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:14:38 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/13 15:15:02 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Cette instruction n’est pas suivie d’octet pour décrire les paramètres.
** Elle prend toujours un index (IND_SIZE) et fait un saut à cet index si
** le carry est à un. Si le carry est nul, zjmp ne fait rien mais
** consomme le même temps.
*/
