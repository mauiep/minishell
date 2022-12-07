/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:44:05 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 13:47:05 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args, t_mini *data)
{
	if (args && args[1] && args[2])
	{
		ft_putstr_fd(RED, 2);
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		ft_putstr_fd(RESET, 2);
		data->g_error = 1;
		return (1);
	}
	else if (!args[1] || !ft_strcmp("~", args[1])
		|| !ft_strcmp("--", args[1]))
	{
		data->home = ft_get_env_var("HOME", data);
		if (!data->home)
		{
			ft_putstr_fd(RED, 2);
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			ft_putstr_fd(RESET, 2);
			data->g_error = 1;
			return (1);
		}
		return (ft_cd_error_manager(data->home, data));
	}
	return (ft_cd_check_if_arg_is_dash(args, data));
}
