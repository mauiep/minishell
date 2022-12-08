/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:51:23 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/08 04:56:28 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_space_before_pipe(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] == ' ')
	{
		i++;
	}
	if (line[i] == '|')
		return (ft_error("minishell: syntax error near unexpected token `|'\n",
				RED, -2));
	else if (line[i] == '\0')
		return (-3);
	return (1);
}

static int	ft_for_error_directory_no_fork(char *line)
{
	char	*buffer;

	buffer = NULL;
	if (line[0] == '/')
	{
		buffer = spe_get_word(line, 0);
		if (!buffer)
			return (0);
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(buffer, 2);
		ft_putstr_fd(" No such file or directory\n", 2);
		ft_putstr_fd(RESET, 2);
		free(buffer);
		return (0);
	}
	return (1);
}

int	ft_check_redir(char *line)
{
	if (ft_check_space_before_pipe(line) < 0)
		return (0);
	if (line[0] == '\"' && line[1] == '\"')
		return (ft_error("minishell: command not found\n", RED, 0));
	if (line[0] == '.' && !line[1])
		return (ft_error("minishell: .: filename argument required\n", RED, 0),
			ft_error(".: usage: . filename [arguments]\n", RED, 0));
	if (line[0] == '.' && line[1] == '.')
		return (ft_error("minishell: ..: command not found\n", RED, 0));
	if (line[0] == '/' && !line[1])
		return (ft_error("minishell: /: Is a directory\n", RED, 0));
	if (line[0] == '/' && line[1] == '/')
		return (ft_error("minishell: //: Is a directory\n", RED, 0));
	if (ft_for_error_directory_no_fork(line) == 0)
		return (0);
	if (ft_wrong_syntax_newline_check(line) == 0
		&& ft_wrong_syntax_redir_check(line, '>') == 0)
		return (1);
	return (0);
}
