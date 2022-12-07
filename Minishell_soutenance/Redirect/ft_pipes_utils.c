/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:06:47 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/29 13:18:26 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*ft_next_pipe(t_lst *lst)
{
	while (lst && lst->token != 1)
		lst = lst->next;
	return (lst);
}

int	ft_pipes_left(t_lst *lst)
{
	int	pipes;

	pipes = 0;
	if (!lst)
		return (-1);
	while (lst->next)
	{
		if (lst->next->token == 1)
			pipes++;
		lst = lst->next;
	}
	return (pipes);
}

int	ft_init_pipe_var(t_mini *data, int nb_pipes, t_lst *lst)
{
	data->pipes_left = nb_pipes;
	data->pipefd = create_pipe_arr(nb_pipes);
	if (!data->pipefd)
		return (0);
	data->i = 0;
	data->start_lst = lst;
	data->fd_in = 0;
	data->list = malloc(sizeof(pid_t) * (nb_pipes + 1));
	if (!data->list)
		return (-1);
	return (1);
}
