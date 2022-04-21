/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isolate_env_indexer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:37:19 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/16 03:33:51 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space_or_null_or_dquote(char c)
{
	if (c == 0 || c == 32 || c == '\"' || c == '$')
		return (1);
	else
		return (0);
}

void	env_indexing_loop_instructions(t_token *token,
		t_index *env_index, int i_tok)
{
	int		j;
	int		i_str;
	char	dollar;

	j = 0;
	i_str = 0;
	dollar = 0;
	while (token[i_tok].elem[i_str])
	{
		if (token[i_tok].elem[i_str] != '\"' && env_index->begin_word[j] == -1)
		{
			env_index->begin_word[j] = i_str;
			if (token[i_tok].elem[i_str] == '$')
				dollar = token[i_tok].elem[i_str];
		}
		if (dollar == 0 && env_index->begin_word[j] != -1
			&& token[i_tok].elem[i_str]
			&& token[i_tok].elem[i_str + 1] == '$'
			&& is_space_or_null_or_dquote(token[i_tok].elem[i_str + 2]) == 0)
		{
			env_index->end_word[j] = i_str;
			j++;
		}
		else if (dollar == '$' && env_index->begin_word[j] != -1
			&& is_space_or_null_or_dquote(token[i_tok].elem[i_str + 1]) == 1)
		{
			env_index->end_word[j] = i_str;
			dollar = 0;
			j++;
		}
		i_str++;
	}
	if (env_index->end_word[j] == -1)
		env_index->end_word[j] = i_str - 1;
	env_index->nb_word = j + 1;
}

t_index	*env_indexing(t_token *token, int i_tok)
{
	t_index	*env_index;

	env_index = init_indexer(token[i_tok].elem);
	if (env_index == NULL)
	{
		perror("env_indexing(): Error intializing envindex");
		return (NULL);
	}
	env_indexing_loop_instructions(token, env_index, i_tok);
	return (env_index);
}
