/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:11:42 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/21 15:08:30 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_mini *data)
{
	int	i;

	if (!data->cmd[1])
	{
		ft_sort_and_print_env(data);
		return (1);
	}
	i = 1;
	while (data->cmd[i])
	{
		if (!ft_check_export_var(data->cmd[i]))
		{
			ft_putstr_fd(RED, 2);
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(data->cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ft_putstr_fd(RESET, 2);
		}
		else
			ft_add_env_var(data, i);
		i++;
	}
}