/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:16:29 by ademenet          #+#    #+#             */
/*   Updated: 2016/07/13 15:17:00 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Cette instruction n’est pas suivie d’octet pour décrire les paramètres.
** Elle prend toujours un index et crée un nouveau programme qui s’exécute
** à partir de l’adresse : (PC + (premier paramètre % IDX_MOD)). Fork %34 crée
** un nouveau programme. Le nouveau programme hérite des di érents états
** du père.
*/
