/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:44:05 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/22 14:35:20 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- Le pointeur sur structure data
**	
**	========================================
**	
**	Cette fonction sert a gerer le cas ou l'arguent est "-"
*/

static int	ft_cd_else(char **args, t_mini *data)
{
	char	*pwd;																		  // On creer une variable pwd qui va contenir le path actuel

	pwd = NULL;															  				// On l'initialise a NULL
	if (!ft_strcmp(args[1], "-"))									 			   // Si l'argument est "-"
	{
		pwd = ft_get_env_var("OLDPWD", data);						   				 // On associe la variable d'environement OLDPWD a pwd
		if (pwd)													  				// Si il n'y a pas eu d'erreur de malloc
		{
			ft_cd_error_manager(pwd, data);										  // On lance ft_error_manager() qui va s'occuper de changer de directory
			free(pwd);											   				 // On free pwd pour eviter les fuites de memoires
		}
		pwd = ft_get_env_var("PWD", data);						 			   // On associe la variable d'environement PWD a pwd
		if (pwd)															  // Si il n'y a pas d'erreur de malloc
		{
			ft_putstr_fd(pwd, 1);							  				// On ecrit le path actuel sur la sortie standard
			free(pwd);													  // On free pour eviter les fuites de memoires
		}
		return (1);										  				// On return (1)
	}
	data->converted_path = ft_convert_arg_to_path(args, data);			  // On converti l'argument en path
	return (ft_cd_error_manager(data->converted_path, data));	 		 // Si l'argument n'est pas "-" on return (ft_cd_error_manager()) qui s'occupe de changer de directory
}

/*
**	Cette fonction prend en parametre :
**	
**	Le pointeur sur strucuture data
**	========================================
**	
**	Cette fonction sert a changer de directory
*/

int	ft_cd(char **args, t_mini *data)
{
	if (args && args[1] && args[2])											  // Si il existe plus de 1 arguments (donc autre chose que le path ou on veut aller)
	{
		ft_putstr_fd(RED, 2);																// On ecrit en rouge sur la sortie erreur
		ft_putendl_fd("minishell: cd: too many arguments", 2);							   // minishell: cd: too many arguments
		ft_putstr_fd(RESET, 2);															  // On reset la couleur sur la sortie erreur
		return (1);																		 // On return (1);
	}
	else if (!args[1] || !ft_strcmp("~", args[1])							   // Sinon si il n'y a pas de path ou si l'argument est ~
		||	!ft_strcmp("--", args[1]))											  // Ou --
	{
		data->home = ft_get_env_var("HOME", data);									// On associe a la variable home le path de home
		//printf("Home vaut -> %s\n", data->home);
		if (!data->home)														   // Si la variable home est vide (donc qu'il n'a pas trouver de variable HOME)
		{
			ft_putstr_fd(RED, 2);												 // On ecrit en rouge sur la sortie erreur
			ft_putendl_fd("minishell: cd: HOME not set", 2);						// minishell: cd: HOME not set
			ft_putstr_fd(RESET, 2);											   // On reset la couleur sur la sortie erreur
			return (1);														  // On return (1)
		}
		return (ft_cd_error_manager(data->home, data));						// Sinon on return (ft_cd_error_manager()) qui va s'occuper de changer de directory
	}
	return (ft_cd_else(args, data));											 // On return (ft_cd_else()) qui s'occupe de gerer le cas si l'argument vaut "-"
}