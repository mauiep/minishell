/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:09:26 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/25 15:18:43 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- Le pointeur sur structure data
** 
**	========================================
**	
**	Cette fonction sert a free pour l'affichage du prochain prompt
*/

static void	ft_check_free(t_mini *data)
{
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	if (data->line)
		free(data->line);
}

/*
**	Cette fonction prend en parametre :
**	
**	- Le pointeur sur structure data
** 
**	========================================
**	
**	Cette fonction existe uniquement a cause de la norme des 25 lignes
*/

static void	ft_prompt_else(t_mini *data)
{
	char	*tmp;

	tmp = ft_get_env_var("PWD", data);
	if (!tmp)
		return ;
	data->prompt = ft_strjoin(GREEN, tmp);
	if (!data->prompt)
		return ;
	free(tmp);
	tmp = ft_strdup(data->prompt);
	if (!tmp)
		return ;
	free(data->prompt);
	data->prompt = ft_strjoin(tmp, "$> ");
	if (!data->prompt)
		return ;
	free(tmp);
	tmp = ft_strdup(data->prompt);
	if (!tmp)
		return ;
	free(data->prompt);
	data->prompt = ft_strjoin(tmp, RESET);
	if (!data->prompt)
		return ;
	free(tmp);
}

/*
**	Cette fonction prend en parametre :
**	
**	- Le pointeur sur structure data
** 
**	========================================
**	
**	Cette fonction sert a afficher le prompt
*/

char	*ft_prompt(t_mini *data)
{
	char	*tmp;
	char	*buffer;

	ft_check_free(data);
	buffer = getcwd(NULL, 0);
	if (!buffer)
	{
		ft_prompt_else(data);
		return (data->prompt);
	}
	data->prompt = ft_strjoin(GREEN, buffer);
	free(buffer);
	tmp = ft_strdup(data->prompt);
	free(data->prompt);
	data->prompt = ft_strjoin(tmp, "$> ");
	free(tmp);
	tmp = ft_strdup(data->prompt);
	free(data->prompt);
	data->prompt = ft_strjoin(tmp, RESET);
	free(tmp);
	data->prompt_var++;
	return (data->prompt);
}
