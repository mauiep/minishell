/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:38:05 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 13:56:40 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_env(t_mini *data)
{
	int	i;

	i = 0;
	while (data->envp && data->envp[i])
		i++;
	data->env_tab = malloc(sizeof(char *) * (i + 1));
	if (!data->env_tab)
		return ;
	i = 0;
	while (data->envp && data->envp[i])
	{
		data->env_tab[i] = ft_strdup(data->envp[i]);
		i++;
	}
	data->env_tab[i] = NULL;
}
