/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:27:22 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 14:01:29 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
