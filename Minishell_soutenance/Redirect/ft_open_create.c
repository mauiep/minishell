/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:17:44 by admaupie          #+#    #+#             */
/*   Updated: 2022/12/07 14:01:07 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_open_create_else(int token, char *pathname2, bool apnd_or_not)
{
	int	fd;

	if (token == 3)
		return (dprintf(2, "File not found\n"), -1);
	fd = open(pathname2, O_RDWR | O_CREAT | O_APPEND * apnd_or_not, S_IRWXU);
	return (fd);
}

int	ft_open_create(char *filename, bool apnd_or_not, int token)
{
	int		fd;
	char	*pathname;
	char	*pathname2;
	char	buffer[10000];

	pathname = ft_strjoin(getcwd(buffer, 10000), "/");
	pathname2 = ft_strjoin(pathname, filename);
	free(pathname);
	if (access(pathname2, F_OK))
	{
		fd = ft_open_create_else(token, pathname2, apnd_or_not);
		if (fd == -1)
			return (free(pathname2), ft_error("Cannot create file\n", RED, -1));
	}
	else if (!access(pathname2, R_OK | W_OK))
	{
		fd = open(pathname2, O_CREAT | O_WRONLY | O_TRUNC);
		if (fd == -1)
			return (free(pathname2), ft_error("Cannot Open File\n", RED, -1));
	}
	else
		return (free(pathname2), ft_error("File permission denied\n", RED, -1));
	return (free(pathname2), fd);
}
