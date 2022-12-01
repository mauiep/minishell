/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_else.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 08:54:39 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/29 11:56:54 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lst_remove_quotes_else(t_lst *l, int j, int i, char *to_free)
{
	char	c;

	c = l->str[i];
	if (c != '\0')
	{
		j = 1;
		while (l->str[i + j] && l->str[i + j] != c)
			j++;
		l->str = without_quotes(l->str, i, i + j);
		if (!l->str)
			return (-1);
		free(to_free);
		return ((i + j) - 1);
	}
	return (i);
}

int	lst_remove_quotes(t_lst *l)
{
	char	*to_free;
	int		i;
	int		j;

	i = 0;
	j = 0;
	to_free = l->str;
	while (l->str[i] != 0)
	{
		to_free = l->str;
		while (l->str[i] && l->str[i] != 39 && l->str[i] != 34)
			i++;
		i = lst_remove_quotes_else(l, j, i, to_free);
		if (i == -1)
			return (-1);
	}
	return (1);
}

static int	remove_quotes_else(char **tmp, int i, int j, char *to_free)
{
	char	c;

	c = (*tmp)[i];
	if (c != '\0')
	{
		j = 1;
		while ((*tmp)[i + j] && (*tmp)[i + j] != c)
			j++;
		*tmp = without_quotes(*tmp, i, i + j);
		if (!(*tmp))
			return (-1);
		free(to_free);
		return ((i + j) - 1);
	}
	return (i);
}

int	remove_quotes(char **tab)
{
	int		i;
	int		j;
	char	**tmp;
	char	*to_free;

	i = 0;
	j = 0;
	tmp = tab;
	while ((*tmp) != NULL)
	{
		while ((*tmp)[i] != 0)
		{
			to_free = *tmp;
			while ((*tmp)[i] && (*tmp)[i] != 39 && (*tmp)[i] != 34)
				i++;
			i = remove_quotes_else(tmp, i, j, to_free);
			if (i == -1)
				return (-1);
		}
		i = 0;
		tmp++;
	}
	return (0);
}
