/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 02:56:29 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/06 23:52:58 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- L'index de la string que l'on veut supprimer
**	- Un pointeur sur structure data
**	
**	========================================
**	
**	Cette fonction realloc le env sans la string que l'on veut supprimer
**
*/

static	char	**ft_realloc_env(int index, t_mini *data)
{
	char	**new_env;																			// On creer un double pointeur new_env qui contiendra l'env realloc
	int		i;																				   // On creer une variable i qui parcours new env

	new_env = malloc(sizeof(char *) * (ft_env_len(data)));								 	 // On creer le grand tableau de la taille de env dont 1 pour set a NULL
	if (!new_env)																			// Si le malloc ne fonctionne pas
		return (NULL);																	   // On return (NULL);
	i = -1;																				  // On initialise i a 0 car l
	while (++i < index)																	 //	Tant que on est pas sur la string que l'on veut supprimer de env
	{
		new_env[i] = ft_strdup(data->env_tab[i]);									   // On copie la string dans le nouveau tableau
		new_env = ft_if_malloc_issue(new_env, i);									  // On appelle la fonction de verification des mallocs
		if (!new_env)																 // Si new_env n'existe plus
			return (NULL);															// On return (NULL)
	}
	while (data->env_tab[++index])												  // Tant que env existe et apres avoir passer la string que l'on veut supprimer
	{
		new_env[i] = ft_strdup(data->env_tab[index]);						    // On copie a la suite de new_env a partir de la string apres celle que l'on veut supprimer
		new_env = ft_if_malloc_issue(new_env, i);							   // On appelle la fonction de verification des mallocs
		if (!new_env)														  // Si new_env n'existe plus
			return (NULL);												     // On return (NULL)
		i++;
	}
	new_env[i] = NULL;												  	  // A la fin on set la derniere string a NULL pour finir le tableau
	ft_free(data->env_tab);											  	 // On free l'ancien env
	return (new_env);												 	// On return (new_env)
}

/*
**	Cette fonction prend en parametre :
**	
**	- Un pointeur sur structure data
**	
**	========================================
**	
**	Cette fonction sert a supprimer une variable d'environement
**
*/

int	ft_unset(t_mini *data)
{
	int	env_index;																					// On creer une variable env_index qui contiendra l'index de la string que l'on supprimer dans env
	int	i;																						   // On creer une variable i qui servira a parcourir les arguments de unset()

	if (!data->cmd[1])																			 // Si il n'y a pas d'arguments derriere unset()
		return (1);																				// Alors on ne fait rien et on return (1)
	env_index = 0;																			   // On initialise env_index a 0
	i = 1;																					  // On initialise i a 1 car cmd[0] c'est unset
	while (data->cmd[i])																	 // Tant que il existe des arguments
	{
		env_index = ft_find_env(data->cmd[i], data);									   // On recupere l'index de la string que l'on veut supprimer dans env
		if (env_index != -1)															  // Si env_index vaut autre chose que -1 alors l'argument est une variable d'environement
		{
			if (data->env_tab[env_index])												// On verifie si la string existe dans env											
				data->env_tab = ft_realloc_env(env_index, data);					   // Si oui alors on supprime la variable d'envrionement en reallocant env
		}
		else																		 // Sinon
		{
			ft_putstr_fd(RED, 2);												   // On ecrit en rouge sur la sortie erreur
			ft_putstr_fd("minishell: unset: `", 2);								  // minishell: unset: `
			ft_putstr_fd(data->cmd[i], 2);										 // L'argument
			ft_putstr_fd("': not a valid identifier\n", 2);						// ': not a valid identifier
			ft_putstr_fd(RESET, 2);											   // On reset la couleur sur la sortie erreur
		}
		i++;																 // On passe a l'argument suivant
	}
	return (1);															   // On return (1)
}