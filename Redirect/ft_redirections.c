/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:23:51 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/08 01:48:53 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_redirections(t_lst *lst, t_mini *data)
{
	while (lst && lst->token != 1)
	{
		if (lst->token == 2 || lst->token == 3
			|| lst->token == 4 || lst->token == 5)
		{
			if (ft_open_dup(lst, lst->token, data) == -1)
			lst = lst->next;
		}
		lst = lst->next;
	}
	return (0);
}

/*
**
**	Dans cette fonction, lst pointe sur le maillon contenant la redirection,
**	lst->token varie selon le type de redirection.
**	
**	Le fichier se trouvant dans lst->next->str est ouvert et
**	on dup2 le fd sur STDIN ou STDOUT selon la redirection
**
*/

int	ft_open_dup(t_lst *lst, int token, t_mini *data)
{
	int	fd;

	fd = -1;
	if (ft_cleanfile(lst->next) < 0)
		return (-1);
	if (token == 2)
		return (ft_for_token2(lst, data, fd));
	else if (token == 3)
		return (ft_for_token3(lst, data, fd));
	else if (token == 4)
		return (ft_for_token4(lst, data, fd));
	else if (token == 5)
		return (ft_for_token5(lst, data, fd));
	return (-1);
}
