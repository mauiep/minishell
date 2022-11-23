/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:59:19 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/23 13:59:21 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    sig_null(int signal)
{
    (void)signal;
}

void    sig_handler(int signal)
{
    char    *prompt;

    if (signal == SIGQUIT)
        rl_replace_line("", 0);
    if (signal == SIGINT)
    {
        prompt = getcwd(NULL, 0);
        write(2, "\n", 1);
  	    rl_replace_line("", 0);
        rl_on_new_line();
	    rl_redisplay();
        free(prompt);
    }
    if (signal == SIGSEGV)
	{
		fprintf(stderr, "\nexit\n");
		exit(0);
	}
    return ;
}

void    define_signals(void)
{
    signal(SIGINT, sig_handler);
	signal(SIGSEGV, sig_handler);
    signal(SIGQUIT, SIG_IGN);
}