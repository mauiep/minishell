/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:24:44 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/25 13:25:42 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- L'index de la string que l'on veut supprimer
**	- Un pointeur sur structure data
**	
**	========================================
**	
**	Cette fonction realloc le env sans la string que l'on veut supprimer
**	Et fonctionne ainsi :
**
**	- On creer un nouvel env
**	- On copie les variables d'envrionement dans le nouvel env
**	 Jusqu'a la variable que l'on veut supprimer
**	- On passe la variable que l'on veut supprimer
**	- On copie les variables d'envrionement dans le nouvel env
**	 Jusqu'a la fin
*/

char	**ft_realloc_env(int index, t_mini *data)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (ft_env_len(data)));
	if (!new_env)
		return (NULL);
	i = -1;
	while (++i < index)
	{
		new_env[i] = ft_strdup(data->env_tab[i]);
		new_env = ft_if_malloc_issue(new_env, i);
		if (!new_env)
			return (NULL);
	}
	while (data->env_tab[++index])
	{
		new_env[i] = ft_strdup(data->env_tab[index]);
		new_env = ft_if_malloc_issue(new_env, i);
		if (!new_env)
			return (NULL);
		i++;
	}
	new_env[i] = NULL;
	ft_free(data->env_tab);
	return (new_env);
}
