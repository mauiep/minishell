/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrong_syntax_redir_check.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:30:56 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/29 10:46:44 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- L'input de l'utilisateur
**	- L'index qui parcours ligne
**	- Le compteur de "<"
**	
**	========================================
**	
**	Cette fonction n'existe que pour la norme (25 lignes)
*/

static int	ft_error_else(char *line, int i, char cpt)
{
	if (cpt == 3)
		return (-1);
	if (cpt == 4)
		return (ft_error_msg(line, '<', i + 2));
	else if (cpt == 5)
		return (ft_error_msg(line, '<', i));
	else if (cpt > 5)
		return (ft_error_msg(line, 'x', i));
	return (1);
}

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
	int	cpt;

	while (line[i])
	{
		cpt = 0;
		i = ft_is_inside_quote(line, i);
		if (i == (int)ft_strlen(line))
			break ;
		while (line[i] && line[i] == '<')
		{
			if (line[i] == '<')
				cpt++;
			i++;
		}
		if (ft_error_else(line, i, cpt) == -1)
			return (-1);
		if (i == (int)ft_strlen(line))
			break ;
		i++;
	}
	return (0);
}

/*
**	Cette fonction prend en parametre :
**	
**	- L'input de l'utilisateur
**	- Le caractere qu'on veut verifier
**	- L'index qui parcours l'input
**	- Le compteur de charcater
**	
**	========================================
**	
**	Cette fonction sert a compter le nombre de "<" et de ">"
**	Et si il y en a trop retourner l'erreur correspondante
*/

static int	ft_count_and_print_error(char *line, char character, int i, int cpt)
{
	while ((line[i] && line[i] == character) || line[i] == ' ')
	{
		if (line[i] == character)
			cpt++;
		if (cpt == 3)
			return (ft_error_msg(line, character, i + 2));
		else if (cpt >= 3)
			return (ft_error_msg(line, character, i));
		i++;
	}
	return (i);
}

/*
**	
**	Cette fonction prend en parametre :
**	
**	- La ligne donnee par GNL
**	- Le caractere qu'on veut verifier
**	
**	========================================
**	
**	Cette fonction sert a compter le nombre de "<" et de ">"
**	Et si il y en a trop retourner l'erreur correspondante
*/

int	ft_wrong_syntax_redir_check(char *line, char character)
{
	int	i;
	int	cpt;

	i = 0;
	if (ft_wrong_syntax_redir_check_else(line, 0) == -1)
		return (-1);
	while (line[i])
	{
		cpt = 0;
		i = ft_is_inside_quote(line, i);
		if (i == ft_strlen(line))
			break ;
		i = ft_count_and_print_error(line, character, i, cpt);
		if (i == ft_strlen(line))
			break ;
		else if (i == -1)
			return (-1);
		i++;
	}
	return (0);
}
