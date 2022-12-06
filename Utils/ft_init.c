/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:30:36 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/06 08:42:21 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(t_mini *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->line = NULL;
	data->home = NULL;
	data->prompt_var = 0;
	data->dup = 1;
	data->i = 0;
	data->converted_path = NULL;
	data->nb_pipes = 0;
	data->pipes_left = 0;
	data->prompt = NULL;
	data->g_error = 0;
	data->command_ok = 0;
	data->envval = NULL;
	data->start_lst = NULL;
	data->lst = NULL;
	data->list = NULL;
	data->splitargs = NULL;
	data->pipefd = NULL;
}
