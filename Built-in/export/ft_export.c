/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:11:42 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/23 14:16:50 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **args, t_mini *data)
{
	int	i;

	if (!args[1])
	{
		ft_sort_and_print_env(data);
		return (1);
	}
	i = 1;
	while (args[i])
	{
		if (!ft_check_export_var(args[i]))
		{
			ft_error("minishell: export: `", RED, 0);
			ft_error(args[i], RED, 0);
			return (ft_error(": not a valid identifier\n", RED, 0));
		}
		else
			ft_add_env_var(args[i], data);
		i++;
	}
}