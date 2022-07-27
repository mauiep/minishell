#include "minishell.h"

void	sigd_handler(int i)
{
	free_dynarray(g_safe.darr);
	free_pipe_array(pipefd, nb_pipes);
}
