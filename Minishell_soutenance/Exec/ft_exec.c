/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:09:01 by admaupie          #+#    #+#             */
/*   Updated: 2022/12/07 13:57:17 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	program_exec(char **args, t_mini *data)
{
	if (access(args[0] + 2, F_OK & X_OK) == 0)
	{
		execve(args[0] + 2, args, data->env_tab);
		ft_putstr_fd(RED, 2);
		perror("execve");
		ft_putstr_fd(RESET, 2);
		data->g_error = 0;
	}
	else
	{
		ft_error("minishell: ", RED, 42);
		ft_error(args[0], RED, 42);
		ft_error(": No such file or directory", RED, 42);
		ft_error("\n", RED, 42);
		ft_free_all(data);
		ft_free(args);
		data->g_error = 127;
	}
	return (data->g_error);
}

static void	ft_check_if_executable(char **args, t_mini *data)
{
	if (ft_strncmp(args[0], "./", 2) == 0)
		exit (program_exec(args, data));
}

static void	ft_handle_exec_error(char **args, t_mini *data)
{
	ft_error(args[0], RED, 42);
	ft_error(" : command not found\n", RED, 42);
	ft_free_all(data);
	ft_free(args);
	data->g_error = 127;
	exit(127);
}

static void	ft_handle_exec_else(t_lst *lst, char **args, t_mini *data)
{
	char	*tmp;

	tmp = NULL;
	if (lst->token == 0 && lst->str != NULL)
	{
		if (ft_is_built_in(args, data))
		{
			ft_free_all(data);
			ft_free(args);
			exit (0);
		}
		ft_check_if_executable(args, data);
		tmp = ft_find_bin(args[0], ft_get_env_var("PATH", data),
				args, data->env_tab);
		if (!tmp)
			ft_handle_exec_error(args, data);
	}
}

int	ft_handle_exec(t_lst *lst, t_mini *data)
{
	char	**args;

	if (lst->token != 0)
	{
		ft_free_all(data);
		exit(0);
	}
	args = ft_splitargs(lst);
	if (!args)
		return (-1);
	while (args && lst && lst->token != 1)
	{
		ft_handle_exec_else(lst, args, data);
		lst = lst->next;
	}
	return (0);
}
