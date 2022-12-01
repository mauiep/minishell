/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if_malloc_issue.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:51:15 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/29 11:58:18 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Cette fonction prend en parametre :
**	
**	- Le double tableau tab
**	- L'index de la derniere string malloc
**	
**	========================================
**	
**	Cette fonction free tab si le malloc d'une string s'est mal passer
**	Sinon elle renvoie tab
*/

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
