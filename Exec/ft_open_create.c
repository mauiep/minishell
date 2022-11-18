/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:17:44 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/18 19:17:46 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_create(char *filename, bool apnd_or_not, int token)
{
	int		fd;
	char	*pathname;
	char	*pathname2;
	char	buffer[10000];

	pathname = ft_strjoin(getcwd(buffer, 10000), "/");
	pathname2 = ft_strjoin(pathname, filename);
	free(pathname);
	if (access(pathname2, F_OK))/*no file found*/
	{
		if (token == 3)
			return (free(pathname2), dprintf(2, "File not found\nPATHNAME=%s ET PATHNAME2=%s\n", pathname, pathname2), -1);
		fd = open(pathname2, O_RDWR | O_CREAT | O_APPEND * apnd_or_not, S_IRWXU);
		if (fd == -1)
			return (free(pathname2), dprintf(2, "Cannot create file\n"), -1);
	}
	else if (!access(pathname2, R_OK | W_OK)) /*ask if we can r/w on file*/
	{
		fd = open(pathname2, O_RDWR | O_APPEND * apnd_or_not);
		if (fd == -1)
			return (free(pathname2), dprintf(2, "Cannot Open File\n"), -1);
	}
	else
		return (free(pathname2), dprintf(2, "File permission denied\n"), -1);
	return (free(pathname2), fd);
}
