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

int	program_exec(char **args, t_lst *lst, t_mini *data)
{//	Ajouter une condition si pas les droits sur le fichier afficher	Permission DENIED
	if (access(args[0] + 2, F_OK & X_OK) == 0)
	{
		execve(args[0] + 2, args, data->env_tab);
		perror("execve");
		//FREE LE DOUBLE TABLEAU ARGS
	}
	else
	{
		ft_error("minishell: No such file or directory : ", RED, 42);
		ft_error(args[0], RED, 42);
		ft_error("\n", RED, 42);
	}
	return (-1);
}

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
			if (ft_strncmp(args[0], "./", 2) == 0)
				exit (program_exec(args, lst, data));
			if (!ft_strcmp(args[0], "env") || !ft_strcmp(args[0], "pwd") || !ft_strcmp(args[0], "unset"))
				exit (-1);
			tmp = ft_find_bin(args[0], ft_get_env_var("PATH", data),
					args, data->env_tab);
			if (!tmp)
			{
				ft_error(args[0], RED, 42);
				ft_error(" : command not found\n", RED, 42);
				exit(-1);
			}
		}
		lst = lst->next;
	}
	return (0);
}
