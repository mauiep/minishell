/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:30:16 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 12:31:28 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_create_heredoc(char *nb, t_mini *data)
{
	int		fd;
	char	*docname;

	(void)data;
	docname = ft_strjoin2(".tmpfile", nb);
	if (docname == NULL)
		return (-1);
	fd = open(docname, O_WRONLY | O_TRUNC | O_CREAT, 0755);
	free(nb);
	free(docname);
	return (fd);
}

int	ft_handle_heredoc(t_lst *lst, t_mini *data)
{
	t_lst	*tmp;
	int		i;
	int		fd;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		if (tmp->token == 5)
		{
			tmp->num = i;
			fd = ft_create_heredoc(ft_itoa(i), data);
			if (fd < 0)
				return (fd);
			ft_heredoc(tmp->next, data, fd);
			close(fd);
			i++;
		}
		tmp = tmp->next;
	}
	return (1);
}
