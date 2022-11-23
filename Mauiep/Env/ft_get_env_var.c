/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:10:27 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/18 15:10:53 by ceatgie          ###   ########.fr       */
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
**	Cette fonction sert a renvoyer la variable d'environement
**	Que l'on souhaite recuperer
*/

char	*ft_get_env_var(char *env_var, t_mini *data)
{
	int		i;																						// On creer un index pour parcourir env
	char	*found_env_var;																		   // On creer une variable pour contenir la variable d'environement demandee

	i = 0;																						 // On initialise l'index a 0 car env commence a l'index 0
	while (data->env_tab[i])																	// Tant que env existe
	{
		if (!ft_strncmp(env_var, data->env_tab[i], ft_strlen(env_var)))						  // Si on trouve la variable d'environement demandee
		{
			found_env_var = ft_strndup(data->env_tab[i], ft_strlen(env_var));				// On la copie en recuperant la variable sans le nom par exemple sans le OLDPWD=
			if (!found_env_var)															   // Si le malloc ne fonctionne pas
				return (NULL);															  // On return (NULL)
			return (found_env_var);														 // Sinon on return la variable d'environement demandee
		}
		i++;																		   // Si on ne trouve pas la variable d'environement demandee on passe a la prochaine
	}
	return (NULL);																	 // Sinon on return NULL si rien n'est trouvee
}