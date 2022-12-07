/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_unset_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:09:18 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/07 13:56:18 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_unset_arg(char *arg)
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
	while (arg[i])
	{
		if (ft_isalpha(arg[i]) || ft_isdigit(arg[i]) || arg[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}
