/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:27:22 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/29 13:30:06 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre
**	
**	-Le message d'erreur
**	-La ligne donnee par GNL
**	-Le caractere qu'on veut verifier
**	-L'index dans line
**
**	==============================================
**	
**	Cette fonction sert a ecrire la bonne erreur en fonction du caractere
**	Que l'on veut verifier
*/

int	ft_error_token(char	*msg, char *line, char character, int i)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	if (character == 'n')
		ft_putstr_fd("newline\'", 2);
	else if (character == 'x')
	{
		ft_putchar_fd('<', 2);
		ft_putchar_fd('<', 2);
		ft_putchar_fd('<', 2);
		ft_putstr_fd("\'", 2);
	}
	else if (line[i + 1] == character || (i > 0 && line[i - 1] == character))
	{
		ft_putchar_fd(character, 2);
		ft_putchar_fd(character, 2);
		ft_putstr_fd("\'", 2);
	}
	else
	{
		ft_putchar_fd(character, 2);
		ft_putstr_fd("\'", 2);
	}
	ft_putendl_fd(RESET, 2);
	return (-1);
}
