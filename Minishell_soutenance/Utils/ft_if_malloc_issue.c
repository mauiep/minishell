/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if_malloc_issue.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:51:15 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 14:01:36 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_if_malloc_issue(char **tab, int i)
{
	if (!tab[i])
	{
		ft_free(tab);
		return (NULL);
	}
	return (tab);
}
