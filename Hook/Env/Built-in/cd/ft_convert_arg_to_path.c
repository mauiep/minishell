/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_arg_to_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:56:42 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/03 01:01:39 by ceatgie          ###   ########.fr       */
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
**	Cette fonction sert a convertir le path absolu si il commence
**	Par ~/ en path comprehensible pour CD 
*/


static char * ft_add_home_path(t_mini *data)
{
	char 	*converted_path;														// On creer une variable converted_path qui contiendra le path converti
	char	*buffer;															   // On creer une variable buffer qui contiendra la backup entre les deux strjoin
	char 	*home;																  // On creer une variable home qui contiendra la variable d'environement home

	converted_path = NULL;														// On initialise converted_path a NULL
	buffer = NULL;															   // On initialise buffer a NULL
	if (!ft_strncmp("~/", data->cmd[1], 2))									  // Si l'argument commence par ~/		
	{
		home = ft_get_env_var("HOME=", data);								// On associe la variable d'environement HOME a home
		converted_path = ft_strjoin(home, "/");							   // On rajoute / a home par exemple /home/usr deviens /home/usr/
		buffer = ft_strdup(converted_path);								  // On fait une backup dans le buffer
		free (converted_path);											 // On free converted_path pour le preparer au second strjoin
		converted_path = ft_strjoin(buffer, data->cmd[1] + 2);			// On rajoute l'argument sans le ~/ (d'ou le + 2)
		free(buffer);												   // On free le buffer car on en a plus besoin
		free(home);													  // On free home car on en a plus besoin
		return (converted_path);									 // On return le path converti
	}
	return (NULL);												   // Si la string ne commence pas par ~/ on return (NULL)
}

/*
**	Cette fonction prend en parametre :
**	
**	- Le pointeur sur structure data
**	
**	========================================
**	
**	Cette fonction sert a convertir le dossier ou on veut aller en 
**	Path qui va etre compris par CD
*/

char	*ft_convert_arg_to_path(t_mini *data)
{
	char *converted_path;														// On creer une variable qui va contenir le path converti
	char *buffer;															   // On creer un buffer qui contiendra une backup entre les deux strjoin pour eviter les leaks
	char *pwd;																  // On creer une variable qui contiendra le path actuel

	converted_path = ft_add_home_path(data);							    // On initialise a NULL ou on met le path si l'arguement commence par ~/
	if (converted_path)													   // Si le converted_path a ete rempli
		return (converted_path);										  // Ca veut dire que l'argument commence par ~/ et a ete modifier par ft_add_home_path()
	pwd = getcwd(NULL, 0);												 // On recupere le path actuel
	buffer = NULL;														// On initialise a NULL
	if (data->cmd[1][0] == '/')
	{
		converted_path = ft_strdup(data->cmd[1]);					  // On fait une copie du path absolu dans la variable converted path
		return (converted_path);									 // On return (converted_path)
	}
	converted_path = ft_strjoin(pwd, "/");					   	   // On rajoute au path actuel un / pour acceuillir derriere l'endroit ou on veut aller
	free(pwd);													  // On free pwd car on en a plus besoin
	buffer = ft_strdup(converted_path);							 // On copie le resultat dans le buffer
	free(converted_path);										// On free le converted_path pour le preparer au second strjoin
	converted_path = ft_strjoin(buffer, data->cmd[1]);		   // On rajoute derriere le / le nom de l'endroit ou on veut aller
	if (!converted_path)									  // Si le malloc se passe mal
		return (NULL);										 // On return (NULL);
	free(buffer);											// On free le buffer car on en a plus besoin
	return (converted_path);							   // On return le nouveau path converti
}