/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_error_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:22:02 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 13:46:59 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_data_and_set_null(t_mini *data)
{
	ft_putstr_fd(RESET, 2);
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

int	ft_cd_error_manager(char *path, t_mini *data)
{
	struct stat	st;

	if (ft_change_directory(path, data))
		return (data->g_error = 0, 1);
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	if (stat(path, &st) == -1)
		ft_putendl_fd(": No such file or directory", 2);
	else if (!S_ISDIR(st.st_mode))
		ft_putendl_fd(": Not a directory", 2);
	else if (!(st.st_mode & S_IXUSR))
		ft_putendl_fd(": Permission denied", 2);
	data->g_error = 1;
	ft_free_data_and_set_null(data);
	return (1);
}
