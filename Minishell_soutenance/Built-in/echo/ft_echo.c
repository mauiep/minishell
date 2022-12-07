/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:26:41 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 13:54:55 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_if_n_option(char **args)
{
	int	i;

	i = 0;
	while (args[1] && args[1][i])
	{
		if (args[1][0] == '-')
		{
			i++;
			while (args[1] && args[1][i])
			{
				if (args[1][i] != 'n')
					return (0);
				i++;
			}
		}
		return (1);
	}
	return (1);
}

static int	ft_for_n_option(char **args)
{
	int	i;

	i = 2;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	return (1);
}

/*
**	Cette fonction prend en parametre :
**	
**	- Les arguments de echo
**	
**	========================================
**	
**	Cette fonction sert a faire fonctionner echo sans le "-n"
**	Et fonctionne ainsi :
**	
**	- Tant que il existe des arguments
**	- On ecris les arguments suivi d'un saut a la ligne
**	- On return (1)
*/

int	ft_for_no_n_option(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
	return (1);
}

/*
**	Cette fonction prend en parametre :
**	
**	- Les arguments de echo
**	
**	========================================
**	
**	Cette fonction sert a faire fonctionner echo avec et sans "-n"
**	Et fonctionne ainsi :
**	
**	- Si il n'y a pas d'argument
**	- On ecrit un saut a la ligne
**	
**	========================================
**	
**	- Si le 1er argument est "-n"
**	- Tant que il existe des arguments
**	- On ecrit les arguments suivi d'un saut a la ligne
**	- On return (1)
*/

int	ft_echo(char **args)
{
	if (!args[1])
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	if (ft_check_if_n_option(args))
		return (ft_for_n_option(args));
	else
		return (ft_for_no_n_option(args));
}
