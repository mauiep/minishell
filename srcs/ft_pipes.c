/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikotikcho <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:47:33 by nikotikch         #+#    #+#             */
/*   Updated: 2022/07/25 17:59:39 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipes_left(t_lst *lst)
{
	int	pipes;

	pipes = 0;
	if (lst == 0)
		return (-1);
	while (lst->next)
	{
		if (lst->next->token == 1)
			pipes++;
		lst = lst->next;
	}
	return (pipes);
}

char	*ft_pipes(t_lst *lst, int nb_pipes, t_dynarray *darr)
{
	int		**pipefd;
	int		i;
	pid_t	list[nb_pipes + 1];
//
//	lst->str = "ls -la fsdljgod"
//	lst->token = 0 string
//				= 1 pipe
//				= 2 >
//				= 3 <
//				= 4 >>
//				= 5 <<
//	argv = splitargs(lst->str)
//
	pipefd = create_pipe_arr(nb_pipes);
	if (!pipefd)
		return (NULL);
	i = 0;
	printf("nb_pipes = %d\n", nb_pipes);
	while (lst)
	{
		if (lst->token == 0 && lst->str != NULL)
		{
			dprintf(1, "i = %d\n TOKEN = %s\n", i, lst->str);
			list[i] = fork();
			if (list[i] == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				if (i != 0)
					dup2(pipefd[i - 1][0], STDIN_FILENO);
				if (i != nb_pipes)
					dup2(pipefd[i][1], STDOUT_FILENO);
				ft_close_pipes(nb_pipes, pipefd);
				printf("DARR darr->list = %p\nDARR darr->nb_cells = %ld\n", darr->list, darr->nb_cells);
				if (ft_find_bin(ft_splitargs(lst)[0], ft_getenvval("PATH", darr->list,
					darr->nb_cells, 1), ft_splitargs(lst), darr->list) == NULL) //A FINIR APRES
					return (dprintf(2, "BAD BAD\n"), NULL);
			}
			printf("darr->LIST = %p\n", darr->list);
			i++;
		}
		lst = lst->next;
	}
	ft_close_pipes(nb_pipes, pipefd);
	ft_wait_procs(nb_pipes, list);
	free_pipe_array(pipefd, nb_pipes);
	return (NULL);
}

int	ft_close_pipes(int ac, int **pipefd)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
	return (0);
}

int	ft_close_unused_fd(int nb_cmd, int **pipefd, int i)
{
	int	x;
	int	y;

	x = 0;
	while (x < nb_cmd)
	{
		y = 0;
		while (y < 2)
		{
			if (i == 0)
				if (x != 0 || y != 1)
					close(pipefd[x][y]);
			if (i < nb_cmd - 1 && i != 0)
				if ((x != i - 1 || y != 0) && (x != i || y != 1))
					close(pipefd[x][y]);
			if (i == nb_cmd - 1)
				if ((x != i || y != 0))
					close(pipefd[x][y]);
			y++;
		}
		x++;
	}
	return (0);
}

int	ft_wait_procs(int ac, pid_t *list)
{
	int i;
	int status;
	pid_t w;

	i = 0;
	while (i < ac + 1)
	{
		w = waitpid(list[i], &status, 0);
		printf("status = %d\n", status);
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
