/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:32:28 by admaupie          #+#    #+#             */
/*   Updated: 2022/12/07 13:58:43 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echap(char *str, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = str + i;
	if (tmp[1] == '\0')
		return (0);
	while (tmp[j] != '\0')
	{
		if (j == 0)
			tmp[j] = -tmp[j + 1];
		else
			tmp[j] = tmp[j + 1];
		j++;
	}
	return (1);
}
