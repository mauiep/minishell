/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_for_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:00:05 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/08 01:47:16 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_last_heredoc(t_lst *lst)
{
	t_lst	*tmp;

	tmp = lst->next;
	while (tmp)
	{
		if (tmp->token == 5)
			return (0);
		else if (tmp->token == 1)
			return (1);
		tmp = tmp->next;
	}
	return (1);
}

int	ft_for_token2(t_lst *lst, t_mini *data, int fd)
{
	fd = ft_open_create(lst->next->str, 0, 2);
	if (fd == -1)
		return (-1);
	if (data->dup && dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), -1);
	close(fd);
	return (fd);
}

int	ft_for_token3(t_lst *lst, t_mini *data, int fd)
{
	fd = ft_open_create(lst->next->str, 0, 3);
	if (fd == -1)
		return (-1);
	if (data->dup && dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), -1);
	close(fd);
	return (fd);
}

int	ft_for_token4(t_lst *lst, t_mini *data, int fd)
{
	fd = ft_open_create(lst->next->str, 1, 4);
	if (fd == -1)
		return (-1);
	if (data->dup && dup2(fd, STDOUT_FILENO) < 0)
		return (close(fd), -1);
	close(fd);
	return (fd);
}

int	ft_for_token5(t_lst *lst, t_mini *data, int fd)
{
	char	*docname;
	char	*to_free;

	to_free = ft_itoa(lst->num);
	if (!to_free)
		return (-1);
	docname = ft_strjoin2(".tmpfile", to_free);
	if (!docname)
		return (-1);
	free(to_free);
	fd = open(docname, O_RDONLY);
	if (fd == -1)
		return (-1);
	unlink(docname);
	free(docname);
	if (data->dup && is_last_heredoc(lst) && dup2(fd, STDIN_FILENO) < 0)
		return (close(fd), -1);
	close(fd);
	return (fd);
}
