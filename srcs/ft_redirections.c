#include "minishell.h"

int	ft_handle_redirections(t_lst *lst)
{
	while (lst && lst->token != 1)
	{
		if (lst->token == 2)
		{
			dprintf(2, "DUP 2 TOKEN = 2\n");
			dup2(ft_open_create(lst->next->str, 0), STDOUT_FILENO); //A SECURISER
			lst = lst->next;
		}
		if (lst->token == 3)
		{
			dprintf(2, "DUP 2 TOKEN = 3\n");
			dup2(ft_open_create(lst->prev->str, 0), STDOUT_FILENO);
		}
		if (lst->token == 4)
		{
			dprintf(2, "DUP 2 TOKEN = 4\n");
			dup2(ft_open_create(lst->next->str, 1), STDOUT_FILENO);
			lst = lst->next;
		}
		lst = lst->next;
	}
	return (0);
}
