/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 03:33:01 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/08 18:37:37 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quoted_good(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = str[i];
	if (ft_strlen(str) == 1)
		return (-1);
	while (str[i])
	{
		if (i > 0 && str[i] == quote)
			return (0);
		i++;
	}
	return (-1);
}

void	to_quote_or_not_to_quote(char *str, int i, t_split *split)
{
	if (((str[i] == '\'') || (str[i] == '\"')) && split->quote == 0)
	{
		if (i > 0)
		{
			if (str[i - 1] != '\\')
				split->quote = str[i];
		}
		else if (i == 0)
				split->quote = str[i];
	}
	else if (i > 0
		&& ((str[i] == '\'' && str[i - 1] != '\\'
				&& split->quote == '\'') || (str[i] == '\"'
				&& str[i - 1] != '\\' && split->quote == '\"')))
		split->quote = 0;
}
