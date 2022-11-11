#include "../minishell.h"

int	ft_handle_redirections(t_lst *lst)
{
	while (lst && lst->token != 1)
	{
		if (lst->token == 2 || lst->token == 3 || lst->token == 4)
		{
			if (ft_open_dup(lst, lst->token) == -1)
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
		if (!ft_cleanfile(lst->next))
			return (-1);
		fd = ft_open_create(lst->next->str, 0, 2);
		if (fd != -1 && dup2(fd, STDOUT_FILENO) == -1)
			return (close(fd), dprintf(2, "dup 2 error\n"), -1);
		close(fd);
	}
	else if (token == 3)
	{
		dprintf(2, "DUP2 token 3\n");
		fd = ft_open_create(lst->next->str, 0, 3);
		if (fd != -1 && dup2(fd, STDIN_FILENO) == -1)
			return (close(fd), dprintf(2, "dup 2 error\n"), -1);
	}
	else
	{
		dprintf(2, "DUP2 token 4\n");
		fd = ft_open_create(lst->next->str, 1, 4);
		if (fd != -1 && dup2(fd, STDOUT_FILENO) == -1)
			return (close(fd), dprintf(2, "dup 2 error\n"), -1);
	}
	if (fd != -1)
		close(fd);
	return (fd);
}
