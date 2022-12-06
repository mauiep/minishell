/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:44:05 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/06 14:46:13 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- Les arguments de cd
**	- Le pointeur sur strucuture data
**
**	========================================
**	
**	Cette fonction sert a changer de directory
**	Et fonctionne ainsi :
**	
**	- Si il existe plus de 1 arguments alors on return un message d'erreur
**	 Qui indique qu'il y a trop d'argument dans l'appel de cd
**	
**	========================================
**	
**	- Si il n'y a pas de path ou si l'argument est "~" ou "--"
**	- On verifie si la variable d'environement HOME existe
**	- Si la variable d'envrironement HOME existe alors
**	- On appelle ft_cd_error_manager qui s'occupe de changer de directory
**	 En lui donnant HOME comme path,
**	
**	========================================
**	
**	- Si la variable d'environement HOME n'existe pas alors
**	- On return un message d'erreur
**	 Qui indique que HOME n'est pas set dans env
**	
**	========================================
**	
**	- Si il existe un path ou que l'argument n'est pas "~" ou "--"
**	- On return ft_cd_check_if_arg_is_dash() qui s'occupe de verifier
**	 Si l'argument est un "-"
*/

int	ft_cd(char **args, t_mini *data)
{
	if (args && args[1] && args[2])
	{
		ft_putstr_fd(RED, 2);
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		ft_putstr_fd(RESET, 2);
		data->g_error = 1;
		return (1);
	}
	else if (!args[1] || !ft_strcmp("~", args[1])
		|| !ft_strcmp("--", args[1]))
	{
		data->home = ft_get_env_var("HOME", data);
		if (!data->home)
		{
			ft_putstr_fd(RED, 2);
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			ft_putstr_fd(RESET, 2);
			data->g_error = 1;
			return (1);
		}
		return (ft_cd_error_manager(data->home, data));
	}
	return (ft_cd_check_if_arg_is_dash(args, data));
}
