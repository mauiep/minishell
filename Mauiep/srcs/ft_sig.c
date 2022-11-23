#include "minishell.h"

void	sigd_handler(int i)
{
	(void)i;
	ft_free_all(g_vrac.darr);
	free_pipe_array(g_vrac.pipefd, g_vrac.nb_pipes);
}
