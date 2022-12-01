/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:24:13 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/29 13:29:47 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre
**	
**	-La ligne donnee par GNL
**	-Le caractere qu'on veut verifier
**	-L'index dans line
**  
**  ========================================
**  
**  Cette fonction sert a ecrire un message d'erreur par rapport au token donnee
*/

int	ft_error_msg(char *line, char character, int i)
{
	ft_error_token("syntax error near unexpected token `", line, character, i);
	return (-1);
}
