/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:09:01 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/22 15:05:36 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_exec(t_lst *lst, t_mini *data)
{
	char	**args;
	char	*tmp;

	args = ft_splitargs(lst);
	if (!args)
		return (-1);
	if (args[0] == NULL)
		return (free(args[0]), free(args), 0);
	while (args && lst && lst->token != 1)
	{
		if (lst->token == 0 && lst->str != NULL)
		{
			if (ft_is_built_in(args, data)) // Ici ca marche pas
				exit (-1);
			tmp = ft_find_bin(args[0], ft_get_env_var("PATH", data),
					args, data->env_tab);
			if (!tmp)
			{
				fprintf(stderr, "%s : command not found\n", args[0]);
				exit(-1);
			}
		}
		lst = lst->next;
	}
	return (0);
}
