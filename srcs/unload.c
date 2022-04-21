/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unload.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:26:23 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/16 02:32:20 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unload(t_split *split, t_token *token)
{
	int	i;
	int	j;

	i = 0;
	while (split->split[i] != NULL)
		free(split->split[i++]);
	free(split->split);
	free(split);
	i = 0;
	while (token[i].elem != NULL)
	{
		j = 0;
		while (j < token[i].nb_subtoken)
		{
			if (token[i].is_word == 1)
				free(token[i].subtoken[j++].sub_elem);
			else
				free(token[i].dq[j++].dq_elem);
		}
		if (token[i].is_word == 1)
			free(token[i].subtoken);
		else
			free(token[i].dq);
		i++;
	}
	free(token);
}

void	unload_indexer(t_index *index)
{
	free(index->end_word);
	free(index->begin_word);
	free(index);
}
