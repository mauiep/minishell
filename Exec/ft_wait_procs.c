/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_procs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 01:27:19 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/08 01:31:39 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
