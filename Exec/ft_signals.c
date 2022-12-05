/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:59:19 by admaupie          #+#    #+#             */
/*   Updated: 2022/12/05 18:54:09 by ceatgie          ###   ########.fr       */
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
	return ;
}

void	define_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGSEGV, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
