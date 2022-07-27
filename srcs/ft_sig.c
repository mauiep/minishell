#include "minishell.h"

void	sigd_handler(int i)
{
	(void)i;
	dprintf(1, "IN SIG HANDLER\n");
	dprintf(1, "darr = %p\n", g_vrac.darr);
	free_dynarray(g_vrac.darr);
	free_pipe_array(g_vrac.pipefd, g_vrac.nb_pipes);
}
