/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:57:13 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/10 21:48:10 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_mini *data)
{
	if (data->line)
		free(data->line);
	if (data->cmd)
		ft_free(data->cmd);
	if (data->env_tab)
		ft_free(data->env_tab);
	if (data->prompt)
		free(data->prompt);
	ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
}