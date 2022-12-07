/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:51:23 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/29 10:07:33 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_redir(char *line)
{
	if (ft_wrong_syntax_newline_check(line) == 0
		&& ft_wrong_syntax_redir_check(line, '>') == 0)
		return (1);
	return (0);
}
