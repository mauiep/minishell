/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:09:01 by admaupie          #+#    #+#             */
/*   Updated: 2022/12/05 19:59:19 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	ft_free_handle_exec(t_mini *data)
{
	ft_error("ca passe ici\n", RED, 0);
	if (data->line)
		free(data->line);
	if (data->env_tab)
		ft_free(data->env_tab);
	if (data->prompt)
		free(data->prompt);
	if (data->splitargs)
		ft_free(data->splitargs);
	if (data->lst)
		free_lst(data->lst);
	if (data->list)
		free(data->list);
}

/*
**	Cette fonction prend en parametre :
**	
**	- Les arguments de l'input
**	- Un pointeur sur structure data
**	
**	========================================
**	
**	Cette fonction sert executer un programme dans minishell et a verifier
** Ses droits d'exec
*/

static int	program_exec(char **args, t_mini *data)
{
	if (access(args[0] + 2, F_OK & X_OK) == 0)
	{
		execve(args[0] + 2, args, data->env_tab);
		ft_putstr_fd(RED, 2);
		perror("execve");
		ft_putstr_fd(RESET, 2);
		ft_free_handle_exec(data);
	}
	else
	{
		ft_error("minishell: ", RED, 42);
		ft_error(args[0], RED, 42);
		ft_error(": No such file or directory", RED, 42);
		ft_error("\n", RED, 42);
		ft_free_handle_exec(data);
	}
	return (-1);
}

/*
**	Cette fonction prend en parametre :
**	
**	- Les arguments de l'input
**	
**	========================================
**	
**	Cette fonction sert a bloquer les built-in qui sont gerer par execve
*/

static void	ft_block_built_in(char **args, t_mini *data)
{
	if (!ft_strcmp(args[0], "env") || !ft_strcmp(args[0], "pwd")
		|| !ft_strcmp(args[0], "unset") || !ft_strcmp(args[0], "echo")
		|| !ft_strcmp(args[0], "exit"))
	{
		ft_free_handle_exec(data);
		exit (-1);
	}
}

/*
**	Cette fonction prend en parametre :
**	
**	- Les arguments de l'input
**	- Le pointeur sur structure data
** 
**	========================================
**	
**	Cette fonction sert a verifier si on veut exec un executable
** Au lieu d'une commande
*/

static void	ft_check_if_executable(char **args, t_mini *data)
{
	if (ft_strncmp(args[0], "./", 2) == 0)
		exit (program_exec(args, data));
}

/*
**	Cette fonction prend en parametre :
**	
**	- Les arguments de l'input
** 
**	========================================
**	
**	Cette fonction sert a renvoyer l'erreur de la fonction handle_exec
*/

static void	ft_handle_exec_error(char **args)
{
	ft_error(args[0], RED, 42);
	ft_error(" : command not found\n", RED, 42);
	ft_free(args);
	exit(127);
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
	char	*tmp;

	if (lst->token != 0)
	{
		ft_free_handle_exec(data);
		exit(0);
	}
	if (data->splitargs)
		ft_free(data->splitargs);
	data->splitargs = ft_splitargs(lst);
	fprintf(stderr, "%sargv[0]=%s\n%s", RED, data->splitargs[0], RESET);
	if (!data->splitargs)
		return (-1);
	while (data->splitargs && lst && lst->token != 1)
	{
		if (lst->token == 0 && lst->str != NULL)
		{
			if (ft_is_built_in(data->splitargs, data))
			{
				//free_pipe_array(data->pipefd, data->nb_pipes);
				ft_free_handle_exec(data);
				exit (data->g_error);
			}
			ft_error("ON PASSE ICI \n", RED, 0);
			ft_check_if_executable(data->splitargs, data);
			//ft_block_built_in(data->splitargs, data);
			tmp = ft_find_bin(data->splitargs[0], ft_get_env_var("PATH", data),
					data->splitargs, data->env_tab);
			if (!tmp)
				ft_handle_exec_error(data->splitargs);
		}
		lst = lst->next;
	}
	return (0);
}
