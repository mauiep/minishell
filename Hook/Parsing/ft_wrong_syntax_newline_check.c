/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrong_syntax_newline_check.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:32:17 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/28 14:34:36 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre
**	
**	-La ligne donnee par GNL
**	
**	========================================
**	
**	Check si la ligne se finit par un chevron ou 
**	passe les espaces jusqu'a en trouver un
*/

int	ft_wrong_syntax_newline_check(char *line)
{
	int	i;																					// On initialise un index
	i = 0;																				  // On le demarre a 0 pour parcourir la ligne
	while (line[i])																		 // Tant que la ligne existe
		i++;																			// On incremente i pour arriver a la fin
	i-= 1;																			   // On decremente i pour acceder au dernier caractere avant le \0
	if (line[i] == '>' || line[i] == '<')											  // Si ce caractere est un chevron ouvrant ou fermant
		return (ft_error_msg(line, 'n', i));										 // Alors on return ft_error_msg avec le token n qui permettra d'ecrire newline'
	while (line[i] && (line[i] == ' ' || line[i] == '<' || line[i] == '>'))			// Tant que la ligne existe et que on est sur un espace ou un chevron ouvrant ou fermant
	{
		i = ft_is_inside_quote(line, i);										  // On passe les quotes
		if (i == (int)ft_strlen(line))											 // Si on arrive a la fin
			break ;																// Alors on quitte la boucle
		else if (line[i] == '>' || line[i] == '<')							   // Si on se trouve sur un chevron ouvrant ou fermant
			return (ft_error_msg(line, 'n', i));							  // On return ft_error_msg avec le token n qui permettra d'ecrire newline'
		i--;																 // On passe au caractere d'avant 
	}
	return (0);															   // On return (0)
}