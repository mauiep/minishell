#include "minishell.h"

int	ft_handle_pipe(int **pipefd, int pipes_left, int nb_pipes, int *fd_in)
{
	int	fd_out;

	if (pipes_left != nb_pipes)
		*fd_in = dup2(pipefd[nb_pipes - pipes_left - 1][0], STDIN_FILENO);
	if (*fd_in == -1)
		return (dprintf(2, "FD_ERR\n"), ft_close_pipes(pipefd, nb_pipes),
				free_pipe_array(pipefd, nb_pipes), -1);
	if (pipes_left != 0)
		fd_out = dup2(pipefd[nb_pipes - pipes_left][1], STDOUT_FILENO);
	if (fd_out == -1)
		return (dprintf(2, "FD_ERR\n"), free_pipe_array(pipefd, nb_pipes), -1);
	return (fd_out);
}
