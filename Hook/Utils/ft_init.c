/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:30:36 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/10 21:39:22 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init(t_mini *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->line = NULL;
	data->cmd = NULL;
	data->home = NULL;
	data->prompt_var = 0;
	data->converted_path = NULL;
	data->prompt = NULL;
}