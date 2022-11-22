/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:16:54 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/22 12:28:59 by ceatgie          ###   ########.fr       */
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

static int	ft_init_pipe_var(t_mini *data, int nb_pipes, t_lst *lst)
{
	data->pipes_left = nb_pipes;
	data->pipefd = create_pipe_arr(nb_pipes);
	if (!data->pipefd)
		return (0);
	data->i = 0;
	data->start_lst = lst;
	data->fd_in = 0;
	data->list = malloc(sizeof(pid_t) * (nb_pipes + 1));
	if (!data->list)
		return (-1);
}

int	ft_pipes(t_lst *lst, int nb_pipes, t_mini *data)
{
	int	init;
	char **args;
	
	init = ft_init_pipe_var(data, nb_pipes, lst);
	if (init == 0)
		return (printf("FD_ERR\n"), 0);
	else if (init == -1)
		return (-1);
	args = ft_splitargs(lst);
	while (lst && lst->str)
	{
		lst = data->start_lst;
		if (nb_pipes == 0 && ft_is_built_in(args, data))
		{
			return (1);
		}
		data->list[data->i] = fork();
		if (data->list[data->i] == 0)
		{
			 ft_handle_pipe(data->pipefd, data->pipes_left, nb_pipes, &data->fd_in);
			ft_close_pipes(data->pipefd, nb_pipes);// Cette fonction close tous les fd des pipes
			if (ft_handle_redirections(data->start_lst, data) == -1)// Dans cette fonction les stdin et stdout sont edit selon les redirr
				return (-1);
			if (ft_handle_exec(data->start_lst, data) == -1)// Dans cette fonction lance l'exec sur start_lst qui contient la commande
				return (-1);
		}
		data->i++;
		data->pipes_left--;
		lst = ft_next_pipe(data->start_lst);
		if (lst)
			data->start_lst = lst->next;// On met le pointeur start_lst sur la prochaine commande
	}
	ft_close_pipes(data->pipefd, nb_pipes);// A voir si on a vraiment besoin de close les fd 2 fois
	free_pipe_array(data->pipefd, nb_pipes);
	ft_wait_procs(data->i, data->list);
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
			printf("terminé, code=%d\n", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			printf("tué par le signal %d\n", WTERMSIG(status));
		}
		else if (WIFSTOPPED(status))
		{
			printf("arrêté par le signal %d\n", WSTOPSIG(status));
		}
		else if (WIFCONTINUED(status))
		{
			printf("relancé\n");
		}
		i++;
	}
	return (0);
}
