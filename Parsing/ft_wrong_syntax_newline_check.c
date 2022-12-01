/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrong_syntax_newline_check.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:32:17 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/29 10:11:01 by ceatgie          ###   ########.fr       */
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
	int	i;

	i = 0;
	while (line[i])
		i++;
	i -= 1;
	if (line[i] == '>' || line[i] == '<')
		return (ft_error_msg(line, 'n', i));
	while (i >= 0 && (line[i] == ' ' || line[i] == '<' || line[i] == '>'))
	{
		i = ft_is_inside_quote(line, i);
		if (i == (int)ft_strlen(line))
			break ;
		else if (line[i] == '>' || line[i] == '<')
			return (ft_error_msg(line, 'n', i));
		i--;
	}
	return (0);
}
