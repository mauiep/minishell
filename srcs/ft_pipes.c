#include "minishell.h"

char *ft_pipes(int ac, char **argv, t_dynarray *darr)
{
	int pipefd[(ac / 3) - 1][2];
	int i;
	pid_t list[ac / 3];
	char *nul;
	int	fd_in;

	nul = NULL;
	i = -1;
	while (++i < (ac / 3) - 1)
		pipe(pipefd[i]);
	i = -1;
	fd_in = dup(STDIN_FILENO);
	while (++i < ac / 3)
	{
		list[i] = fork();
		if (list[i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (i != 0)
				dup2(pipefd[0][0], STDIN_FILENO);
			if (i + 1 != ac / 3)
				dup2(pipefd[0][1], STDOUT_FILENO);
			else
				dup2(fd_in, STDOUT_FILENO);
			push_dynarray(darr, &nul, 1, 0);
			if (ft_find_bin(argv[i * 3], ft_getenvval("PATH", darr->list, darr->nb_cells), &argv[i * 3], darr->list) == NULL)
				return (NULL);
		}
	}
	ft_wait_procs(ac, list);
	ft_close_pipes(ac, (int **)pipefd);
	return NULL;
}

int ft_close_pipes(int ac, int **pipefd)
{
	int i;

	i = 0;
	while (i < (ac / 3) - 1)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
	return (0);
}

int ft_wait_procs(int ac, pid_t *list)
{
	int i;
	int status;
	pid_t w;

	i = 0;
	while (i < ac / 3)
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
