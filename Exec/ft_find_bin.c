/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:09:12 by admaupie          #+#    #+#             */
/*   Updated: 2022/12/08 04:54:25 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- Le nom du binaire
**	- Le path vers ce dernier
**	
**	========================================
**	
**	Cette fonction sert a [a toi d'ecrire]
*/

char	*ft_check_bin_path(char *bin, char *paths)
{
	char	*bin_path;
	char	*init_path;

	if (paths[0] != '/')
		bin_path = malloc(ft_strlen(bin) + ft_len_bef_col(paths) + 5);
	else
		bin_path = malloc(ft_strlen(bin) + ft_len_bef_col(paths) + 4);
	if (bin_path == NULL)
		return ((char *) NULL);
	init_path = bin_path;
	if (paths[0] != '/')
	{
		bin_path[0] = '~';
		bin_path[1] = '/';
		bin_path += 2;
	}
	ft_strncpy2(paths, bin_path, ft_len_bef_col(paths) + 1);
	bin_path[ft_len_bef_col(paths) + 1] = '/';
	ft_strcpy(bin, bin_path + 2 + ft_len_bef_col(paths));
	if (paths[0] != '/')
		bin_path -= 1;
	return (init_path);
}

/*
**	Cette fonction prend en parametre :
**	
**	- Le nom du binaire
**	- Le path vers ce dernier
**	
**	========================================
**	
**	Cette fonction sert a renvoyer la len du path avant de tomber sur un ":"
*/

int	ft_len_bef_col(char *paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (paths[i] == ':')
			return (i - 1);
		i++;
	}
	return (i - 1);
}

/*
**	Cette fonction prend en parametre :
**	
**	- Le paths
**
**	========================================
**	
**	Cette fonction existe uniquement pour la norme des 25 lignes
*/

static char	*ft_find_bin_else(char *paths)
{
	paths += ft_len_bef_col(paths) + 1;
	if (*paths)
		paths += 1;
	return (paths);
}

/*
**	Cette fonction prend en parametre :
**	
**	- Le path vers le binaire
**	- argv
**	- envp

**	========================================
**	
**	Cette fonction sert a executer une commande grace au path
*/

static int	ft_exec(char *bin_path, char **argv, char **envp)
{
	if (access(bin_path, F_OK & X_OK) == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(bin_path, argv, envp);
		perror("execve");
		free(bin_path);
		return (1);
	}
	return (0);
}

/*
**	Cette fonction prend en parametre :
**	
**	- Le nom du binaire
**	- Le path vers ce dernier
**	- L'input utilisateur
**	- Env
**
**	========================================
**	
**	Cette fonction sert a renvoyer la len du path avant de tomber sur un ":"
*/

char	*ft_find_bin(char *bin, char *paths, char **argv, char **envp)
{
	char	*bin_path;
	char	*to_free;

	if (!paths)
		return (NULL);
	if (bin[0] == '/')
		if (ft_exec(bin, argv, envp) == 1)
			return ((char *)1);
	to_free = paths;
	while (*paths)
	{
		bin_path = ft_check_bin_path(bin, paths);
		if (bin_path == NULL)
			return (free(to_free), NULL);
		if (ft_exec(bin_path, argv, envp) == 1)
			return ((char *)1);
		else
			free(bin_path);
		paths = ft_find_bin_else(paths);
	}
	return (free(to_free), NULL);
}
