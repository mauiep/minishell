/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:29:06 by admaupie          #+#    #+#             */
/*   Updated: 2022/10/24 15:47:43 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	get_next_word(char *buffer, t_lst *new)
{
	int		i;
	int		c;
	char	*tmp;

	i = 0;
	c = ' ';
	tmp = buffer;
	while (*tmp && tmp[i] == ' ')
		tmp++;
	while (tmp[i] && (c != ' ' || (!is_sep(tmp[i]) && tmp[i] != ' ')))
	{
		if (c == ' ' && (tmp[i] == SIMPLE_QUOTE || tmp[i] == 34))
			c = tmp[i];
		else if (c != ' ' && tmp[i] == c)
			c = ' ';
		i++;
	}
	if (c != ' ')
		return (-2);
	new->str = ft_strndup(tmp, i);
	if (!new->str)
		return (-1);
	return (1);
}

int	push_next_word(t_lst *lst, char *buffer)
{
	t_lst	*new;
	int		ret;
	int		i;

	i = 0;
	while (buffer[i] == ' ')
		i++;
	new = ft_lstnew();
	if (!new)
		return (-1);
	ret = get_next_word(buffer, new);
	if (ret < 0)
		return (ret);
	push_lst(new, lst);
	ret = recover_args(new, buffer + i + ft_strlen(new->str));
	if (ret < 0)
		return (ret);
	return (i + ft_strlen(new->str) + ret);
}

int	push_word(t_lst *lst, char *buffer)
{
	t_lst	*new;
	int		ret;

	new = ft_lstnew();
	if (!new)
		return (-1);
	ret = get_word(buffer, new);
	if (ret < 0)
		return (ret);
	push_lst(new, lst);
	return (ft_strlen(new->str));
}

int	push_sep(t_lst *lst, char *buffer)
{
	int		i;
	t_lst	*new;
	int		token;

	i = 0;
	new = ft_lstnew();
	if (!new)
		return (-1);
	while (is_sep(buffer[i]))
		i++;
	new->str = ft_strndup(buffer, i);
	if (!new->str)
		return (-1);
	token = which_redirect(new->str);
	if (token == -1)
		return (-3);
	new->token = token;
	push_lst(new, lst);
	if (new->token % 2 == 0)
		return (push_next_word(lst, buffer + i) + i);
	return (i);
}
