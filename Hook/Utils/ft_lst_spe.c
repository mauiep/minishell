/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_spe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:31:58 by admaupie          #+#    #+#             */
/*   Updated: 2022/10/26 18:36:18 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	push_first_lst(t_lst *new, t_lst *lst)
{
	t_lst	*tmp;
	t_lst	*first;

	first = lst;
	while (first->prev != NULL)
		first = first->prev;
	tmp = first->next;
	new->prev = first;
	first->next = new;
	tmp->prev = new;
	new->next = tmp;
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
