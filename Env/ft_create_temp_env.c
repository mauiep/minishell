/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_temp_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:40:16 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/18 15:02:37 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**ft_create_temp_env(t_mini *data, int size)
{
	char	**temp_env;
	int		i;

	temp_env = malloc(sizeof(char *) * (size + 1));
	if (!temp_env)
		return (NULL);
	i = 0;
	while (data->env_tab[i])
	{
		temp_env[i] = ft_strdup(data->env_tab[i]);
		temp_env = ft_if_malloc_issue(temp_env, i);
		if (!temp_env)
			return (NULL);
		i++;
	}
	temp_env[i] = NULL;
	return (temp_env);
}