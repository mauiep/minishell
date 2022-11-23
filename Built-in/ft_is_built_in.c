/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:41:34 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/22 13:27:52 by ceatgie          ###   ########.fr       */
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
**	Cette fonction sert verifier si l'utilisateur utilise un built in
*/

int	ft_is_built_in(char **args, t_mini *data)
{
	if (!args || !args[0])
		return (-1);
	if (!(ft_strcmp("pwd",args[0])))										// Si l'input utilisateur est pwd
	{
		ft_pwd();													  	  // On lance le built in pwd
		return (1);													     // On retourne 1 pour dire que ca ete bien utiliser
	}
	else if (!(ft_strcmp("env", args[0])))					   		   // Si l'input utilisateur est env
	{
		ft_env(data);											     // On lance le built in env
		return (1);												    // On retourne 1 pour dire que ca ete bien utiliser
	}
	else if (!(ft_strcmp("cd", args[0])))						  // Si l'input utilisateur est env
	{
		ft_cd(args, data);										// On lance le built in cd
		return (1);											   // On retourne 1 pour dire que ca ete bien utiliser
	}
	else if (!(ft_strcmp("unset", args[0])))
	{
		ft_unset(args, data);
		return (1);
	}
	/*
	else if (!(ft_strcmp("export", data->cmd[0])))
	{
		ft_export(data);
		return (1);
	}*/
	return (0);											 // Sinon on retourne 0 si l'input utilisateur n'est associer a aucun built in
}