/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:02:30 by admaupie          #+#    #+#             */
/*   Updated: 2022/07/27 14:28:52 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "parse.h"
//
//int	ft_verif(t_lst *lst)
//{
//	t_lst	*tmp;
//	int		i;
//
//	tmp = lst->next;
//	while (tmp)
//	{
//		if (tmp->token != 0)
//		{
//			if (tmp->token == 1 && tmp->next && tmp->next->token != 1)
//				i++;
//			else if (tmp->token > 1 && tmp->next && tmp->next->token == 0)
//				i++;
//			else
//				return (0);
//		}
//		tmp = tmp->next;
//	}
//	(void)i;
//	return (1);
//}
//
//int	last_redirect(t_lst *lst)
//{
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
//		return (1);
//}
