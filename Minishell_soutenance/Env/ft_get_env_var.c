/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:10:27 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 13:56:58 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env_var(char *env_var, t_mini *data)
{
	int		i;
	char	*found_env_var;

	i = 0;
	if (!env_var)
		return (NULL);
	while (data->env_tab[i])
	{
		if (!ft_strncmp(env_var, data->env_tab[i], ft_strlen(env_var)))
		{
			found_env_var = ft_strndup(data->env_tab[i], ft_strlen(env_var));
			if (!found_env_var)
				return (NULL);
			return (found_env_var);
		}
		i++;
	}
	return (NULL);
}
