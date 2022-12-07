/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 02:59:17 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 13:56:54 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_env(char *to_find_env_var, t_mini *data)
{
	int	i;

	i = 0;
	if (!data->env_tab)
		return (-1);
	while (data->env_tab[i])
	{
		if (!ft_strncmp(to_find_env_var, data->env_tab[i]
				, ft_strlen(to_find_env_var)))
			return (i);
		i++;
	}
	return (-1);
}
