/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_else.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 01:04:47 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/08 05:14:07 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_all_exec(t_mini *data)
{
	if (data->line)
		free(data->line);
	if (data->prompt)
		free(data->prompt);
	if (data->splitargs)
		ft_free(data->splitargs);
	if (data->list)
		free(data->list);
	if (data->lst)
		free_lst(data->lst);
	if (data->pipefd)
		free_pipe_array(data->pipefd, data->nb_pipes);
}

int	program_exec(char **args, t_mini *data)
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
