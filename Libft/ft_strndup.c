/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:33:16 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/08 05:15:54 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *s, int n)
{
	int		i;
	int		j;
	char	*tab;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (s && s[i])
		i++;
	tab = malloc(sizeof(char) * ((i - n) + 1));
	if (tab == NULL)
		return (NULL);
	i = n + 1;
	while (s && s[i])
	{
		tab[j] = s[i];
		i++;
		j++;
	}
	tab[j] = '\0';
	return (tab);
}
