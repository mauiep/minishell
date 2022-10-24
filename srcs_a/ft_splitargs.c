/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitargs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <ngenadie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:34:36 by admaupie          #+#    #+#             */
/*   Updated: 2022/10/24 22:00:06 by admaupie         ###   ########.fr       */
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
		while ((int)(*tmp)[i] != 0)
		{
			to_free = *tmp;
			while ((*tmp)[i] && (*tmp)[i] != SIMPLE_QUOTE && (*tmp)[i] != 34)
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

int	spe_count_words(char *str)
{
	int	w;
	int	i;
	int	c;

	c = ' ';
	w = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c && c == ' ')
			i++;
		if (str[i])
			w++;
		while (str[i] && (c != ' ' || str[i] != c))
		{
			if (c == ' ' && (str[i] == SIMPLE_QUOTE || str[i] == 34))
				c = str[i];
			else if (c != ' ' && str[i] == c)
				c = ' ';
			i++;
		}
	}
	return (w);
}

int	spe_lenword(char *str)
{
	char	c;
	int		i;

	c = ' ';
	i = 0;
	while (str[i] && (c != ' ' || str[i] != c))
	{
		if (c == ' ' && (str[i] == SIMPLE_QUOTE || str[i] == 34))
			c = str[i];
		else if (c != ' ' && str[i] == c)
			c = ' ';
		i++;
	}
	return (i);
}

char	*spe_get_word(char *str, int n)
{
	int		w;
	int		i;
	int		j;
	char	*new;

	j = 0;
	w = 0;
	i = 0;
	while (w != n)
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i])
			w++;
		i = i + spe_lenword(str + i);
	}
	while (str[i] && str[i] == ' ')
			i++;
	j = spe_lenword(str + i);
	new = ft_strndup(str + i, j);
	if (!new)
		return (NULL);
	//printf("word = %s\n", new);
	return (new);
}

char	**ft_splitargs(t_lst *lst)
{
	char	**new;
	int		i;
	int		j;

	i = spe_count_words(lst->str);
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new[j] = spe_get_word(lst->str, j);
		if (!new[j])
			return (NULL);
		j++;
	}
	new[j] = NULL;
	if (remove_quotes(new) != -1)
		return (new);
	return (NULL);
}
