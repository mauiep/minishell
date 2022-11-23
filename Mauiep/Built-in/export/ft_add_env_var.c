/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:35:57 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/21 15:08:30 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_fill_new_env(t_mini *data, char **env_temp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_free(data->env_tab);
	while (env_temp[i])
		i++;
	data->env_tab = malloc(sizeof(char *) * (i + 1));
	if (!data->env_tab)
		return ;
	while (j < i)
	{
		data->env_tab[j] = ft_strdup(env_temp[j]);
		data->env_tab = ft_if_malloc_issue(data->env_tab, j);
		if (!data->env_tab)
			return ;
		j++;
	}
	data->env_tab[j] = NULL;
	ft_free(env_temp);
}

void	ft_add_env_var(t_mini *data, int arg)
{
	char	**env_temp;
	int		size;
	int		i;

	i = 0;
	size = (ft_env_len(data) + 1);
	env_temp = ft_create_temp_env(data, size);
	while (env_temp[i])
	{
		if (!env_temp[i])
			break ;
		i++;
	}
	env_temp[i] = ft_strdup(data->cmd[arg]);
	env_temp[i + 1] = NULL;
	ft_fill_new_env(data, env_temp);
}