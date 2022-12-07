/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:27:24 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 13:56:11 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*buffer;

	buffer = NULL;
	buffer = getcwd(NULL, 0);
	if (buffer)
		ft_putendl_fd(buffer, 1);
	else
	{
		write(2, RED, ft_strlen(RED));
		write(2, "minishell: pwd: ", 16);
		ft_putendl_fd(strerror(errno), 2);
		ft_putstr_fd(RESET, 2);
	}
	free(buffer);
}
