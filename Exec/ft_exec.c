/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:09:01 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/22 13:39:09 by ceatgie          ###   ########.fr       */
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
	while (args && lst && lst->token != 1)
	{
		if (lst->token == 0 && lst->str != NULL)
		{
			if (ft_is_built_in(args, data))
				exit (-1);
			if (!ft_strcmp(args[0], "env") || !ft_strcmp(args[0], "pwd") || !ft_strcmp(args[0], "unset"))
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
