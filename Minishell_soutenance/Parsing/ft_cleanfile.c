/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:54:29 by admaupie          #+#    #+#             */
/*   Updated: 2022/12/07 13:58:39 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_remove_spaces(t_lst *lst)
{
	int	i;
	int	c;

	i = 0;
	c = ' ';
	while (lst->str[i] && (c != ' ' || lst->str[i] != ' '))
	{
		if (lst->str[i] == c)
			c = ' ';
		else if (lst->str[i] == 39 || lst->str[i] == 34)
			c = lst->str[i];
		i++;
	}
	while (lst->str[i])
	{
		lst->str[i] = '\0';
		i++;
	}
}

int	ft_cleanfile(t_lst *lst)
{
	char	*to_free;

	lst_remove_spaces(lst);
	if (lst_remove_quotes(lst) < 0)
		return (-1);
	to_free = lst->str;
	lst->str = ft_strpos(lst->str);
	if (!lst->str)
		return (-1);
	free(to_free);
	return (1);
}
