/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_and_print_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:45:53 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 13:56:04 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_swap(char **temp_env, int j)
{
	char	*tmp;

	tmp = temp_env[j];
	temp_env[j] = temp_env[j + 1];
	temp_env[j + 1] = tmp;
}

static void	ft_print_env(char **temp_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (temp_env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		while (temp_env[i][j] && !(temp_env[i][j] == '='))
		{
			write(1, &temp_env[i][j], 1);
			j++;
		}
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(temp_env[i] + (j + 1), 1);
		ft_putstr_fd("\"\n", 1);
		j = 0;
		i++;
	}
	ft_free(temp_env);
}

void	ft_sort_and_print_env(t_mini *data)
{
	char	**temp_env;
	int		i;
	int		j;

	temp_env = ft_create_temp_env(data, ft_env_len(data));
	if (!temp_env)
	{
		ft_free(temp_env);
		return ;
	}
	i = 0;
	j = 0;
	while (temp_env[i])
	{
		while (temp_env[j + 1])
		{
			if (ft_strcmp(temp_env[j], temp_env[j + 1]) > 0)
				ft_swap(temp_env, j);
			j++;
		}
		i++;
		j = 0;
	}
	ft_print_env(temp_env);
}
