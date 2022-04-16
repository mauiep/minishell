/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isolate_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:51:44 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/15 17:15:35 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dollar_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

int	double_quoted_arg_has_env(char *str)
{
	int	i;
	int	dollar;

	i = 0;
	dollar = dollar_count(str);
	while (str[i] != 0)
	{
		if (str[i] == '$' && (is_space_or_null_or_dquote(str[i + 1]) == 1))
			dollar--;
		i++;
	}
	return (dollar);
}
