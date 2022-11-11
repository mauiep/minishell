/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:08:29 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/04 14:04:10 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*tab;

	tab = malloc(elementSize * elementCount);
	if (!tab)
		return (NULL);
	ft_bzero(tab, elementSize * elementCount);
	return (tab);
}
