/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:59:19 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/25 15:07:58 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_null(int signal)
{
	(void)signal;
}

void	sig_handler(int signal)
{
	if (signal == SIGQUIT)
		rl_replace_line("", 0);
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (signal == SIGSEGV)
	{
		fprintf(stderr, "\nexit\n");
		exit(0);
	}
	return ;
}

void	define_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGSEGV, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
