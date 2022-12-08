/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:23:26 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 15:24:25 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_parse_error(char *linebuffer, t_lst *lst)
{
	int	ret;

	ret = ft_verif(lst, linebuffer);
	if (ret <= 0)
	{
		free_lst(lst);
		if (ret == 0)
			print_err(-4);
		return (-1);
	}
	return (0);
}

static int	parse_else_else(char *line_buffer, int i, t_lst *lst)
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

static int	parse_else(char *line_buffer, t_mini *data, int i, t_lst *lst)
{
	i = 0;
	while (line_buffer[i])
	{
		i = parse_else_else(line_buffer, i, lst);
		if (i < 0)
			return (i);
	}
	if (ft_parse_error(line_buffer, lst) < 0)
		return (-1);
	if (expand(lst, data) == -1)
	{
		free_lst(lst);
		return (-1);
	}
	if (data->command_ok == 1)
	{
		data->nb_pipes = ft_pipes_left(lst);
		if (ft_pipes(lst->next, data->nb_pipes, data) == -1)
			return (-1);
	}
	free_lst(lst);
	return (1);
}

int	parse(char *line_buffer, t_mini *data)
{
	int		i;
	t_lst	*lst;
	int		ret;
	int		error;

	ft_tab_to_spaces(line_buffer);
	ret = ft_check_redir(line_buffer);
	if (!ret)
		return (-1);
	lst = ft_lstnew();
	if (!lst)
		return (print_err(-1));
	data->lst = lst;
	i = 0;
	if (command_ok(line_buffer) == 1)
		data->command_ok = 1;
	error = parse_else(line_buffer, data, i, lst);
	return (error);
}
