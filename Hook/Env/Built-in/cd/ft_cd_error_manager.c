/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_error_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:22:02 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/03 01:01:20 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

static void	ft_free_and_set_null(t_mini *data)
{
	if (data->converted_path)							// Si le pointeur converted_path existe
	{
		free(data->converted_path);					  // On le free
		data->converted_path = NULL;				 // Puis on le set a NULL
	}
	if (data->home)								   // Si le pointeur home existe
	{
		free(data->home);						 // On le free
		data->home = NULL;						// On le set a NULL
	}
}

/*
**	Cette fonction prend en parametre :
**	
**	- Le path ou on veut aller
**	- Le pointeur sur structure data
**	
**	========================================
**	
**	Cette fonction appelle la fonction pour changer de directory
**	Et gere les differentes erreurs possible de cd
*/

int	ft_cd_error_manager(char *path, t_mini *data)
{
	struct stat	st;																// On creer une variable st de type struct stat

	if (ft_change_directory(path, data))									  // On appelle la fonction qui change de directory
		return (1);															 // Si elle fonctionne on return (1)
	ft_putstr_fd(RED, 2);													// Sinon on ecrit en rouge
	ft_putstr_fd("minishell: cd: ", 2);									   // minishell: cd: 
	ft_putstr_fd(path, 2);												  // Suivi du path ou on veut aller (qui n'existe pas pour le coup)
	if (stat(path, &st) == -1)											 // Si la fonction stat() return (-1)
		ft_putstr_fd(": No such file or directory", 2);					// On ecrit : No such file or directory
	else if (!S_ISDIR(st.st_mode))									   // Si ce n'est pas un dossier
		ft_putstr_fd(": Not a directory", 2);						  // On ecrit : Not a directory
	else if (!(st.st_mode & S_IXUSR))								 // On verifie si le proprietaire a le droit d'exec		
		ft_putstr_fd(": Permission denied", 2);						// Si non on ecrit : Permission denied
	ft_free_and_set_null(data);									   // On appelle la fonction qui s'occupe de free home et converted_path
	return (1);													  // On return (1)
}