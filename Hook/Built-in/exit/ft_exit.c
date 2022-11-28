/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:57:13 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/28 12:04:13 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_mini *data, t_lst *lst)
{
	if (data->line)
		free(data->line);
	if (data->cmd)
		ft_free(data->cmd);
	if (data->env_tab)
		ft_free(data->env_tab);
	if (data->prompt)
		free(data->prompt);
	if (lst)
		free_lst(lst);
	ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
}
