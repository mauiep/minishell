/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:54:56 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/12 01:02:06 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../minishell.h"

int	get_word(char *buffer, t_lst *new)
{
	int	i;
	int	c;

	i = 0;
	c = ' ';
	while (buffer[i] && (c != ' ' || !is_sep(buffer[i])))
	{
		if (c == ' ' && (buffer[i] == '\'' || buffer[i] == '\"'))
			c = buffer[i];
		else if (c != ' ' && buffer[i] == c)
			c = ' ';
		i++;
	}
	if (c != ' ')
		return (-2);
	new->str = ft_strndup2(buffer, i);
	if (!new->str)
		return (-42);
	return (1);
}

int	expand(t_lst *lst, t_mini *data)
{
	t_lst	*ptr;
	int		i;
	int		j;
	int		c;

	ptr = lst->next;
	while (ptr)
	{
		if (ptr->token == 0)
		{
			i = 0;
			c = 0;
			while (ptr->str && ptr->str[i])
			{
				j = 0;
				if (c == 0 && (ptr->str[i] == '\'' || ptr->str[i] == '\"'))
					c = ptr->str[i];
				else if (c != 0 && ptr->str[i] == c)
					c = 0;
				else if (ptr->str[i] == '$' && c != '\''
						&& ptr->str[i + 1] && ptr->str[i + 1] != ' ' && printf("on va rentrer ds join\n"))
					j = ft_joindollar(ptr, i, data);
				if (j == -42)
					return (-1);
				i = i + j + 1;
			}
		}
		ptr = ptr->next;
	}
	return (1);
}

int	parse(char *line_buffer, t_mini *data)
{
	int		i;
	int		len;
	t_lst	*lst;

	lst = ft_lstnew();
	ft_printlst(lst);
	if (!lst)
		return (print_err(-1));
	i = 0;
	while (line_buffer[i])
	{
		len = 1;
		if (!is_sep(line_buffer[i]) && line_buffer[i] != ' ')
		{
			len = push_word(lst, line_buffer + i);
			//fprintf(stdout, "je passe dans le premier if\n");
		}
		else if (line_buffer[i] != ' ')
		{
			len = push_sep(lst, line_buffer + i);
			//fprintf(stdout, "je passe dans le deuxieme if\n");
		}
		if (len < 0)
		{
			//fprintf(stdout, "je passe dans le troisieme if\n");
			return (print_err(len) + free_lst(lst));
		}
		//fprintf(stdout, "len vaut -> %i et i vaut -> %i\n", len, i);
		i = i + len;
		//usleep(2000000);
	}
	if (!ft_verif(lst))
		return (print_err(-4));
	ft_printlst(lst);
	if (expand(lst, data) == -1)
		return (printf("BUG EXPAND\n"));
	if (!ft_pipes(lst->next, ft_pipes_left(lst), data))
		return (printf("PIPES BAD RETURN\n"), -1);
	free_lst(lst);
	return (1);
}
