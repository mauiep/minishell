/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:17:25 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/21 09:26:14 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

	Cette fonction s'occupe de la gestion des pipe,
	on a un double tableau pipefd qui recevra les STDIN (pipefd[n][0]) et STDOUT (pipefd[n][1])
	fd_in et fd_out permet de garder en memoire quel fd close en cas d'erreur

	Return value inutilisee 

*/

int	ft_handle_pipe(int **pipefd, int pipes_left, int nb_pipes, int *fd_in)
{
	int	fd_out;

	if (pipes_left != nb_pipes) // Si on doit modifier la STDIN
	{
		*fd_in = dup2(pipefd[nb_pipes - pipes_left - 1][0], STDIN_FILENO); // On redirige 
		if (*fd_in == -1)
			return (dprintf(2, "FD_ERR\n"), ft_close_pipes(pipefd, nb_pipes),
				free_pipe_array(pipefd, nb_pipes), -1);
		else
			close(pipefd[nb_pipes - pipes_left - 1][0]);
	}
	if (pipes_left != 0) // Et ici on s'occupe de STDOUT
	{
		fd_out = dup2(pipefd[nb_pipes - pipes_left][1], STDOUT_FILENO);
		if (fd_out == -1)
			return (dprintf(2, "FD_ERR\n"), ft_close_pipes(pipefd, nb_pipes),
				close(*fd_in), free_pipe_array(pipefd, nb_pipes), -1);
		else
			close(pipefd[nb_pipes - pipes_left][1]);
	}
	return (fd_out);
}
