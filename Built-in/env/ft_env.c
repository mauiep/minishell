/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:49:42 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/06 15:35:08 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- Le pointeur sur structure data
**	- L'index de la variable d'environement que l'on veut check
**	========================================
**	
**	Cette fonction sert a verifier si le nom de la variable d'envrionement est
** Succede par un "="
** Et fonctionne ainsi :
**	
**	- Si il y a un "=" dans la ligne de declaration de la variable d'environement
**	- On return (1);
**	
**	========================================
**	
**	- Si il n'y a pas de "=" dans la ligne
**	 De declaration de la variable d'environement
**	- On return (0);
*/

static int	ft_is_equal_in_var(t_mini *data, int i)
{
	int	j;

	j = 0;
	while (data->env_tab[i][j])
	{
		if (data->env_tab[i][j] == '=')
			return (1);
		j++;
	}
	return (0);
}

/*
**	Cette fonction prend en parametre :
**	
**	- Le pointeur sur structure data
**
**	========================================
**	
**	Cette fonction sert a afficher les variables d'environements qui ont ete
** Set par une valeur
** Et fonctionne ainsi :
**	
**	- Si il y a un "=" dans la ligne de declaration de la variable d'environement
**	- On affiche la variable d'environement;
**	
**	========================================
**	
**	- Si il n'y a pas de "=" dans la ligne
**	 De declaration de la variable d'environement
**	- On n'affiche pas la variable d'environement;
*/

void	ft_env(t_mini *data)
{
	int	i;

	i = 0;
	while (data->env_tab[i])
	{
		if (ft_is_equal_in_var(data, i))
		{
			ft_putstr_fd(data->env_tab[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	data->g_error = 0;
}
