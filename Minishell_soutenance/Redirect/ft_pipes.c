/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:16:54 by admaupie          #+#    #+#             */
/*   Updated: 2022/12/06 16:38:32 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_pipes_else_else(t_mini *data, int nb_pipes)
{
	if (data->list[data->i] == 0)
	{
		signal(SIGINT, sig_null);
		signal(SIGINT, SIG_DFL);
		ft_handle_pipe(data->pipefd, data->pipes_left, nb_pipes, &data->fd_in);
		ft_close_pipes(data->pipefd, nb_pipes);
		if (ft_handle_redirections(data->start_lst, data) == -1)
			return (-1);
		if (ft_handle_exec(data->start_lst, data) == -1)
			return (-1);
	}
	return (1);
}

static int	ft_pipes_else(t_lst *lst, int nb_pipes, t_mini *data, char **args)
{
	while (lst && lst->str)
	{
		lst = data->start_lst;
		if (nb_pipes == 0 && ft_is_built_in(args, data))
			return (free_pipe_array(data->pipefd, nb_pipes),
				ft_free(args), free(data->list), 1);
		data->list[data->i] = fork();
		signal(SIGINT, SIG_IGN);
		if (ft_pipes_else_else(data, nb_pipes) == -1)
			return (-1);
		data->i++;
		data->pipes_left--;
		lst = ft_next_pipe(data->start_lst);
		if (lst)
			data->start_lst = lst->next;
	}
	ft_free(args);
	return (0);
}

int	ft_pipes(t_lst *lst, int nb_pipes, t_mini *data)
{
	int		init;
	int		error;

	data->dup = 1;
	if (lst->token != 0)
		data->dup = 0;
	init = ft_init_pipe_var(data, nb_pipes, lst);
	if (init == 0)
		return (0);
	else if (init == -1)
		return (free_pipe_array(data->pipefd, nb_pipes), -1);
	if (!ft_handle_heredoc(lst, data))
		return (-1);
	data->splitargs = ft_splitargs(lst);
	if (!data->splitargs)
		return (free_pipe_array(data->pipefd, nb_pipes), -1);
	error = ft_pipes_else(lst, nb_pipes, data, data->splitargs);
	if (error == 1 || error == -1)
		return (error);
	ft_close_pipes(data->pipefd, nb_pipes);
	free_pipe_array(data->pipefd, nb_pipes);
	ft_wait_procs(data->i, data->list, data);
	return (1);
}

static int	ft_wait_procs_else(t_mini *data, int status)
{
	if (WIFSIGNALED(status))
	{
		data->g_error = WTERMSIG(status);
		if (data->g_error != 130)
			data->g_error += 128;
	}
	return (1);
}

int	ft_wait_procs(int ac, pid_t *list, t_mini *data)
{
	int		i;
	int		status;
	pid_t	w;

	i = 0;
	while (i < ac)
	{
		w = waitpid(list[i], &status, 0);
		if (w == -1)
			exit(EXIT_FAILURE);
		if (WIFEXITED(status))
			data->g_error = WEXITSTATUS(status);
		i += ft_wait_procs_else(data, status);
	}
	if (data->g_error == 130)
		ft_putchar_fd('\n', 2);
	free(list);
	return (0);
}
