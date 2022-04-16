/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublequote_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 12:37:50 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/16 03:31:45 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dq_split(t_token *token, t_index *dq_index, int i_tok, int i_dq)
{
	int		i_dup;
	int		len;
	char	*dup;

	len = (dq_index->end_word[i_dq] - dq_index->begin_word[i_dq]) + 2;
	dup = (char *)malloc(sizeof(char) * len);
	if (dup == NULL)
	{
		unload_indexer(dq_index);
		perror("sub_split(): allocation error of dup string");
		return (NULL);
	}
	ft_memset((void *)dup, 0, len);
	i_dup = 0;
	while (token[i_tok].elem[i_dup + dq_index->begin_word[i_dq]]
		&& i_dup < (len - 1))
	{
		dup[i_dup] = token[i_tok].elem[i_dup + dq_index->begin_word[i_dq]];
		i_dup++;
	}
	return (dup);
}

int	dq_tokenize_loop(t_token *token, t_index *dq_index, int i_tok, int i_dq)
{
	while (i_dq < dq_index->nb_word - 1)
	{
		token[i_tok].dq[i_dq].id_dq = i_dq;
		token[i_tok].dq[i_dq].dq_elem = dq_split(token, dq_index, i_tok, i_dq);
		if (token[i_tok].dq[i_dq].dq_elem == NULL)
		{
			perror("dqtokenize_loop(): error getting dq string");
			return (-1);
		}
		i_dq++;
	}
	token[i_tok].nb_subtoken = i_dq;
	return (0);
}

/*
 *
void	debug_indexing(t_token *token, int i_tok, t_index *dq_index)
{
	int	i;

	i = 0;
	while (i < dq_index->nb_word - 1)
	{
		printf("dq_index->beginword[%d] = %d->%c\n", i, dq_index->begin_word[i],
		token[i_tok].elem[dq_index->begin_word[i]]);
		printf("dq_index->endword[%d] = %d->%c\n", i, dq_index->end_word[i],
		token[i_tok].elem[dq_index->end_word[i]]);
		i++;
	}
}
 *
 */

int	double_quote_tokenize(t_token *token, int i_tok)
{
	t_index	*dq_index;
	int		i_dq;

	i_dq = 0;
	dq_index = env_indexing(token, i_tok);
	if (dq_index == NULL)
		return (-1);
	token[i_tok].dq = (t_dq *)malloc(sizeof(t_dq) * (dq_index->nb_word + 2));
	if (token[i_tok].dq == NULL)
	{
		perror("dq_tokenize(): error allocating dq_token to token");
		return (-1);
	}
	ft_memset((void *)token[i_tok].dq, 0, sizeof(t_dq)
		* (dq_index->nb_word + 2));
	if (dq_tokenize_loop(token, dq_index, i_tok, i_dq) == -1)
	{
		perror("dq_tokenize(): error while loop");
		return (-1);
	}
	unload_indexer(dq_index);
	return (0);
}
