/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 12:37:50 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/16 03:39:18 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sub_split(t_token *token, t_index *subindex, int i_tok, int i_subtok)
{
	int		i_dup;
	int		len;
	char	*dup;

	len = (subindex->end_word[i_subtok] - subindex->begin_word[i_subtok]) + 2;
	dup = (char *)malloc(sizeof(char) * len);
	if (dup == NULL)
	{
		unload_indexer(subindex);
		perror("sub_split(): allocation error of dup string");
		return (NULL);
	}
	ft_memset((void *)dup, 0, len);
	i_dup = 0;
	while (i_dup < (len - 1))
	{
		dup[i_dup] = token[i_tok].elem[i_dup + subindex->begin_word[i_subtok]];
		i_dup++;
	}
	return (dup);
}

int	subtokenize_loop(t_token *token, t_index *subindex, int i_tok, int i_subtok)
{
	while (i_subtok < subindex->nb_word)
	{
		token[i_tok].subtoken[i_subtok].id_subtoken = i_subtok;
		token[i_tok].subtoken[i_subtok].father_token = i_tok;
		token[i_tok].subtoken[i_subtok].sub_elem = sub_split(token, subindex,
				i_tok, i_subtok);
		if (token[i_tok].subtoken[i_subtok].sub_elem == NULL)
		{
			perror("subtokenize_loop(): error getting sub string");
			return (-1);
		}
		i_subtok++;
	}
	token[i_tok].nb_subtoken = i_subtok;
	return (0);
}

int	subtokenize(t_token *token, int i_tok)
{
	t_index	*subindex;
	int		i_subtok;

	i_subtok = 0;
	subindex = subindexing(token, i_tok);
	if (subindex == NULL)
		return (-1);
	token[i_tok].subtoken = (t_subtoken *)malloc(
			sizeof(t_subtoken) * (subindex->nb_word + 2));
	if (token[i_tok].subtoken == NULL)
	{
		perror("subtokenize(): error allocating subtoken to token");
		return (-1);
	}
	ft_memset((void *)token[i_tok].subtoken, 0,
		sizeof(t_subtoken) * (subindex->nb_word + 2));
	if (subtokenize_loop(token, subindex, i_tok, i_subtok) == -1)
	{
		perror("subtokenize(): error while loop");
		return (-1);
	}
	unload_indexer(subindex);
	return (0);
}
