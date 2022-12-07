/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:10:27 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/28 12:17:04 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- La variable d'environement que l'on veut recuperer
**	- Un pointeur sur structure data
**	
**	========================================
**	
**	Cette fonction sert a renvoyer la valeur de la variable d'environement
**	Que l'on souhaite recuperer
*/

char	*ft_get_env_var(char *env_var, t_mini *data)
{
	int		i;
	char	*found_env_var;

	i = 0;
	if (!env_var)
		return (NULL);
	else if (env_var[0] == '\0')
		return (ft_strdup("$"));
	while (data->env_tab[i])
	{
		if (!ft_strncmp(env_var, data->env_tab[i], ft_strlen(env_var)))
		{
			found_env_var = ft_strndup(data->env_tab[i], ft_strlen(env_var));
			if (!found_env_var)
				return (NULL);
			return (found_env_var);
		}
		i++;
	}
	return (NULL);
}
