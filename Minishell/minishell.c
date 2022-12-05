/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:25:25 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/05 19:00:57 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_ctrl_d(t_mini *data)
{
	if (data->env_tab)
		ft_free(data->env_tab);
	if (data->prompt)
		free(data->prompt);
	data->line = NULL;
	data->env_tab = NULL;
	data->prompt = NULL;
}

/*
**	Cette fonction prend en parametre :
**	
**	- Le pointeur sur structure data
** 
**	========================================
**	
**	Cette fonction sert a faire fonctionner minishell 
*/

int	minishell(t_mini *data)
{
	char	*buffer;

	while (42)
	{
		define_signals();
		buffer = ft_prompt(data);
		if (!buffer)
			return (ft_error("Error: fail getcwd", RED, -1));
		data->line = readline(buffer);
		add_history(data->line);
		if (!data->line)
		{
			ft_ctrl_d(data);
			exit(data->g_error);
		}
		if (data->line[0] == '\0')
			continue ;
		parse(data->line, data);
	}
}
