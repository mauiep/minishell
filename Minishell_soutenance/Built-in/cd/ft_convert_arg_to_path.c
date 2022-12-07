/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_arg_to_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:56:42 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 13:47:21 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_convert_arg_to_path(char **args, t_mini *data)
{
	char	*converted_path;
	char	*buffer;
	char	*pwd;

	converted_path = ft_add_home_path(args, data);
	if (converted_path)
		return (converted_path);
	pwd = getcwd(NULL, 0);
	buffer = NULL;
	if (args[1][0] == '/')
	{
		converted_path = ft_strdup(args[1]);
		return (converted_path);
	}
	converted_path = ft_strjoin(pwd, "/");
	free(pwd);
	buffer = ft_strdup(converted_path);
	free(converted_path);
	converted_path = ft_strjoin(buffer, args[1]);
	if (!converted_path)
		return (NULL);
	free(buffer);
	return (converted_path);
}
