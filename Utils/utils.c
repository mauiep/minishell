/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:03:31 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/18 15:04:43 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_ok(char *str)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (str && str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			cpt++;
		i++;
	}
	if (cpt == ft_strlen(str))
		return (0);
	return (1);
}

int	is_sep(char c)
{
	if (c == ';' || c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	print_err(int err)
{
	if (err == -1)
		return (ft_error("minishell: Malloc error\n", RED, -1));
	else if (err == -2)
		return (ft_error("minishell: Missing quotes\n", RED, -2));
	else if (err == -3)
		return (ft_error("minishell: Syntax error\n", RED, -3));
	else if (err == -4)
		return (ft_error("minishell: Parse error\n", RED, -4));
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
