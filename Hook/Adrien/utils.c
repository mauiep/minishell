/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:03:31 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/11 15:20:52 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_sep(char c)
{
	if (c == ';' || c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	print_err(int err)
{
	if (err == -1)
		write(2, "Error malloc\n", 13);
	else if (err == -2)
		write(2, "Missing quotes\n", 15);
	else if (err == -3)
		write(2, "Syntax error\n", 13);
	else if (err == -4)
		write(2, "Parse error\n", 12);
	return (err);
}

int	which_redirect(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (1);
	else if (ft_strcmp(str, ">") == 0)
		return (2);
	else if (ft_strcmp(str, "<") == 0)
		return (3);
	else if (ft_strcmp(str, ">>") == 0)
		return (4);
	else if (ft_strcmp(str, "<<") == 0)
		return (5);
	else
		return (-1);
}
