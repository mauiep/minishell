#include "minishell.h"

int	ft_handle_redirections(t_lst *lst)
{
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
	return (0);
}
