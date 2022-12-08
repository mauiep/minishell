/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 05:13:42 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/08 05:14:32 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_for_error_dot(char *line)
{
	if (line[0] == '.')
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		ft_putstr_fd(RESET, 2);
		return (0);
	}
	return (1);
}

static int	ft_for_error_double_dot(char *line)
{
	if (line[0] == '.' && line[1] == '.')
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("minishell: ..: command not found\n", 2);
		ft_putstr_fd(RESET, 2);
		return (0);
	}
	return (1);
}

int	ft_for_error_directory(char *line)
{
	char	*buffer;

	buffer = NULL;
	if (line[0] == '\0')
		return (ft_error("minishell: command not found\n", RED, 0));
	if (ft_for_error_double_dot(line) == 0)
		return (0);
	if (ft_for_error_dot(line) == 0)
		return (0);
	if (line[0] == '/')
	{
		buffer = spe_get_word(line, 0);
		if (!buffer)
			return (0);
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(buffer, 2);
		ft_putstr_fd(" No such file or directory\n", 2);
		ft_putstr_fd(RESET, 2);
		free(buffer);
		return (0);
	}
	return (1);
}

int	ft_error_for_executable(char **args, t_mini *data)
{
	ft_error("minishell: ", RED, 42);
	ft_error(args[0], RED, 42);
	ft_error(": No such file or directory", RED, 42);
	ft_error("\n", RED, 42);
	ft_free_all(data);
	ft_free(args);
	data->g_error = 127;
	return (data->g_error);
}
