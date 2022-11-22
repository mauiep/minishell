/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:27:17 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/22 14:54:25 by ceatgie          ###   ########.fr       */
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
	int		i;																						 // On creer une variale i qui servira a parcourir env																					
	char	*buffer;																				// On creer un buffer pour contenir un backup de notre env entre chaque strjoin
	char	*backup_env;																		   // On creer une variale backup_env qui servira a contenir l'ancienne version de la variable d'environement si le strjoin ne fonctionne pas

	i = 0;																					  	 // On l'initialise a 0 car env commence a l'index 0
	if (!data->env_tab)																		 	// Si env n'existe pas alors on quitte la fonction
		return ;																			   // Alors on quitte la fonction
	while (data->env_tab[i])															   	  // Tant que env existe
	{
		if (!ft_strncmp(env_var, data->env_tab[i], ft_strlen(env_var)))					  	// Si on trouve la variable d'envrionement 
			break;																		   // On quitte la boucle
		i++;																			  // Sinon on passe a la variable suivante
	}
	backup_env = ft_strdup(data->env_tab[i]);											// On creer une backup de notre variable d'environement au cas ou strjoin ne fonctionne pas	
	free(data->env_tab[i]);														  	   // On free l'ancienne version de la variable d'environement
	data->env_tab[i] = ft_strjoin(env_var, "=");									  // On ecris join env_var et = par exemple PWD=
	buffer = ft_strdup(data->env_tab[i]);											 // On contient la bakcup dans un buffer pour le prochain strjoin
	free(data->env_tab[i]);															// On free pour contenir le prochain strjoin
	data->env_tab[i] = ft_strjoin(buffer, pwd);									   // On strjoin le contenant de la variable
	free(buffer);																  // On free le buffer
	if (!data->env_tab[i])														 // Si le strjoin ne marche pas
	{
		ft_free(data->env_tab);												   // On free tout le tableau
		data->env_tab[i] = ft_strdup(backup_env);						      // On recupere l'ancienne version de la variable d'environement
		free(backup_env);													 // On free la backup
		return ;															// On quitte la fonction
	}
	free(backup_env);													  // On free la backup si tout s'est bien passer
} 