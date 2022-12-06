/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 02:56:29 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/06 16:08:22 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- Les arguments de unset
**	- Un pointeur sur structure data
**	
**	========================================
**	
**	Cette fonction sert a faire fonctionner unset
**	Et fonctionne ainsi :
**	
**	- Si il n'y a pas d'argument
**	- On return (1)
**	
**	========================================
**	
**	- Tant que il existe des arguments
**	- On recupere l'index de la string que l'on veut supprimer dans env
**	
**	========================================
**	
**	- Tant que il existe des arguments
**	- On recupere l'index de la string que l'on veut supprimer dans env
**	- On realloc env pour le supprimer grace a ft_realloc_env()
*/

int	ft_unset(char **args, t_mini *data)
{
	int	env_index;
	int	i;

	if (!args[1])
		return (1);
	env_index = 0;
	i = -1;
	while (args[++i])
	{
		if (!ft_check_unset_arg(args[i]))
		{
			ft_putstr_fd(RED, 2);
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ft_putstr_fd(RESET, 2);
			return (data->g_error = 1, 0);
		}
		env_index = ft_find_env(args[i], data);
		if (env_index != -1)
			if (data->env_tab[env_index])
				data->env_tab = ft_realloc_env(env_index, data);
	}
	return (data->g_error = 0, 1);
}
