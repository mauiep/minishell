/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:02:30 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/11 14:59:14 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_verif(t_lst *lst)
{
	t_lst	*tmp;
	int		i;

	i = 0;
	tmp = lst->next;
	while (tmp)
	{
		if (tmp->token != 0)
		{
			if (tmp->token == 1 && tmp->next && tmp->next->token != 1)
				i++;
			else if (tmp->token > 1 && tmp->next && tmp->next->token == 0)
				i++;
			else
				return (0);
		}
		tmp = tmp->next;
	}
	(void)i;
	return (1);
}

int	edit_maillon(char *buffer, int i, t_lst *tmp)
{
	char	*to_free;
	char	*str;
	int		ret;

	to_free = tmp->str;
	str = strndup(buffer + i, spe_lenword(buffer + i));
	if (!str)
		return (-1);
	ret = strlen(str);
	tmp->str = ft_strjoin2(tmp->str, str);
	if (!(tmp->str))
		return (-1);
	free(to_free);
	to_free = NULL;
	free(str);
	str = NULL;
	return (i + ret);
}

int	recover_args(t_lst *last, char *buffer)
{
	int		i;
	t_lst	*tmp;

	i = 0;
	while (buffer[i] && buffer[i] == ' ')
		i++;
	if (!buffer[i] || is_sep(buffer[i]))
		return (0);
	tmp = pick_the_lst(last->prev->prev);
	if (!tmp)
	{
		tmp = ft_lstnew();
		if (!tmp)
			return (0);
		if (get_word(buffer + i, tmp) == -1)
			return (0);
		push_first_lst(tmp, first_lst(last));
		return (i + ft_strlen(tmp->str));
	}
	else
		return (edit_maillon(buffer, i, tmp));
}

int	last_redirect(t_lst *lst)
{
	(void)lst;
//	t_lst	*tmp;
//
//	tmp = lst;
//	if (lst_len(tmp > 2))
//	{
//		if (tmp->next->next->token != 2 && tmp->next->next->token != 4)
//			return (1);
//		else
//			return (0);
//	}
//	else
		return (1);
}
