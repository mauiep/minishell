/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrong_syntax_redir_check.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:30:56 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/28 15:04:47 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- La ligne donnee par GNL
**	- l'index qui parcours ligne
**	
**	========================================
**	
**	Cette fonction n'existe que pour la norme (25 lignes)
*/

static int	ft_wrong_syntax_redir_check_else(char *line, int i)
{
	int	cpt;																			 // On creer un compteur pour compter les chevrons
	while (line[i])																	    // Tant que la ligne existe
	{
		cpt = 0;																	  // On initialise le compteur a 0
		i = ft_is_inside_quote(line, i);											 // On verifie les quotes
		if (i == (int)ft_strlen(line))												// Si on est a la fin de line
			break ;																   // Alors on quitte la boucle
		while (line[i] && line[i] == '<')				      // Tant que on est sur le caractere qu'on veut verifier ou sur un espace
		{
			if (line[i] == '<')													// Si on est sur le caractere qu'on veut verifier
				cpt++;												   		   // Alors on augmente compteur de 1
			i++;												   	 	 	  // On passe au caractere suivant
		}
        if (cpt == 3)
            return (-1);
		if (cpt == 4)													  	// Si le compteur vaut 4
			return (ft_error_msg(line, '<', i + 2));				 	   // On retourne le message d'erreur i + 2 car on doit ecrire que un seul > C'est pour ne pas rentrer dans la condition ou on print 2x character dans ft_error_token
		else if (cpt == 5)												  // Si le compteur vaut 5
			return (ft_error_msg(line, '<', i));				   	  	 // Alors on return ft_error_msg avec le i inchanger car on veut qu'il rentre dans la condition ou on ecrit 2 fois character dans ft_error_token
		else if (cpt > 5)											  	// Si compteur vaut plus de 5
			return (ft_error_msg(line, 'x', i));					   // Alors on return ft_error_msg avec le token x qui va s'occuper du cas ou on ecrit trois fois <<<
		if (i == (int)ft_strlen(line))								  // Si on est a la fin de line
			break ;													 // On quitte la boucle
		i++;														// On passe au caractere suivant
	}
	return (0);													  // On return (0);
}

/*
**	====================================================================================================================================================
**	====================================================================================================================================================
**	
**	Cette fonction prend en parametre :
**	
**	- La ligne donnee par GNL
**	- Le caractere qu'on veut verifier
*/

int	ft_wrong_syntax_redir_check(char *line, char character)
{
	int	i;																					// On creer un index pour parcourir line
	int	cpt;																			   // On creer un compteur pour compter les chevrons

	i = 0;  																			 // On initialise i a 0
	if (ft_wrong_syntax_redir_check_else(line, 0) == -1)								// On test pour le caractere < qui est un cas particulier
		return (-1);																   //
	while (line[i])																	  // Tant que la ligne existe
	{
		cpt = 0;																	// On initialise le compteur a 0
		i = ft_is_inside_quote(line, i);										   // On verifie les quotes
		if (i == (int)ft_strlen(line))											  // Si on est a la fin de line
			break ;																 // Alors on quitte la boucle
		while (line[i] && line[i] == character || line[i] == ' ')				// Tant que on est sur le caractere qu'on veut verifier ou sur un espace
		{
			if (line[i] == character)										  // Si on est sur le caractere qu'on veut verifier
				cpt++;														 // Alors on augmente compteur de 1
			if (cpt == 3)													// Si le compteur vaut 3
				return (ft_error_msg(line, character, i + 2));			   // On retourne le message d'erreur i + 2 car on doit ecrire que un seul > C'est pour ne pas rentrer dans la condition ou on print 2x character dans ft_error_token
			else if (cpt >= 3)											  // En revanche si le compteur vaut plus de 3
				return (ft_error_msg(line, character, i));				 // Alors on return ft_error_msg avec le i inchanger car on veut qu'il rentre dans la condition ou on ecrit 2 fois character dans ft_error_token
			i++;														// On passe au caractere suivant
		}
		if (i == (int)ft_strlen(line))								  // Si on est a la fin de line
			break ;													 // On quitte la boucle
		i++;														// On passe au caractere suivant
	}
	return (0);													  // On return (0);
}