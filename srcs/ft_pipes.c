#include "minishell.h"

t_lst	*ft_next_pipe(t_lst *lst)
{
	while (lst && lst->token != 1)
		lst = lst->next;
	return (lst);
}

int	ft_pipes_left(t_lst *lst)
{
	int	pipes;

	pipes = 0;
	if (!lst)
		return (-1);
	while (lst->next)
	{
		if (lst->next->token == 1)
			pipes++;
		lst = lst->next;
	}
	return (pipes);
}

char	*ft_pipes(t_lst *lst, int nb_pipes, t_dynarray *darr)
{
	int		**pipefd;
	int		i;
	pid_t	list[nb_pipes + 1];
	int		pipes_left;
	int		fd_in;
	t_lst	*start_lst;

	ft_print_list(lst);
	return (NULL);
	printf("NB_PIPES = %d\n", nb_pipes);
	pipes_left = nb_pipes;
	pipefd = create_pipe_arr(nb_pipes);
	if (!pipefd)
		return (printf("FD_ERR\n"), NULL);
	ft_print_pipes(pipefd, nb_pipes);
	start_lst = lst;
	while (lst && lst->str)
	{
		lst = start_lst;
		if (pipes_left > 0)
		{
			ft_handle_pipe(pipefd, pipes_left, nb_pipes, &fd_in);
			pipes_left--;
		}
		while (lst && lst->str && lst->token != 1)
		{
			if (lst->token == 2)
			{
				dup2(ft_open_create(lst->next->str, 0), STDOUT_FILENO); //A SECURISER
				lst = lst->next;
			}
			if (lst->token == 3)
				dup2(ft_open_create(lst->prev->str, 0), STDOUT_FILENO);
			if (lst->token == 4)
			{
				dup2(ft_open_create(lst->prev->str, 1), STDOUT_FILENO);
				lst = lst->next;
			}
			lst = lst->next;
		}
		ft_close_pipes(pipefd, nb_pipes);
		lst = start_lst;
		ft_print_token(*lst);
		i = 0;
		while (lst && lst->token != 1)
		{
			if (lst->token == 0 && lst->str != NULL)
			{
				dprintf(2, "i = %d\n", i);
				list[i] = fork();
				if (list[i] == 0)
				{
					dprintf(2, "EXECUTE STR  = %s\n", lst->str);
					if (ft_find_bin(ft_splitargs(lst)[0], ft_getenvval("PATH", darr,
						darr->nb_cells, 1), ft_splitargs(lst), darr->list) == NULL) //A FINIR APRES
						return (dprintf(2, "BAD BAD\n"), NULL);
				}
				i++;
			}
			lst = lst->next;
		}
		lst = ft_next_pipe(start_lst);
		start_lst = lst->next;
	}
	ft_close_pipes(pipefd, nb_pipes);
	free_pipe_array(pipefd, nb_pipes);
	ft_wait_procs(i, list);
	return (NULL);
}

//
//	lst->str = "ls -la fsdljgod"
//	lst->token = 0 string
//				= 1 pipe
//				= 2 >
//				= 3 <
//				= 4 >>
//				= 5 <<
//	argv = splitargs(lst->str)

int	ft_wait_procs(int ac, pid_t *list)
{
	int i;
	int status;
	pid_t w;

	i = 0;
	while (i < ac + 1)
	{
		w = waitpid(list[i], &status, 0);
		printf("status = %d\n", status);
		if (w == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
		{
			printf("terminé, code=%d\n", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			printf("tué par le signal %d\n", WTERMSIG(status));
		}
		else if (WIFSTOPPED(status))
		{
			printf("arrêté par le signal %d\n", WSTOPSIG(status));
		}
		else if (WIFCONTINUED(status))
		{
			printf("relancé\n");
		}
		i++;
	}
	return (0);
}
