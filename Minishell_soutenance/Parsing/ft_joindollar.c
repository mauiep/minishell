/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joindollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:21:18 by admaupie          #+#    #+#             */
/*   Updated: 2022/12/06 16:09:23 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	char_is_a_valid_dollar(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}

char	*dollarval(char *tmp, int i, int j, t_mini *data)
{
	char	*dollar;
	char	*envval;

	dollar = ft_strndup2(tmp + i + 1, j - 1);
	if (!dollar)
		return (NULL);
	envval = ft_get_env_var(dollar, data);
	if (!envval)
		envval = ft_strndup2("", 0);
	free(dollar);
	return (envval);
}

int	return_dollar(char *str, char *tmp, char *envval, t_lst *ptr)
{
	int		ret;
	char	*to_free;

	to_free = ptr->str;
	ptr->str = ft_strjoin2(ptr->str, str);
	if (!ptr->str)
		return (-42);
	ret = ft_strlen(envval) - 1;
	if (ret == -1)
		ret = 0;
	ft_quadrafree(str, envval, tmp, to_free);
	return (ret);
}

static int	ft_joindollar_else(char *tmp, t_mini *data, int i, int j)
{
	if (tmp[i + j] == '?' && j++)
		data->envval = ft_itoa(data->g_error);
	else
	{
		while (char_is_a_valid_dollar(tmp[i + j]) == 1)
			j++;
		data->envval = dollarval(tmp, i, j, data);
		if (!data->envval)
			return (-42);
	}
	return (j);
}

int	ft_joindollar(t_lst *ptr, int i, t_mini *data)
{
	char	*tmp;
	char	*to_free;
	int		j;

	j = 1;
	tmp = ptr->str;
	ptr->str = ft_strndup2(tmp, i);
	if (!ptr->str)
		return (-42);
	to_free = ptr->str;
	j = ft_joindollar_else(tmp, data, i, j);
	if (j == -42)
		return (-42);
	ptr->str = ft_strjoinneg(to_free, data->envval);
	if (!ptr->str)
		return (-42);
	free(to_free);
	to_free = ft_strndup2(tmp + i + j, ft_strlen(tmp + i + j));
	if (!ptr->str)
		return (-42);
	return (return_dollar(to_free, tmp, data->envval, ptr));
}
