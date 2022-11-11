/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 09:48:21 by ceatgie           #+#    #+#             */
/*   Updated: 2022/10/29 03:12:23 by ceatgie          ###   ########.fr       */
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
	minishell(&data);
}