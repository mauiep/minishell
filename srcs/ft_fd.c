#include "minishell.h"

int	**create_pipe_arr(int nb_pipes)
{
	int	i;
	int	**pipefd;

	pipefd = malloc(nb_pipes * sizeof(int*));
	if (pipefd == NULL)
		return (NULL);
	i = -1;
	while (++i < nb_pipes)
	{
		pipefd[i] = malloc(8);
		if (pipefd[i] == NULL)
		{
			while (--i >= 0)
				free(pipefd[i]);
			free(pipefd);
			return (NULL);
		}
	}
	i = -1;
	while (++i < nb_pipes)
		pipe(pipefd[i]);
	return (pipefd);
}

void	free_pipe_array(int **pipefd, int	nb_pipes)
{
	int	i;

	i = -1;
	while (++i < nb_pipes)
		free(pipefd[i]);
	free(pipefd);
}
