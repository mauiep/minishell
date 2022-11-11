/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:25:25 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/11 14:46:07 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	minishell(t_mini *data)
{
	char	*buffer;

	while (42)
	{
		buffer = ft_prompt(data);
		if(!buffer)
			return (ft_error("Error: fail getcwd", RED, -1));
		data->line = readline(buffer);
		add_history(data->line);
		if (data->line[0] == '\0')
			continue ;
		if (ft_strncmp("exit", data->line, 4))
				parse(data->line, data);
		else
			ft_exit(data);
	}
}