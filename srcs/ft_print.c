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
