/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:17:39 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/25 14:45:40 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- Le nombre de pipe
**	
**	========================================
**	
**	Cette fonction sert a [a toi d'ecrire]
*/

int	**create_pipe_arr(int nb_pipes)
{
	int	i;
	int	**pipefd;
	int	ret;

	pipefd = malloc(nb_pipes * sizeof(int *));
	if (pipefd == NULL)
		return (NULL);
	i = -1;
	while (++i < nb_pipes)
	{
		pipefd[i] = malloc(8);
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
	return (pipefd);
}

/*
**	Cette fonction prend en parametre :
**	
**	- [a toi d'ecrire]
**	
**	========================================
**	
**	Cette fonction sert a free les tableau de pipe
*/

void	free_pipe_array(int **pipefd, int nb_pipes)
{
	int	i;

	if (!pipefd)
		return ;
	i = -1;
	while (++i < nb_pipes)
	{
		if (!pipefd[i])
			return ;
		free(pipefd[i]);
	}
	free(pipefd);
}

/*
**	Cette fonction prend en parametre :
**	
**	- [a toi d'ecrire]
**	- Le nombre de pipe
**	========================================
**	
**	Cette fonction sert a close tout les pipefd
*/

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
