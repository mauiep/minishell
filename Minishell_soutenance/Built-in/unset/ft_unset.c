/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 02:56:29 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 13:56:27 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args, t_mini *data)
{
	int	env_index;
	int	i;

	if (!args[1])
		return (1);
	env_index = 0;
	i = -1;
	while (args[++i])
	{
		if (!ft_check_unset_arg(args[i]))
		{
			ft_putstr_fd(RED, 2);
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ft_putstr_fd(RESET, 2);
			return (data->g_error = 1, 0);
		}
		env_index = ft_find_env(args[i], data);
		if (env_index != -1)
			if (data->env_tab[env_index])
				data->env_tab = ft_realloc_env(env_index, data);
	}
	return (data->g_error = 0, 1);
}
