/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:16:54 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/18 19:16:57 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*ft_next_pipe(t_lst *lst)
{
	while (lst && lst->token != 1)
		lst = lst->next;
	return (lst);
}

int	ft_pipes_left(t_lst *lst)
{
	int	pipes;

	pipes = 0;
	if (!lst)
		return (-1);
	while (lst->next)
	{
		if (lst->next->token == 1)
			pipes++;
		lst = lst->next;
	}
	return (pipes);
}

int	ft_pipes(t_lst *lst, int nb_pipes, t_mini *data)
{
	int		**pipefd;
	int		i;
	pid_t	list[nb_pipes + 1];
	int		pipes_left;
	int		fd_in;
	t_lst	*start_lst;

	pipes_left = nb_pipes;
	pipefd = create_pipe_arr(nb_pipes);
	i = 0;
	if (!pipefd)
		return (printf("FD_ERR\n"), 0);
	start_lst = lst;
	while (lst && lst->str)
	{
		lst = start_lst;
		list[i] = fork();
		if (list[i] == 0)
		{
			ft_handle_pipe(pipefd, pipes_left, nb_pipes, &fd_in);
			ft_close_pipes(pipefd, nb_pipes);// Cette fonction close tous les fd des pipes
			if (ft_handle_redirections(start_lst, data) == -1)// Dans cette fonction les stdin et stdout sont edit selon les redirr
				return (-1);
			if (ft_handle_exec(start_lst, data) == -1)// Dans cette fonction lance l'exec sur start_lst qui contient la commande
				return (-1);
		}
		i++;
		pipes_left--;
		lst = ft_next_pipe(start_lst);
		if (lst)
			start_lst = lst->next;// On met le pointeur start_lst sur la prochaine commande
	}
	ft_close_pipes(pipefd, nb_pipes);// A voir si on a vraiment besoin de close les fd 2 fois
	free_pipe_array(pipefd, nb_pipes);
	ft_wait_procs(i, list);
	return (1);
}

int	ft_wait_procs(int ac, pid_t *list)
{
	int i;
	int status;
	pid_t w;

	i = 0;
	while (i < ac)
	{
		w = waitpid(list[i], &status, 0);//	printf("status = %d\n", status); Recuperer le status dans $? ???
		if (w == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
		{
			//printf("terminé, code=%d\n", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			//printf("tué par le signal %d\n", WTERMSIG(status));
		}
		else if (WIFSTOPPED(status))
		{
			//printf("arrêté par le signal %d\n", WSTOPSIG(status));
		}
		else if (WIFCONTINUED(status))
		{
			//printf("relancé\n");
		}
		i++;
	}
	return (0);
}
