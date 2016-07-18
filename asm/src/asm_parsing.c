/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 18:53:48 by tvisenti          #+#    #+#             */
/*   Updated: 2016/07/16 16:37:48 by Transmetropolitan###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

int 	asm_check_dir(char **line)
{
	ft_printf("Alors on en est la : %s\n", *line);
	return(1);

}
int		asm_check_arg(char *line, int instruct)
{
	int	i;

	i = 0;
	while (*line == ' ' || *line == '\t')
		line++;
	if (instruct == 1 || instruct == 9 || instruct == 12 || instruct == 15)
	{
		 if (asm_check_dir(&line))
		 	return (1);
	}
	//if (instruct == 16 && asm_check_reg(&line))
	//	return(1);
	return (0);
}

/*
** Verifie les instructions
*/

int		asm_check_instruct(char *line)
{
	char	**tab;
	int		ret;

	ret = 0;
	
	if (ft_strchr(line, '\t'))
		tab = ft_strsplit(line, '\t');
	else
		tab = ft_strsplit(line, ' ');

	if (tab[0])
	{
		//ft_printf("test1\n");
		//ret = asm_instruct_name(&line);
		//printf("ARG : %d\n", ret);
		// asm_check_arg(line, ret);
	}
	//ft_printf("test2\n");
	return (asm_free_tab(tab, 1));
}

/*
** Récupére le nom et le comment et le stocke dans la struct(header)
** !!!! FAIRE DES FREE + RETOUR ERROR !!!!
*/

int		asm_copy_name_comment(char *line, t_header *head, int first, int last)
{
	if (ft_strncmp(NAME_CMD_STRING, line, first) == 0)
	{
		first = first + 2;
		last = ft_strlen(line) - first - 1;
		ft_strcpy(head->prog_name, ft_strsub(line, first, last));
		head->prog_name[PROG_NAME_LENGTH] = '\0';
	}
	else if (ft_strncmp(COMMENT_CMD_STRING, line, last) == 0)
	{
		first = last + 2;
		last = ft_strlen(line) - first - 1;
		ft_strcpy(head->comment, ft_strsub(line, first, last));
		head->comment[COMMENT_LENGTH] = '\0';
	}
	return (1);
}

/*
** Récupére le nom et le comment et le stocke dans la struct(header)
*/

int		asm_handler_name_comment(int fd, char *line, t_header *head)
{
	int	first;
	int	last;

	first = 0;
	last = 0;
	while (get_next_line(fd, &line) > 0)
	{
		g_line++;
		if (line[0] != COMMENT_CHAR && line[0] != '\0')
		{
			first = ft_strlen(NAME_CMD_STRING);
			last = ft_strlen(COMMENT_CMD_STRING);
			asm_copy_name_comment(line, head, first, last);
			if (head->comment[0] && head->prog_name[0])
				return(1);
		}
	}
	return (0);
}
int check_valid_line(char *line)
{
	int fct = asm_instruct_name(&line);
	if (fct == 1 || fct == 9 || fct == 12 || fct == 14 || fct == 15)
	{	
		line = line + 4;
		//while(*line == ' ' || *line == '\t')
		//	line++;
	}
	else if (fct == 2 || fct == 3 || fct == 7)
		line = line + 2;
	else
		line = line + 3;
	//ft_printf("test line :%s\n", line); 
	asm_check_arg(line, fct);
	line = NULL;
return(0);	
}

/*
** Join + free; voir realloc ?
** !!!! Il faut traiter le label !!!!
*/

t_label		*asm_parse_line(char *line, int fd)
{
	t_label		*new;

	new = NULL;
	if (get_next_line(fd, &line) == 1)
	{
		if (line[0] != COMMENT_CHAR && asm_check_label(line) == 1)
		{
			// printf("Found a label : %s\n", line);
			new = asm_label_init();
			new->name = ft_strsub(line, 0, ft_strclen(line, LABEL_CHAR));
			new->pos = 0;
			// Enregistrer la suite du label //
			new->next = asm_parse_line(line, fd);
		}
		else if (line[0] != COMMENT_CHAR && line[0] != '\0' && asm_check_label(line) == 0)
		{
			// printf("Found instruct :%s\n", line);	
			check_valid_line(line);
			return(asm_parse_line(line, fd));
		}
		else
			return(asm_parse_line(line, fd));
	}
	return (new);
}

int			asm_parsing(char *champion, t_header *head)
{
    int			fd;
    int			pos;
    char		*line;
    t_label		*label;

    pos = 0;
    line = NULL;
    if ((fd = open(champion, O_RDONLY, 0555)) == -1)
        return (-1);
    if (asm_handler_name_comment(fd, line, head) == 0)
        return (0);
	label = asm_parse_line(line, fd);
	// Verification de l'enregistrement des labels
	// while(label)
    // {
    //     printf("Label : -%s-\n", label->name);
    //     label = label->next;
    // }
	// printf("Name : |%s|\n", head->prog_name);
	// printf("Comment : |%s|\n", head->comment);
    return (0);
}
