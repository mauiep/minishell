/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:35:57 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 13:55:41 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_does_export_name_already_exists(char *arg, t_mini *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arg[i] && !(arg[i] == '='))
		i++;
	while (data->env_tab[j])
	{
		if (!strncmp(arg, data->env_tab[j], i))
			return (j);
		j++;
	}
	return (0);
}

static void	ft_add_env_var_with_no_equal(char *arg, t_mini *data)
{
	int		i;

	if (ft_does_export_name_already_exists(arg, data))
		return ;
	i = 0;
	data->env_tab = ft_create_temp_env(data, ft_env_len(data));
	while (data->env_tab[i])
		i++;
	data->env_tab[i] = ft_strdup(arg);
	data->env_tab = ft_if_malloc_issue(data->env_tab, i);
	if (!data->env_tab)
		return ;
}

static void	ft_add_env_var_with_equal(char *arg, t_mini *data)
{
	int	i;
	int	pos;

	i = 0;
	pos = ft_does_export_name_already_exists(arg, data);
	if (pos)
	{
		free(data->env_tab[pos]);
		data->env_tab[pos] = ft_strdup(arg);
		data->env_tab = ft_if_malloc_issue(data->env_tab, pos);
		if (!data->env_tab)
			return ;
		return ;
	}
	data->env_tab = ft_create_temp_env(data, ft_env_len(data));
	i = 0;
	while (data->env_tab[i])
		i++;
	data->env_tab[i] = ft_strdup(arg);
	data->env_tab = ft_if_malloc_issue(data->env_tab, i);
	if (!data->env_tab)
		return ;
}

static int	ft_is_equal_in_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (-1);
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_add_env_var(char *arg, t_mini *data)
{
	if (ft_is_equal_in_arg(arg) == -1)
		return ;
	else if (ft_is_equal_in_arg(arg) == 1)
		ft_add_env_var_with_equal(arg, data);
	else if (ft_is_equal_in_arg(arg) == 0)
		ft_add_env_var_with_no_equal(arg, data);
}
