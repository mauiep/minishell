/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:54:56 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/30 14:30:44 by ceatgie          ###   ########.fr       */
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
	new->str = ft_strndup2(buffer, i);
	if (!new->str)
		return (-42);
	return (1);
}

static int	expand_else(t_lst *ptr, int c, int i)
{
	if (c == 0 && (ptr->str[i] == 39 || ptr->str[i] == 34))
		c = ptr->str[i];
	else if (c != 0 && ptr->str[i] == c)
		c = 0;
	return (c);
}

static int	dollard_manager(t_lst *ptr, int c, int i, t_mini *data)
{
	int	j;

	j = 0;
	if (ptr->str[i] == '$' && c != 39
		&& ptr->str[i + 1] && ptr->str[i + 1] != ' ')
		j = ft_joindollar(ptr, i, data);
	return (j);
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
				c = expand_else(ptr, c, i);
				j = dollard_manager(ptr, c, i, data);
				if (j == -42 || j == -1)
					return (-1);
				i = i + j + 1;
			}
		}
		ptr = ptr->next;
	}
	return (1);
}
