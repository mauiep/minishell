/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:49:42 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 13:55:07 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_equal_in_var(t_mini *data, int i)
{
	int	j;

	j = 0;
	while (data->env_tab[i][j])
	{
		if (data->env_tab[i][j] == '=')
			return (1);
		j++;
	}
	return (0);
}

void	ft_env(t_mini *data)
{
	int	i;

	i = 0;
	while (data->env_tab[i])
	{
		if (ft_is_equal_in_var(data, i))
		{
			ft_putstr_fd(data->env_tab[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	data->g_error = 0;
}
