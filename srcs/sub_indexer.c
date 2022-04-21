/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_indexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:37:19 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/16 03:37:41 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	subindexing_loop_instructions(t_token *token, t_index *subindex,
		int i_str, int i_tok)
{
	int	j;
	int	ret;
	int	stock_meta;

	j = 0;
	stock_meta = 0;
	while (token[i_tok].elem[i_str])
	{
		ret = which_meta_char(token, i_tok, i_str);
		if (subindex->begin_word[j] == -1)
		{
			subindex->begin_word[j] = i_str;
			if (stock_meta == 0 && ret != 0)
				stock_meta = ret;
		}
		if (subindex->begin_word[j] != -1
			&& which_meta_char(token, i_tok, i_str + 1) != stock_meta)
		{
			if (ret == 4 || ret == 5)
				subindex->end_word[j] = i_str + 1;
			else
				subindex->end_word[j] = i_str;
			stock_meta = 0;
			j++;
		}
		if (ret == 4 || ret == 5)
			i_str++;
		i_str++;
	}
	if (subindex->end_word[j] == -1)
		subindex->end_word[j] = i_str;
	subindex->nb_word = j + 1;
}

t_index	*subindexing(t_token *token, int i_tok)
{
	int		i_str;
	t_index	*subindex;

	i_str = 0;
	subindex = init_indexer(token[i_tok].elem);
	if (subindex == NULL)
	{
		perror("subindexing(): Error intializing subindex");
		return (NULL);
	}
	i_str = skip_space(token[i_tok].elem);
	subindexing_loop_instructions(token, subindex, i_str, i_tok);
	return (subindex);
}
