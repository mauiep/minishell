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

void	ft_print_token(t_lst token)
{
	dprintf(2, "PRINTING TOKEN:\n");
	dprintf(2, "token->str = %s\n", token.str);
	if (token.next != NULL)
	{
		dprintf(2, "token->next = %s\n", token.next->str);
		dprintf(2, "token->prev = %s\n", token.prev->str);
	}
}

void	ft_print_list(t_lst *token)
{
	while (token != NULL)
	{
		ft_print_token(*token);
		token = token->next;
	}
	if (token == NULL)
		dprintf(2, "PRINTING TOKEN:\n NULL\n");
}
