/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:54:56 by admaupie          #+#    #+#             */
/*   Updated: 2022/10/28 20:40:56 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

int	get_word(char *buffer, t_lst *new)
{
	int	i;
	int	c;

	i = 0;
	c = ' ';
	while (buffer[i] && (c != ' ' || !is_sep(buffer[i])))
	{
		if (buffer[i] == '\\' && ft_echap(buffer, i) == 0)
			return (-3);
		if (c == ' ' && (buffer[i] == SIMPLE_QUOTE || buffer[i] == 34))
			c = buffer[i];
		else if (c != ' ' && buffer[i] == c)
			c = ' ';
		i++;
	}
	if (c != ' ')
		return (-2);
	new->str = ft_strndup(buffer, i);
	if (!new->str)
		return (-42);
	return (1);
}

int	expand(t_lst *lst, t_dynarray *darr)
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
				if (c == 0 && (ptr->str[i] == 39 || ptr->str[i] == 34))
					c = ptr->str[i];
				else if (c != 0 && ptr->str[i] == c)
					c = 0;
				else if (ptr->str[i] == '$' && c != 39
						&& ptr->str[i + 1] && ptr->str[i + 1] != ' ')
					j = ft_joindollar(ptr, i, darr);
				if (j == -42)
					return (-1);
				i = i + j + 1;
			}
		}
		ptr = ptr->next;
	}
	return (1);
}

int	parse(char *line_buffer, t_dynarray *darr)
{
	int		i;
	int		len;
	t_lst	*lst;

	lst = ft_lstnew();
	if (!lst)
		return (print_err(-1));
	i = 0;
	while (line_buffer[i])
	{
		len = 1;
		if (!is_sep(line_buffer[i]) && line_buffer[i] != ' ')
			len = push_word(lst, line_buffer + i);
		else if (line_buffer[i] != ' ')
			len = push_sep(lst, line_buffer + i);
		if (len < 0)
			return (print_err(len) + free_lst(lst));
		i = i + len;
	}
	if (!ft_verif(lst))
		return (print_err(-4));
	//ft_printlst(lst);
	if (expand(lst, darr) == -1)
		return (printf("BUG EXPAND\n"));
	ft_pipes(lst->next, ft_pipes_left(lst), darr);
	free_lst(lst);
	return (1);
}
