/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:41:34 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/06 16:34:59 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- Les arguments des differents built-ins
**	- Le pointeur sur structure data
**	
**	========================================
**	
**	Cette fonction sert verifier si l'utilisateur utilise un built in
**	Et fonctionne ainsi : 
**	
**	- Si il n'y a pas de commande
**	- On return (-1)
**	
**	========================================
**	
**	- On verifie si la commande a le meme nom que les built-ins
**	- Si oui on appelle la fonction du Built-in en question
*/

int	ft_is_built_in(char **args, t_mini *data)
{
	if (!args || !args[0])
		return (-1);
	if (!(ft_strcmp("pwd", args[0])))
		return (data->g_error = 0, ft_pwd(), 1);
	else if (!(ft_strcmp("env", args[0])))
		return (ft_env(data), 1);
	else if (!(ft_strcmp("cd", args[0])))
		return (ft_cd(args, data), 1);
	else if (!(ft_strcmp("unset", args[0])))
		return (ft_unset(args, data), 1);
	else if (!(ft_strcmp("export", args[0])))
		return (ft_export(args, data), 1);
	else if (!(ft_strcmp("echo", args[0])))
		return (data->g_error = 1, ft_echo(args), 1);
	else if (!(ft_strcmp("exit", args[0])))
		return (ft_exit(args, data), 1);
	return (0);
}
