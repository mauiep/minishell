/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:09:01 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/21 09:20:24 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_exec(t_lst *lst, t_mini *data)
{
	char	**args;
	char	*tmp;

	args = ft_splitargs(lst);
	while (args && lst && lst->token != 1)
	{
		if (lst->token == 0 && lst->str != NULL)
		{
			//ici faire un strcmp de la str avec les builtins
			tmp = ft_find_bin(args[0], ft_get_env_var("PATH", data),
					args, data->env_tab);
			if (!tmp)
				return (printf("%s : command not found\n", args[0]), -1);
		}
		lst = lst->next;
	}
	return (0);
}
