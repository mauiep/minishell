/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:11:19 by admaupie          #+#    #+#             */
/*   Updated: 2022/10/20 23:12:26 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

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

int	free_lst(t_lst *src)
{
	t_lst	*next;

	while (src->prev)
		src = src->prev;
	while (src)
	{
		next = src->next;
		if (src->str)
			free(src->str);
		src->str = NULL;
		free(src);
		src = next;
	}
	src = 0;
	next = 0;
	return (0);
}

void	push_lst(t_lst *new, t_lst *lst)
{
	t_lst	*tmp;

	tmp = lst;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	else
		lst = new;
	return ;
}

void	ft_printlst(t_lst *a)
{
	int		i;
	t_lst	*tmp;

	i = 0;
	tmp = a;
	while (tmp->prev != NULL)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->str == NULL)
			printf("maillon nul\n");
		if (tmp->str)
			printf("- %s\n", tmp->str);
		tmp = tmp->next;
		i++;
	}
	printf("%d\n", i);
}

int	lst_len(t_lst *lst)
{
	int		i;
	t_lst	*ptr;

	ptr = lst;
	while (ptr->prev != NULL)
		ptr = ptr->prev;
	i = 0;
	while (ptr && ptr->next && ++i)
		ptr = ptr->next;
	return (i);
}

t_lst	*ft_lstnew(void)
{
	t_lst	*new;

	new = malloc(sizeof(t_lst));
	if (!new)
		return (NULL);
	new->str = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->token = 0;
	return (new);
}
