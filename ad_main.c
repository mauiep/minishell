/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ad_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:16:24 by admaupie          #+#    #+#             */
/*   Updated: 2022/07/22 17:16:27 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*line_buffer;
	t_dynarray	darr;


	(void)av;
	if (ac != 1)
		return (-1);
	if (init_dyn_env(envp, &darr))
		return (-1);
	while (1)
	{
		line_buffer = readline("$admaupie>");
		if (line_buffer == NULL)
			return (0);
		add_history(line_buffer);
		parse(line_buffer, &darr);
		free(line_buffer);
	}
	return (0);
}
