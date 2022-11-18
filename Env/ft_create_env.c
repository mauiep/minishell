/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:38:05 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/18 15:02:34 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- Un pointeur sur structure data
**	
**	========================================
**	
**	Cette fonction sert a modifier les variables d'environement dans env
*/

void	ft_create_env(t_mini *data)
{
	int	i;																// On creer un index pour parcourir tout env

	i = 0;															  // On l'initialise a 0 car env demarre a l'index 0
	while (data->envp[i])											 // Tant que env existe
		i++;														// On passe a la string suivante (On recupere ainsi la taille de env)
	data->env_tab = malloc(sizeof(char *) * (i + 1));			   // On creer un tableau qui va contenir env
	if (!data->env_tab)											  // Si le malloc se passe mal
		return ;												 // On quitte la fonction 
	i = 0;														// On remet i a 0 pour l'utiliser comme index pour le tableau que je viens de creer
	while (data->envp[i])									   // Tant que env existe
	{
		data->env_tab[i] = ft_strdup(data->envp[i]);		 // On copie chaque string dans le nouveau tableau
		i++;												// On passe a la string suivante
	}
	data->env_tab[i] = NULL;							  // On initialise la derniere case a NULL
}
