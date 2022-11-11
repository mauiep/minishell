/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:54:29 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/11 15:10:12 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cleanfile(t_lst *lst)
{
	char	*to_free;

	//if (lst_remove_spaces(lst) < 0)
	//	return (-1);
	if (lst_remove_quotes(lst) < 0)
		return (-1);
	to_free = lst->str;
	lst->str = ft_strpos(lst->str);
	if (!lst->str)
		return (-1);
	free(to_free);
	return (1);
}
