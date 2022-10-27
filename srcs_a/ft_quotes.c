/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:25:52 by admaupie          #+#    #+#             */
/*   Updated: 2022/10/26 18:47:32 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

char	*without_quotes(char *src, int i, int j)
{
	char	*str1;
	char	*str2;
	char	*str3;
	char	*new;

	str1 = ft_strndup(src, i);
	if (!str1)
		return (NULL);
	str2 = ft_strndup(src + i + 1, j - i - 1);
	if (!str2)
		return (NULL);
	str3 = ft_strndup(src + j + 1, ft_strlen(src + j + 1));
	if (!str3)
		return (NULL);
	new = ft_strjoin(str1, str2);
	if (!new)
		return (NULL);
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

int remove_quotes(char **tab)
{
	int		i;
	int		j;
	char	c;
	char	**tmp;
	char	*to_free;

	i = 0;
	tmp = tab;
	while ((*tmp) != NULL)
	{
		while ((*tmp)[i] != 0)
		{
			to_free = *tmp;
			while ((*tmp)[i] && (*tmp)[i] != 39 && (*tmp)[i] != 34)
				i++;
			c = (*tmp)[i];
			if (c != '\0')
			{
				j = 1;
				while ((*tmp)[i + j] && (*tmp)[i + j] != c)
					j++;
				*tmp = without_quotes(*tmp, i, i + j);
				if (!(*tmp))
					return (-1);
				free(to_free);
				i = i + j - 1;
			}
		}
		i = 0;
		tmp++;
	}
	return (0);
}
