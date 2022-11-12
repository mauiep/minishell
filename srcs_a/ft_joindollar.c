/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joindollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:21:18 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/08 15:51:28 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

	ft_joindollar sert a remplacer dans la string ptr->str un $ARG par
	sa valeur recuperee dans l'env, ou une string vide si la variable
	n'est pas dans l'env

	Args : 	ptr, le maillon de la liste a traiter
			i, index du $ dans la string
			darr, la copie de l'environnement
	Return : la taille de la string de l'env - 1 ou -42 si malloc error

*/

int	ft_joindollar(t_lst *ptr, int i, t_dynarray *darr)
{
	char	*tmp;
	char	*to_free;
	char	*envval;
	char	*dollar;
	char	*new;
	int		j;
	int		ret;

	j = 1;
	tmp = ptr->str;
	to_free = ft_strndup(tmp, i);
	if (!to_free)
		return (-42);
	while (tmp[i + j] && tmp[i + j] != '\t' && tmp[i + j] != 39
		&& tmp[i + j] != ' ' && tmp[i + j] != 34 && tmp[i + j] != '$')
		j++;
	dollar = ft_strndup(tmp + i + 1, j - 1);
	if (!dollar)
		return (-42);
	envval = ft_getenvval(dollar, darr, 0, 0);
	if (!envval)
		envval = "";
	ret = ft_strlen(envval);
	new = ft_strjoinneg(to_free, envval);
	if (!new)
		return (-42);
	free(to_free);
	to_free = new;
	envval = ft_strndup(tmp + i + j, ft_strlen(tmp + i + j));
	if (!envval)
		return (-42);
	new = ft_strjoin(new, envval);
	if (!new)
		return (-42);
	free(to_free);
	free(dollar);
	free(envval);
	ptr->str = new;
	free(tmp);
	return (ret - 1);
}