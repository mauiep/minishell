/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:27:17 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/18 15:02:22 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- Le path actuell
**	- La variable d'environement que l'on veut modif
**	- Un pointeur sur structure data
**	
**	========================================
**	
**	Cette fonction sert a modifier les variables d'environement dans env
*/

void	ft_change_env(char *pwd, char *env_var, t_mini *data)
{
	int	i;																						// On creer une variale i qui servira a parcourir env

	i = 0;																					  // On l'initialise a 0 car env commence a l'index 0
	if (!data->env_tab)																		 // Si env n'existe pas alors on quitte la fonction
		return ;																			// Alors on quitte la fonction
	while (data->env_tab[i])															   // Tant que env existe
	{
		if (!ft_strncmp(env_var, data->env_tab[i], ft_strlen(env_var)))					  // Si on trouve la variable d'envrionement 
			break;																		 // On quitte la boucle
		i++;																			// Sinon on passe a la variable suivante
	}
	free(data->env_tab[i]);														  	  // On free l'ancienne version de la variable d'environement
	data->env_tab[i] = ft_strjoin(env_var, pwd);									 // On remplace par la nouvelle
	if (!data->env_tab[i])															// Si le malloc ne marche pas
	{
		ft_free(data->env_tab);													  // On free tout le tableau
		ft_create_env(data);													 // On reset env
		return ;																// On quitte la fonction
	}
} 