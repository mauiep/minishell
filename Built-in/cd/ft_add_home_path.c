/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_home_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:32:36 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/24 15:49:44 by ceatgie          ###   ########.fr       */
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
**	Cette fonction sert a convertir le path absolu si il commence
**	Par "~/" en path comprehensible pour CD
**	Et fonctionne ainsi :
**
**	- Si l'argument de cd commence par "~/"
**	- On recupere la variable d'envrionement HOME et on lui rajoute "/"
**	 Ce qui donne $HOME/
**	- On rajoute le path sans le "~/" qui a ete transformer en HOME
**	 Par exemple cd ~/Documents/42 deviens $HOME/Documents/42
**	- On return le path converti
**	
**	========================================
**	
**	- Si l'argument de cd ne commence pas par "~/"
**	- On return (NULL)
*/

char	*ft_add_home_path(char **args, t_mini *data)
{
	char	*converted_path;
	char	*buffer;
	char	*home;

	converted_path = NULL;
	buffer = NULL;
	if (!ft_strncmp("~/", args[1], 2))
	{
		home = ft_get_env_var("HOME", data);
		converted_path = ft_strjoin(home, "/");
		buffer = ft_strdup(converted_path);
		free (converted_path);
		converted_path = ft_strjoin(buffer, args[1] + 2);
		free(buffer);
		free(home);
		return (converted_path);
	}
	return (NULL);
}
