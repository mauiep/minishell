/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:11:42 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/06 16:07:39 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- Les arguments de export
**	- Le pointeur sur structure data
**
**	========================================
**	
**	Cette fonction sert a faire fonctionner export
**	Et fonctionne ainsi :

**	- Si il n'y a pas d'argument
**	- On affiche les variables d'environement dans l'ordre ascii
**	 Precedees de "declare -x"
**	
**	========================================
**	
**	- Pour tout les arguments,
**	- Si le parsing de l'argument renvoie 0
**	- On return un message d'erreur
**	
**	========================================
**	
**	- Si le parsing de l'argument renvoie 1
**	- On ajoute l'argument dans env
*/

int	ft_export(char **args, t_mini *data)
{
	int	i;

	data->g_error = 0;
	if (!args[1])
	{
		ft_sort_and_print_env(data);
		return (1);
	}
	i = 1;
	while (args[i])
	{
		if (!ft_check_export_var(args[i]))
		{
			ft_error("minishell: export: `", RED, 0);
			ft_error(args[i], RED, 0);
			data->g_error = 1;
			return (ft_error(": not a valid identifier\n", RED, 0));
		}
		else
			ft_add_env_var(args[i], data);
		i++;
	}
	return (1);
}
