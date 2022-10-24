/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:02:30 by admaupie          #+#    #+#             */
/*   Updated: 2022/10/24 22:00:46 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_lst	*pick_the_lst(t_lst *last)
{
	t_lst	*tmp;

	tmp = last;
	if (!tmp)
		return (NULL);
	while (tmp->str != NULL && tmp->prev->str != NULL && tmp->prev->token % 2 == 0)
		tmp = tmp->prev->prev;
	if (tmp->str != NULL)
		return (tmp);
	else
		return (NULL);
}

t_lst	*first_lst(t_lst *lst)
{
	t_lst	*tmp;

	tmp = lst;
	while (tmp->prev != NULL)
		tmp = tmp->prev;
	return (tmp);
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
	tmp->str = ft_strjoin(tmp->str, str);
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
