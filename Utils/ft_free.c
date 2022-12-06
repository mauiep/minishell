/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:31:32 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/06 16:05:05 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_all(t_mini *data)
{
	if (data->line)
		free(data->line);
	if (data->env_tab)
		ft_free(data->env_tab);
	if (data->prompt)
		free(data->prompt);
	if (data->splitargs)
		ft_free(data->splitargs);
	if (data->list)
		free(data->list);
	if (data->lst)
		free_lst(data->lst);
	if (data->pipefd)
		free_pipe_array(data->pipefd, data->nb_pipes);
}

void	ft_quadrafree(void *s1, void *s2, void *s3, void *s4)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	if (s4)
		free(s4);
}

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
