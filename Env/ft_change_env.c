/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:27:17 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/25 14:07:11 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- Un pointeur sur structure data
**	- L'index de la variable d'environement que l'on veut modifier
**	- Le path
**	- La variable d'environement que l'on veut modifier
**
**	========================================
**	
**	Cette fonction existe uniquement pour la norme des 25 lignes
*/

static void	ft_change_env_else(t_mini *data, int i, char *pwd,
		char *env_var)
{
	char	*buffer;

	free(data->env_tab[i]);
	data->env_tab[i] = ft_strjoin(env_var, "=");
	if (!data->env_tab[i])
		return ;
	buffer = ft_strdup(data->env_tab[i]);
	if (!buffer)
		return ;
	free(data->env_tab[i]);
	data->env_tab[i] = ft_strjoin(buffer, pwd);
	if (!data->env_tab[i])
		return ;
	free(buffer);
}

/*
**	Cette fonction prend en parametre :
**	
**	- Le path
**	- La variable d'environement que l'on veut modifier
**	- Le pointeur sur structure data
**
**	========================================
**	
**	Cette fonction sert a modifier une variable d'environement
*/

void	ft_change_env(char *pwd, char *env_var, t_mini *data)
{
	int		i;
	char	*backup_env;

	i = 0;
	i = ft_find_env(env_var, data);
	backup_env = ft_strdup(data->env_tab[i]);
	if (!backup_env)
		return ;
	ft_change_env_else(data, i, pwd, env_var);
	if (!data->env_tab[i])
	{
		ft_free(data->env_tab);
		data->env_tab[i] = ft_strdup(backup_env);
		if (!data->env_tab[i])
			return ;
		free(backup_env);
		return ;
	}
	free(backup_env);
}
