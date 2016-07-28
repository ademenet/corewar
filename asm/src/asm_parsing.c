/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DeSeropelly <DeSeropelly@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 18:53:48 by tvisenti          #+#    #+#             */
/*   Updated: 2016/07/28 09:30:31 by DeSeropelly      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** Bouge le pointeur juste avant le nom ou le commentaire
*/

char		*asm_header_pass(char *line, int name, int com, int one)
{
	int	i;

	i = -1;
	if (one)
		while (++i < name)
			line++;
	else
		while (++i < com)
			line++;
	while (*line != '\n' && *line != '"' && *line != '\0')
		line++;
	if (*line != '"')
		return (NULL);
	line++;
	return (line);
}

/*
** Récursive qui récupere le nom du label, position dans une liste chainée
*/

t_label		*asm_parse_line(char *line, int fd, char **file)
{
	t_label	*label;
	int		i;

	label = NULL;
	i = 0;
	while (!(i = 0) && get_next_line(fd, &line) > 0)
	{
		while (line[i] == '\t' || line[i] == ' ')
			i++;
		if (line[i] && line[i] != COMMENT_CHAR && asm_check_label(line) >= 1)
		{
			label = asm_label_init(label, line);
			while (line[i] != LABEL_CHAR)
				i++;
			i++;
		}
		while (line[i] == '\t' || line[i] == ' ')
			i++;
		if (line[i] && line[i] != COMMENT_CHAR && check_valid_line(&line[i]))
			*file = asm_free_join(&line[i], *file);
		free(line);
		line = NULL;
	}
	return (label);
}

/*
** Début du parsing
*/

int			asm_parsing(char *champion, t_header *head)
{
	int			fd;
	int			pos;
	char		*line;
	char		*file;
	t_label		*label;

	pos = 0;
	label = NULL;
	line = NULL;
	file = NULL;
	if ((fd = open(champion, O_RDONLY, 0555)) == -1)
		return (-1);
	asm_handler_name_comment(fd, line, head);
	label = asm_parse_line(line, fd, &file);
	asm_check_double_label(label);
	if (asm_check_label_exist(label, file) == 0)
		return (asm_error(12));
	ft_printf("file créé : %s\n", file);

	asm_reader(label, head, champion, file);
	if (label)
		asm_free_label(label);
	return (0);
}

// t_label		*asm_parse_line(char *line, int fd, int check, char *file)
// {
// 	t_label	*new;
// 	int		r;
//
// 	r = 1;
// 	new = NULL;
// 	// if (g_tmp_line)
// 		// free(g_tmp_line);
// 	g_tmp_line = NULL;
// 	//ft_printf("file avant gnl= %s\n", file);
// 	if (line && check == 1)
// 	{
// 		// printf("avant le free : %s\n", line);
// 		free(line);
// 		line = NULL;
// 	}
// 	if (check == 1 && (r = get_next_line(fd, &line)) && ++g_line)
// 	{
// 		// g_tmp_line = line;
// 		//ft_printf("****line avant join= %s\n", line);
// 		//ft_printf("file avant join= %s\n", file);
// 		file = asm_free_join(line, file);
// 		//ft_printf("file apres join= %s\n", file);
// 	}
// 	// printf("line : %s\n", line);
// 	if (r > 0 && line && line[0] != COMMENT_CHAR && asm_check_label(line) >= 1)
// 	{
// 		//ft_printf("---label foire= \n%s\n", line);
// 		new = asm_put_label(new, line, fd, file);
//
// 	}
// 	else if (r > 0 && line[0] != COMMENT_CHAR && line[0] != '\0' &&
// 	asm_check_label(line) == 0 && check_valid_line(line))
// 	{
// 		//ft_printf("--- FILE foire= %s\n", file);
// 		return (asm_parse_line(line, fd, 1, file));
// 	}
// 	else if (r > 0)
// 	{
// 		//ft_printf("IMPOSSIBLE\n");
// 		return (asm_parse_line(line, fd, 1, file));
// 	}
// 	 else if (r == 0)
// 	 {
// 		//ft_printf("FILE : %s\n", file);
// 	 	g_file = ft_strdup(file);
// 	 	free(file);
// 	 }
// 	return (new);
// }
