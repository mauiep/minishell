/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 03:33:01 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/16 02:31:10 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_token(t_split *split)
{
	t_token	*token;
	int		i;

	token = (t_token *)malloc(sizeof(t_token) * split->nb_split);
	if (token == NULL)
		return (NULL);
	ft_memset((void *)token, 0, sizeof(t_token) * split->nb_split);
	i = 0;
	while (i < split->nb_split)
	{
		token[i].elem = split->split[i];
		i++;
	}
	return (token);
}
