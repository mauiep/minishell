/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:49:42 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/23 14:28:30 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
**	Cette fonction sert a afficher env
*/

void	ft_env(t_mini *data)
{
	int	i;											  // On initialise une variable qui compte les strings de env

	i = 0;											// On l'initialise a -1;
	while (data->env_tab[i])					   // Tant que le tableau env existe
	{
		if (ft_is_equal_in_var(data, i))
		{
			ft_putstr_fd(data->env_tab[i], 1);		 // On ecrit la string
			ft_putchar_fd('\n', 1);				 	// On ecrit un \n
		}
		i++;								   // On passe a la string suivante
	}
}