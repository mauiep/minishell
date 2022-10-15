#include "minishell.h"

int	ft_handle_pipe(int **pipefd, int pipes_left, int nb_pipes, int *fd_in)
{
	int	fd_out;

	if (pipes_left != nb_pipes)
	{
		*fd_in = dup2(pipefd[nb_pipes - pipes_left - 1][0], STDIN_FILENO);
		if (*fd_in == -1)
			return (dprintf(2, "FD_ERR\n"), ft_close_pipes(pipefd, nb_pipes),
				free_pipe_array(pipefd, nb_pipes), -1);
		else
			close(pipefd[nb_pipes - pipes_left - 1][0]);
	}
/*separation*/
	if (pipes_left != 0)
	{
		dprintf(2, "DUP 2 TOKEN = 1\n");
		fd_out = dup2(pipefd[nb_pipes - pipes_left][1], STDOUT_FILENO);
		if (fd_out == -1)
			return (dprintf(2, "FD_ERR\n"), ft_close_pipes(pipefd, nb_pipes),
				close(*fd_in), free_pipe_array(pipefd, nb_pipes), -1);
		else
			close(pipefd[nb_pipes - pipes_left][1]);
	}
	return (fd_out);
}
//	lst->str = "ls -la fsdljgod"
//	lst->token = 0 string
//				= 1 pipe
//				= 2 >
//				= 3 <
//				= 4 >>
//				= 5 <<
//	argv = splitargs(lst->str)


