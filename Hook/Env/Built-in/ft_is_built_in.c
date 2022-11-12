/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:41:34 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/04 15:13:55 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- Le pointeur sur structure data
**	
**	========================================
**	
**	Cette fonction sert verifier si l'utilisateur utilise un built in
*/

int	ft_is_built_in(t_mini *data)
{
	if (!(ft_strcmp("pwd", data->cmd[0])))								// Si l'input utilisateur est pwd
	{
		ft_pwd();													  // On lance le built in pwd
		return (1);													 // On retourne 1 pour dire que ca ete bien utiliser
	}
	else if (!(ft_strcmp("env", data->cmd[0])))					   // Si l'input utilisateur est env
	{
		ft_env(data);											 // On lance le built in env
		return (1);												// On retourne 1 pour dire que ca ete bien utiliser
	}
	else if (!(ft_strcmp("cd", data->cmd[0])))				  // Si l'input utilisateur est cd
	{
		ft_cd(data);										// On lance le built in cd
		return (1);										   // On retourne 1 pour dire que ca ete bien utiliser
	}
	else if (!(ft_strcmp("unset", data->cmd[0])))
	{
		ft_unset(data);
		return (1);
	}
	else if (!(ft_strcmp("export", data->cmd[0])))
	{
		ft_export(data);
		return (1);
	}
	return (0);											 // Sinon on retourne 0 si l'input utilisateur n'est associer a aucun built in
}