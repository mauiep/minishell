/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:17:39 by admaupie          #+#    #+#             */
/*   Updated: 2022/12/07 13:57:31 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	**ft_create_pipe_arr_for_no_pipe(void)
{
	int	**pipefd;

	pipefd = malloc(sizeof(int *));
	if (pipefd == NULL)
		return (NULL);
	pipefd[0] = malloc(sizeof(long));
	if (pipefd[0] == NULL)
		return (free(pipefd[0]), free(pipefd), NULL);
	if (pipe(pipefd[0]) == -1)
		return (close(pipefd[0][0]), close(pipefd[0][1]), NULL);
	return (pipefd);
}

int	**create_pipe_arr(int nb_pipes)
{
	int	i;
	int	**pipefd;
	int	ret;

	if (nb_pipes == 0)
		pipefd = ft_create_pipe_arr_for_no_pipe();
	else
	{
		pipefd = malloc(nb_pipes * sizeof(int *));
		i = -1;
		while (++i < nb_pipes)
		{
			pipefd[i] = malloc(sizeof(long));
			if (pipefd[i] == NULL)
				return (free_pipe_array(pipefd, i), NULL);
		}
		i = -1;
		while (++i < nb_pipes)
		{
			ret = pipe(pipefd[i]);
			if (ret == -1)
				return (ft_close_pipes(pipefd, i), NULL);
		}
	}
	return (pipefd);
}

void	free_pipe_array(int **pipefd, int nb_pipes)
{
	int	i;

	if (!pipefd)
		return ;
	if (nb_pipes == 0)
		return (free(pipefd[0]), free(pipefd));
	i = -1;
	while (++i < nb_pipes)
	{
		if (!pipefd[i])
			return ;
		free(pipefd[i]);
	}
	free(pipefd);
}

int	ft_close_pipes(int **pipefd, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
	return (0);
}
