/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_check_if_arg_is_dash.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:10:47 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 13:46:50 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_check_if_arg_is_dash(char **args, t_mini *data)
{
	char	*pwd;

	pwd = NULL;
	if (!ft_strcmp(args[1], "-"))
	{
		pwd = ft_get_env_var("OLDPWD", data);
		if (pwd)
		{
			ft_cd_error_manager(pwd, data);
			free(pwd);
		}
		pwd = ft_get_env_var("PWD", data);
		if (pwd)
		{
			ft_putendl_fd(pwd, 1);
			free(pwd);
		}
		return (1);
	}
	data->converted_path = ft_convert_arg_to_path(args, data);
	return (ft_cd_error_manager(data->converted_path, data));
}
