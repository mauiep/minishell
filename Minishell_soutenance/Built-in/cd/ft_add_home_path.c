/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_home_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:32:36 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 13:46:43 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add_home_path(char **args, t_mini *data)
{
	char	*converted_path;
	char	*buffer;
	char	*home;

	converted_path = NULL;
	buffer = NULL;
	if (!ft_strncmp("~/", args[1], 2))
	{
		home = ft_get_env_var("HOME", data);
		converted_path = ft_strjoin(home, "/");
		buffer = ft_strdup(converted_path);
		free (converted_path);
		converted_path = ft_strjoin(buffer, args[1] + 2);
		free(buffer);
		free(home);
		return (converted_path);
	}
	return (NULL);
}
