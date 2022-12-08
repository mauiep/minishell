/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:09:01 by admaupie          #+#    #+#             */
/*   Updated: 2022/12/08 04:40:03 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- Les arguments de l'input
** 
**	========================================
**	
**	Cette fonction sert a renvoyer l'erreur de la fonction handle_exec
*/

static void	ft_handle_exec_error(char **args, t_mini *data)
{
	ft_error(args[0], RED, 42);
	ft_error(" : command not found\n", RED, 42);
	ft_free_all(data);
	ft_free(args);
	data->g_error = 127;
	exit(127);
}

static void	ft_exit_builtin(char **args, t_mini *data)
{
	if (!(ft_strcmp("export", args[0])))
	{
		ft_free_all_exec(data);
		ft_free(args);
		exit (0);
	}
	ft_free_all(data);
	ft_free(args);
	exit (0);
}

static void	ft_check_for_excutable(char **args, t_mini *data)
{
	if ((ft_strncmp(args[0], "./", 2) == 0) && args[0][2] == '.')
		exit(ft_error_for_executable(args, data));
	else if ((ft_strncmp(args[0], "./", 2) == 0) && args[0][2] == '/')
		exit(ft_error_for_executable(args, data));
	else if ((ft_strncmp(args[0], "./", 2) == 0))
		exit(program_exec(args, data));
}

static void	ft_handle_exec_else(t_lst *lst, char **args, t_mini *data)
{
	char	*tmp;
	char	*path;

	tmp = NULL;
	path = NULL;
	if (lst->token == 0 && lst->str != NULL)
	{
		if (ft_is_built_in(args, data))
			ft_exit_builtin(args, data);
		ft_check_for_excutable(args, data);
		if (ft_for_error_directory(args[0]) == 0)
		{
			ft_free_all(data);
			ft_free(args);
			data->g_error = 126;
			exit (126);
		}
		path = ft_get_env_var("PATH", data);
		tmp = ft_find_bin(args[0], path,
				args, data->env_tab);
		if (!tmp)
			ft_handle_exec_error(args, data);
	}
}

/*
**	Cette fonction prend en parametre :
**	
**	- La liste d'argument
**	- Le pointeur sur structure data
** 
**	========================================
**	
**	Cette fonction sert a [a toi d'ecrire]
*/

int	ft_handle_exec(t_lst *lst, t_mini *data)
{
	char	**args;

	if (lst->token != 0)
	{
		ft_free_all(data);
		exit(0);
	}
	args = ft_splitargs(lst);
	if (!args)
		return (-1);
	while (args && lst && lst->token != 1)
	{
		ft_handle_exec_else(lst, args, data);
		lst = lst->next;
	}
	return (0);
}
