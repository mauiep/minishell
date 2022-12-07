/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_inside_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:31:01 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 14:01:43 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_inside_quote(char	*line, int i)
{
	char	quote;

	while (line[i] && ((line[i] == '\'') || line[i] == '"'))
	{
		quote = line[i];
		i++;
		while (line[i] && line[i] != quote)
		{
			if (line[i] && line[i] == '\\')
				i++;
			i++;
		}
		if (i == (ft_strlen(line)))
			break ;
		else
			i++;
	}
	return (i);
}
