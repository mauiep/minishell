/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_directory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:13:17 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 13:47:13 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_data_and_set_null(t_mini *data)
{
	if (data->converted_path)
	{
		free(data->converted_path);
		data->converted_path = NULL;
	}
	if (data->home)
	{
		free(data->home);
		data->home = NULL;
	}
}

int	ft_change_directory(char *path, t_mini *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_get_env_var("PWD", data);
	if (!chdir(path))
	{
		if (pwd)
		{
			ft_change_env(pwd, "OLDPWD", data);
			free(pwd);
		}
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (-1);
		if (pwd)
		{
			ft_change_env(pwd, "PWD", data);
			free(pwd);
		}
		ft_free_data_and_set_null(data);
		return (1);
	}
	free(pwd);
	return (0);
}
