/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:52:14 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/28 10:07:23 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	char	*str;
	char	**cmd;
	t_mini	data;

	ft_print_minishell();
	ft_init(&data, argc, argv, envp);
	ft_create_env(&data);
	define_signals();
	minishell(&data);
	return (0);
}
