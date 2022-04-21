/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:57:44 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/16 16:22:07 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_quotes(char *str, t_split *split)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i > 0)
		{
			if (str[i] == '\'' && str[i - 1] != '\\')
				split->single_quote++;
			else if (str[i] == '\"' && str[i - 1] != '\\')
				split->double_quote++;
		}
		else
		{
			if (str[i] == '\'')
				split->single_quote++;
			else if (str[i] == '\"')
				split->double_quote++;
		}
		i++;
	}
}

int	skip_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32)
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (dup == NULL)
	{
		perror("ft_strdup(): error allocating dup");
		return (NULL);
	}
	ft_memset((void *)dup, 0, ft_strlen(str) + 1);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}
