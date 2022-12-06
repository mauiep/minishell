/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_directory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:13:17 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/24 15:24:13 by ceatgie          ###   ########.fr       */
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
**	Cette fonction free les pointeurs utiliser
**	Et les set a NULL pour la prochaine utilisation
*/

static void	ft_free_data_and_set_null(t_mini *data)
{
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
}

/*
**	Cette fonction prend en parametre :
**	
**	- Le Path de ou on veut aller
**	- Le pointeur sur structure data
**	
**	========================================
**	
**	Cette fonction sert a changer de directory et d'actualiser les variables
**	D'environement OLDPWD et PWD
**	Cette derniere fonctionne ainsi :
**
**	- Si chdir renvoie 0 alors le path est bon et la navigation
**	 Dans le nouveau path a correctement fonctionne
**	- On change la variable OLDPWD grace a ft_change_env()
**	 En raison de l'ancien pwd contenu en memoire
**	- On recupere le pwd apres avoir change de directory
**	- On change la variable PWD grace a ft_change_env()
**	 En raison du nouveau pwd contenu en memoire
**	- On return (1) pour dire que ca s'est bien passe
**	
**	========================================
**	
**	- Dans le cas ou chdir renvoie autre chose que 0
**	- On return (0);
*/

int	ft_change_directory(char *path, t_mini *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free(path), -1);
	if (!chdir(path))
	{
		if (pwd)
		{
			ft_change_env(pwd, "OLDPWD", data);
			free(pwd);
		}
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (-1);
		if (pwd)
		{
			ft_change_env(pwd, "PWD", data);
			free(pwd);
		}
		ft_free_data_and_set_null(data);
		return (1);
	}
	free(pwd);
	ft_free_data_and_set_null(data);
	return (0);
}
