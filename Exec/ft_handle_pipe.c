/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:17:25 by admaupie          #+#    #+#             */
/*   Updated: 2022/12/08 01:46:29 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- le tableau de pipe
**	- Le nombre de pipe restant
**	- Le nombre de pipe total
**	- [a toi d'ecrire]
**	
**	========================================
**	
**	Cette fonction s'occupe de la gestion des pipe,
**   On a un double tableau pipefd qui recevra les STDIN (pipefd[n][0])
**  Et STDOUT (pipefd[n][1])
** Fd_in et fd_out permet de garder en memoire quel fd close en cas d'erreur
*/

int	ft_handle_pipe(int **pipefd, int pipes_left, int nb_pipes, int *fd_in)
{
	int	fd_out;

	if (pipes_left != nb_pipes)
	{
		*fd_in = dup2(pipefd[nb_pipes - pipes_left - 1][0], STDIN_FILENO);
		if (*fd_in == -1)
			return (ft_close_pipes(pipefd, nb_pipes),
				free_pipe_array(pipefd, nb_pipes), -1);
		else
			close(pipefd[nb_pipes - pipes_left - 1][0]);
	}
	if (pipes_left != 0)
	{
		fd_out = dup2(pipefd[nb_pipes - pipes_left][1], STDOUT_FILENO);
		if (fd_out == -1)
			return (ft_close_pipes(pipefd, nb_pipes),
				close(*fd_in), free_pipe_array(pipefd, nb_pipes), -1);
		else
			close(pipefd[nb_pipes - pipes_left][1]);
	}
	return (fd_out);
}
