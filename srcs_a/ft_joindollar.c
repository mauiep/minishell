/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joindollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:21:18 by admaupie          #+#    #+#             */
/*   Updated: 2022/10/26 18:31:20 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strjoindollar(t_lst *l, char *var, int k, int dollar)
{
	int		i;
	char	*tmp;
	char	*new;

	i = ft_strlen(var);
	tmp = l->str;
	new = malloc(sizeof(char) * (ft_strlen(tmp) + i + 1 - dollar));
	if (!new)
		exit(-1);
	i = -1;
	while (++i >= 0 && tmp[i] && i < k)
		new[i] = tmp[i];
	i--;
	while (++i && var[i - k])
		new[i] = var[i - k];
	i--;
	k--;
	while (++i && ++k && tmp[k + dollar])
		new[i] = tmp[k + dollar];
	new[i] = '\0';
	free(tmp);
	tmp = NULL;
	l->str = new;
	return (1);
}

int	ft_replacedollar(t_lst *l, int k, int c, t_dynarray *darr)
{
	int		i;
	int		dollar;
	char	*var;

	(void)c;
	var = NULL;
	dollar = 0;
	k++;
	while (l->str[k + dollar] && l->str[k + dollar] != '\t'
		&& l->str[k + dollar] != 39 && l->str[k + dollar] != ' '
		&& l->str[k + dollar] != 34)
		dollar++;
	if (dollar && dollar++)
		var = ft_getenvval(l->str + k, darr->list, darr->nb_cells, 0);
	else if (l->str[k] == 34 || l->str[k] == SIMPLE_QUOTE)
	{
		var = "$";
		dollar++;
	}
	i = ft_strlen(var);
	if (!i)
		var = "";
	ft_strjoindollar(l, var, k - 1, dollar);
	return (i - 1);
}
