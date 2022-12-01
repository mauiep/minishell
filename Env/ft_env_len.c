/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 03:39:58 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/25 14:10:37 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- Un pointeur sur structure data
**	
**	========================================
**	
**	Cette fonction sert a retourner la taille du env
*/

int	ft_env_len(t_mini *data)
{
	int	i;

	i = 0;
	while (data->env_tab[i])
	{
		i++;
	}
	return (i);
}
