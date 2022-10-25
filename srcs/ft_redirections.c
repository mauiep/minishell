#include "minishell.h"

int	ft_handle_redirections(t_lst *lst)
{
	while (lst && lst->token != 1)
	{
		if (lst->token == 2)
		{
			if (ft_open_dup(lst, 2) == -1)
				return (-1);
			lst = lst->next;
		}
		if (lst->token == 3)
		{
			if (ft_open_dup(lst, 3) == -1)
				return (-1);
			lst = lst->next;
		}
		if (lst->token == 4)
		{
			if (ft_open_dup(lst, 4) == -1)
				return (-1);
			lst = lst->next;
		}
		lst = lst->next;
	}
	return (0);
}

int	ft_open_dup(t_lst *lst, int token)
{
	int	fd;

	fd = -1;
	if (token == 2)
	{
		dprintf(2, "DUP2 token 2\n");
		fd = ft_open_create(lst->next->str, 0);
		if (fd != -1)
			if (dup2(fd, STDOUT_FILENO) == -1)
				return (close(fd), dprintf(2, "dup 2 error\n"), -1);
		close(fd);
	}
	else if (token == 3)
	{
		dprintf(2, "DUP2 token 3\n");
		fd = ft_open_create(lst->next->str, 0);
		if (fd != -1)
			if (dup2(fd, STDIN_FILENO) == -1)
				return (close(fd), dprintf(2, "dup 2 error\n"), -1);
	}
	else
	{
		dprintf(2, "DUP2 token 4\n");
		fd = ft_open_create(lst->next->str, 1);
		if ( fd != -1)
			if (dup2(fd, STDOUT_FILENO) == -1)
				return (close(fd), dprintf(2, "dup 2 error\n"), -1);
	}
	close(fd);
	return (fd);
}
