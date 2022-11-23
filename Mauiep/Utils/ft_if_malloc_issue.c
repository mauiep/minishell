/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if_malloc_issue.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:51:15 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/18 15:03:38 by ceatgie          ###   ########.fr       */
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
	if (!tab[i])					// Si le malloc de la nouvelle a rater
	{
		ft_free(tab);			  // On free tout le tableau
		return (NULL);				 // On return (NULL);
	}
	return (tab);			   // Sinon on return new env
}