/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_export_arg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:06:03 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 13:55:46 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_export_var(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !arg[0] || arg[0] == '=')
		return (0);
	else if (arg[0] == '_')
		i++ ;
	else if (ft_isdigit(arg[0]) || !ft_isalpha(arg[0]))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalpha(arg[i]) || ft_isdigit(arg[i]) || arg[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}
