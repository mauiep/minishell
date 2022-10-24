/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <ngenadie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:07:11 by admaupie          #+#    #+#             */
/*   Updated: 2022/10/24 21:07:31 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strndup(const char *src, int n)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	while (i < n)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
