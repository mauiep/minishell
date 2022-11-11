/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:25:52 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/11 15:14:30 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			new[i] = - src[i];
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
				i = - 1;
			}
			i++;
		}
		tmp++;
	}
	return (0);
}

int	lst_remove_quotes(t_lst *l)
{
	char	*to_free;
	int		i;
	int		j;
	char	c;

	i = 0;
	to_free = l->str;
	while (l->str[i] != 0)
	{
		to_free = l->str;
		while (l->str[i] && l->str[i] != 39 && l->str[i] != 34)
			i++;
		c = l->str[i];
		if (c != '\0')
		{
			j = 1;
			while (l->str[i + j] && l->str[i + j] != c)
				j++;
			l->str = without_quotes(l->str, i, i + j);
			if (!l->str)
				return (-1);
			free(to_free);
			i = i + j - 1;
		}
	}
	return (1);
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
