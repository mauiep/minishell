#include "minishell.h"

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("env[%d] = %s\n", i, envp[i]);
		i++;
	}
}

void	ft_dyn_env(t_dynarray *darr)
{
	uint64_t	i;

	i = 0;
	while (i < darr->nb_cells)
	{
		printf("list[%lu] = %s\n", i, ((char**)darr->list)[i]);
		i++;
	}
}

void	ft_print_pipes(int **pipefd, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		printf("-----------------------------\n");
		printf("pipefd[%d][0] = %d\n", i, pipefd[i][0]);
		printf("pipefd[%d][1] = %d\n", i, pipefd[i][1]);
		printf("-----------------------------\n");
		i++;
	}
}
