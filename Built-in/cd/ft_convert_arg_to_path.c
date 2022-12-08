/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_arg_to_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:56:42 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/08 02:53:57 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- Les arguments de cd
**	- Le pointeur sur structure data
**	
**	========================================
**	
**	Cette fonction sert a convertir le dossier ou on veut aller en 
**	Path qui va etre compris par CD
**	Et fonctionne ainsi :
**	
**	- On verifie si l'argument commence par "~/" grace a ft_add_home_path()
**	- On recupere le pwd actuel
**	
**	========================================
**	
**	- Si l'argument commence par "/" alors il sagit d'un path absolu
**	- On return alors ce dernier
**	
**	========================================
**	
**	- Sinon on ajoute "/" au pwd recupere plus tot ce qui donne $PWD/
**	- On rajoute ensuite l'argument ce qui donne
**	 Par exemple pour cd Documents --> $PWD/Documents
**	- On return le path converti
*/

char	*ft_convert_arg_to_path(char **args, t_mini *data)
{
	char	*converted_path;
	char	*buffer;
	char	*pwd;

	converted_path = ft_add_home_path(args, data);
	if (converted_path)
		return (converted_path);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	buffer = NULL;
	if (args[1][0] == '/')
	{
		converted_path = ft_strdup(args[1]);
		return (free(pwd), converted_path);
	}
	converted_path = ft_strjoin(pwd, "/");
	free(pwd);
	buffer = ft_strdup(converted_path);
	free(converted_path);
	converted_path = ft_strjoin(buffer, args[1]);
	if (!converted_path)
		return (free(buffer), NULL);
	return (free(buffer), converted_path);
}
