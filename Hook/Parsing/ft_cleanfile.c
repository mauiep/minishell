/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:54:29 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/25 16:02:58 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**
**	lst_remove_space va remplacer les espaces de fin de lst->str
**	par des caracteres NULL
**
**	Arg : lst, maillon de la liste 
**
*/

void	lst_remove_spaces(t_lst *lst)
{
	int	i;
	int	c;

	i = 0;
	c = ' ';
	while (lst->str[i] && (c != ' ' || lst->str[i] != ' '))
	{
		if (lst->str[i] == c)
			c = ' ';
		else if (lst->str[i] == 39 || lst->str[i] == 34)
			c = lst->str[i];
		i++;
	}
	while (lst->str[i])
	{
		lst->str[i] = '\0';
		i++;
	}
}

/*
**
**	Dans le parsing, on retire les quotes, les espaces en trop et on repasse les 
**	caracteres de l'expand en positif dans la fonction splitargs qui transforme
**	une string en tableau **argv. 
**	Dans le cas ou on a une redirection, il est important d'effectuer les memes
**	operations sur la string du nom de fichier, voila le but de ft_cleanfile.
**
**	Arg : lst, maillon de la liste correspondant a un nom de fichier
**	Return : 1 si la fonction reussi, -1 si malloc error.
**
*/

int	ft_cleanfile(t_lst *lst)
{
	char	*to_free;

	lst_remove_spaces(lst);
	if (lst_remove_quotes(lst) < 0)
		return (-1);
	to_free = lst->str;
	lst->str = ft_strpos(lst->str);
	if (!lst->str)
		return (-1);
	free(to_free);
	return (1);
}
