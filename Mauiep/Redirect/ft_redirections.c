#include "minishell.h"

int	ft_handle_redirections(t_lst *lst, t_mini *data)
{
	while (lst && lst->token != 1)
	{
		if (lst->token == 2 || lst->token == 3 || lst->token == 4 || lst->token == 5)
		{
			if (ft_open_dup(lst, lst->token, data) == -1)
				return (-1);
			lst = lst->next;
		}
		lst = lst->next;
	}
	return (0);
}

/*

	Dans cette fonction, lst pointe sur le maillon contenant la redirection,
	lst->token varie selon le type de redirection.
	
	Le fichier se trouvant dans lst->next->str est ouvert et
	on dup2 le fd sur STDIN ou STDOUT selon la redirection

*/

int	ft_open_dup(t_lst *lst, int token, t_mini *data)
{
	int	fd;

	fd = -1;
	if (ft_cleanfile(lst->next) < 0)// Retirer les quotes et les espaces du nom de fichier
		return (-1);
	if (token == 2)// REDIREC '>'
	{
		fd = ft_open_create(lst->next->str, 0, 2);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (printf("error : dup2\n"), close(fd), -1);
	}
	else if (token == 3)// REDIREC '<'
	{
		fd = ft_open_create(lst->next->str, 0, 3);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (printf("error : dup2\n"), close(fd), -1);
	}
	else if (token == 4)// REDIREC '>>'
	{
		fd = ft_open_create(lst->next->str, 1, 4);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDOUT_FILENO) < 0)
			return (printf("error : dup2\n"), close(fd), -1);
	}
	else if (token == 5)// REDIREC '<<'
	{
		fd = ft_heredoc(lst->next->str, data);
		if (fd == -1)
			return (printf("no fd heredoc\n"), -1);
		close(fd);
		fd = open("temp", O_RDONLY);
		if (fd == -1)
			return (printf("no fd heredoc\n"), -1);
		unlink("temp");// Unlink permet que le file soit delete une fois le fd close
		if (dup2(fd, STDIN_FILENO) < 0)
			return (printf("error : dup2\n"), close(fd), -1);
	}
	close(fd);
	return (fd);
}
