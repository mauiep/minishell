/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:25:52 by admaupie          #+#    #+#             */
/*   Updated: 2022/12/08 05:09:14 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static char	*without_quotes_else(char *str1, char *str2, char *str3, char *new)
{
	free(str1);
	free(str2);
	str1 = new;
	new = ft_strjoin(new, str3);
	if (!new)
		return (NULL);
	free(str1);
	free(str3);
	return (new);
}

char	*without_quotes(char *src, int i, int j)
{
	char	*str1;
	char	*str2;
	char	*str3;
	char	*new;

	str1 = ft_strndup2(src, i);
	if (!str1)
		return (NULL);
	str2 = ft_strndup2(src + i + 1, j - i - 1);
	if (!str2)
		return (NULL);
	str3 = ft_strndup2(src + j + 1, ft_strlen(src + j + 1));
	if (!str3)
		return (NULL);
	new = ft_strjoin2(str1, str2);
	if (!new)
		return (NULL);
	return (without_quotes_else(str1, str2, str3, new));
}

char	*ft_strpos(char *src)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!new)
		return (NULL);
	while (src[i] != '\0')
	{
		if (src[i] > 0)
			new[i] = src[i];
		else
			new[i] = -src[i];
		i++;
	}
	new[i] = 0;
	return (new);
}

int	ft_negtopos(char **tab)
{
	char	**tmp;
	char	*to_free;
	int		i;

	i = 0;
	tmp = tab;
	while ((*tmp) != NULL)
	{
		i = 0;
		while ((*tmp) && (*tmp)[i])
		{
			to_free = *tmp;
			if ((*tmp)[i] < 0)
			{
				*tmp = ft_strpos(*tmp);
				if (!(*tmp))
					return (-1);
				free(to_free);
				i = -1;
			}
			i++;
		}
		tmp++;
	}
	return (0);
}
