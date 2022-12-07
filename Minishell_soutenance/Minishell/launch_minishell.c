/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:10:21 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/06 16:45:05 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_minishell(int argc, char **argv, char **envp)
{
	t_mini	data;

	ft_print_minishell();
	ft_init(&data, argc, argv, envp);
	ft_create_env(&data);
	define_signals();
	minishell(&data);
}
