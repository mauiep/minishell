/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikotikcho <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:47:33 by nikotikch         #+#    #+#             */
/*   Updated: 2022/07/13 17:11:48 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pipes(int ac, char **argv, t_dynarray *darr)
{
	int		**pipefd;
	int		i;
	pid_t	list[ac + 1];
	char	*nul;

	nul = NULL;
	pipefd = create_pipe_arr(ac);
	if (!pipefd)
		return (NULL);
	i = -1;
	while (++i < ac + 1)
	{
		list[i] = fork();
		if (list[i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (i != 0)
				dup2(pipefd[i - 1][0], STDIN_FILENO);
			if (i != ac)
				dup2(pipefd[i][1], STDOUT_FILENO);
			ft_close_pipes(ac, pipefd);
			push_dynarray(darr, &nul, 1, 0);
			if (ft_find_bin(argv[i * 3], ft_getenvval("PATH", darr->list, darr->nb_cells), &argv[i * 3], darr->list) == NULL)
				return (dprintf(2, "BAD BAD\n"), NULL);
		}
	}
	ft_close_pipes(ac, pipefd);
	ft_wait_procs(ac, list);
	free_pipe_array(pipefd, ac);
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
