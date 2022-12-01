/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_export_arg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:06:03 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/25 12:22:47 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- L'argument de export
**
**	========================================
**	
**	Cette fonction sert a parser l'arg de export
**	Et fonctionne ainsi :

**	- Si il n'y a pas d'argument ou que l'argument commence par "="
**	- On return (0)
**	
**	========================================
**	 
**	- Si le nom de la variable commence par un "_" on passe
**	- Si le nom de la variable commence par un nombre
**	 Ou ne commence pas par un caractere alphabetique
**	- On return (0);
**	
**	========================================
**	 
**	- Tant que on est pas sur le signe "=" ou tant que l'arg n'est pas finit
**	- Si le nom de la variable comporte des chiffres
**	 Ou si le nom de la variable comporte des caracteres alphabetiques
**	Ou si le nom de la variable comporte des "_"
**	- Alors on return (1)
**	- Sinon on return (0);
*/

int	ft_check_export_var(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !arg[0] || arg[0] == '=')
		return (0);
	else if (arg[0] == '_')
		i++ ;
	else if (ft_isdigit(arg[0]) || !ft_isalpha(arg[0]))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalpha(arg[i]) || ft_isdigit(arg[i]) || arg[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}
