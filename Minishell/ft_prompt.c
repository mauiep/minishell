/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:09:26 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/22 15:34:45 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_free(t_mini *data)
{
	if (data->prompt)
		free(data->prompt);
	if (data->line)
		free(data->line);
}

char	*ft_prompt(t_mini *data)
{
	char	*tmp;
	char	*buffer;

	ft_check_free(data);
	buffer = getcwd(NULL, 0);
	if (!buffer)
	{
		data->prompt = ft_strjoin(GREEN, ft_get_env_var("PWD", data));
		tmp = ft_strdup(data->prompt);
		free(data->prompt);
		data->prompt = ft_strjoin(tmp, "$> ");
		free(tmp);
		tmp = ft_strdup(data->prompt);
		free(data->prompt);
		data->prompt = ft_strjoin(tmp, RESET);
		free(tmp);
		return (data->prompt);
	}
	data->prompt = ft_strjoin(GREEN, buffer);
	free(buffer);
	tmp = ft_strdup(data->prompt);
	free(data->prompt);
	data->prompt = ft_strjoin(tmp, "$> ");
	free(tmp);
	tmp = ft_strdup(data->prompt);
	free(data->prompt);
	data->prompt = ft_strjoin(tmp, RESET);
	free(tmp);
	data->prompt_var++;
	return (data->prompt);
}