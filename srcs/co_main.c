/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   co_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:15:54 by gfritsch          #+#    #+#             */
/*   Updated: 2022/06/11 15:56:48 by niki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char	*line_buffer;

	if (ac != 1)
		return (-1);
	while (1)
	{
		line_buffer = readline("$>");
		if (line_buffer == NULL)
			return (0);
		//parse(line_buffer);
		free(line_buffer);
	}
	printf("arg[%d] = %s\n", 0, av[0]);
	return (0);
}
