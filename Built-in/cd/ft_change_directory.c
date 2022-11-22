/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_directory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:13:17 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/21 15:39:35 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	ft_verif_if_there_is_pwd_env_var(t_mini *data)
{
	char	*env_var;

	env_var = NULL;
	env_var = ft_get_env_var("OLDPWD=", data);
	if (!env_var)
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("minishell: cd: OLDPWD is not set", 2);
		ft_putstr_fd(RESET, 2);
		return (0);
	}
	if (env_var)
	{
		free(env_var);
		env_var = NULL;
	}
	env_var = ft_get_env_var("PWD=", data);
	if (!env_var)
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("minishell: cd: PWD is not set", 2);
		ft_putstr_fd(RESET, 2);
		return (0);
	}
	if (env_var)
	{
		free(env_var);
		env_var = NULL;
	}
	return (1);
	
}





/*
**	Cette fonction prend en parametre :
**	
**	- Le Path de ou on veut aller
**	- Le pointeur sur structure data
**	
**	========================================
**	
**	Cette fonction sert a faire fonctionner cd
**	Elle s'occupe d'actualiser les variable d'environement OLDPWD et PWD
*/

int	ft_change_directory(char *path, t_mini *data)
{
	char	*pwd;														// On creer une variable pwd qui va contenir le chemin actuel

	pwd = getcwd(NULL, 0);											  // On associe pwd au chemin actuel
	if (!chdir(path))												 // Si chdir renvoie 0 (si il reussis)
	{
		if (pwd)												   // Si il n'y a pas eu d'erreur de malloc
		{
			ft_change_env(pwd, "OLDPWD", data);				 // On change la variable d'environement OLDPWD par pwd qui deviens le path d'avant
			free(pwd);											// On free pwd pour eviter les fuites de memoires
		}
		pwd = getcwd(NULL, 0);								  // On associe pwd au chemin actuel
		if (pwd)											 // Si il n'y a pas eu d'erreur de malloc
		{
			ft_change_env(pwd, "PWD", data);			   // On change la variable d'environement PWD par pwd qui est le path actuel
			free(pwd);									  // On free pwd pour eviter les fuites de memoires
		}
		if (data->converted_path)
		{
			free(data->converted_path);
			data->converted_path = NULL;
		}
		if (data->home)
		{
			free(data->home);
			data->home = NULL;
		}
		return (1);									    // On return (1)
	}
	free(pwd);										  // Si chdir n'a pas marcher on free pwd pour eviter les fuites de memoires
	return (0);									     // On return (0)
}