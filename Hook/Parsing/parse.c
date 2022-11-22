/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:23:26 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/22 15:49:45 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int parse_else(char *line_buffer, int i, t_lst *lst)
{
	int	len;

	len = 1;
	if (!is_sep(line_buffer[i]) && line_buffer[i] != ' ')
		len = push_word(lst, line_buffer + i);
	else if (line_buffer[i] != ' ')
		len = push_sep(lst, line_buffer + i);
	if (len < 0)
		return (print_err(len) + free_lst(lst));
	return (i + len);
}

int	parse(char *line_buffer, t_mini *data)
{
	int		i;
	int		len;
	t_lst	*lst;

	lst = ft_lstnew();
	if (!lst)
		return (print_err(-1));
	i = 0;
	while (line_buffer[i])
	{
		i = parse_else(line_buffer, i, lst);
		if (i < 0)
		{
			free(lst);
			return (i);
		}
	}
	if (!ft_verif(lst))
	{
		free(lst);
		return (print_err(-4));
	}
	if (expand(lst, data) == -1)
	{
		free(lst);
		return (printf("BUG EXPAND\n"));
	}
	ft_pipes(lst->next, ft_pipes_left(lst), data);
	free_lst(lst);
	return (1);
}
