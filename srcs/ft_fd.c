#include "minishell.h"

int	**create_pipe_arr(int nb_pipes)
{
	int	i;
	int	**pipefd;
	int	ret;

	pipefd = malloc(nb_pipes * sizeof(int*));
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
			return (close_pipe_array(pipefd, i), NULL);
	}
	return (pipefd);
}

int	close_pipe_array(int **pipefd, int	nb_pipes)
{
	int	i;

	i = -1;
	while (++i < nb_pipes)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
	}
	return (0);
}

void	free_pipe_array(int **pipefd, int	nb_pipes)
{
	int	i;

	i = -1;
	while (++i < nb_pipes)
		free(pipefd[i]);
	free(pipefd);
}
