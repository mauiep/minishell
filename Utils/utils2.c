/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:49:57 by admaupie          #+#    #+#             */
/*   Updated: 2022/12/05 13:25:24 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quadrafree(void *s1, void *s2, void *s3, void *s4)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	if (s4)
		free(s4);
}

void	ft_tab_to_spaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != 0)
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}

int	ft_negstrcpy(char *str, char *str2)
{
	int	i;

	i = 0;
	if (!str || !str2)
		return (1);
	while (str[i])
	{
		if (str[i] != ' ')
			str2[i] = -str[i];
		else
			str2[i] = ' ';
		i++;
	}
	str2[i] = '\0';
	return (0);
}

char	*ft_strjoinneg(char *str, char *str2)
{
	char	*str3;

	if (!str || !str2)
		return (NULL);
	str3 = malloc(ft_strlen(str) + ft_strlen(str2) + 1);
	if (str3 == NULL)
		return (NULL);
	ft_strcpy(str, str3);
	ft_negstrcpy(str2, str3 + ft_strlen(str));
	str3[ft_strlen(str) + ft_strlen(str2)] = '\0';
	return (str3);
}
