/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:15:11 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/08 17:49:35 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_init_index_op2(t_index *index)
{
	if (index->end_word == NULL)
	{
		free(index->begin_word);
		index->begin_word = NULL;
		free(index);
		index = NULL;
		perror("check_init_index(): Error allocating end_word");
		return (-1);
	}
	else
		return (0);
}

int	check_init_index(t_index *index, int op)
{
	if (op == 0)
	{
		if (index == NULL)
		{
			perror("check_init_index() - op 0: Error allocating index struct");
			return (-1);
		}
	}
	else if (op == 1)
	{
		if (index->begin_word == NULL)
		{
			free(index);
			index = NULL;
			perror("check_init_index() - op 1: Error allocating begin_word");
			return (-1);
		}
	}
	else if (op == 2)
		return (check_init_index_op2(index));
	return (0);
}

t_index	*init_indexer(char *str)
{
	t_index	*index;

	index = (t_index *)malloc(sizeof(t_index));
	if (check_init_index(index, 0) == -1)
		return (NULL);
	ft_memset((void *)index, 0, sizeof(index));
	index->begin_word = (int *)malloc(sizeof(int) * (ft_strlen(str) + 1));
	if (check_init_index(index, 1) == -1)
		return (NULL);
	index->end_word = (int *)malloc(sizeof(int) * (ft_strlen(str) + 1));
	if (check_init_index(index, 2) == -1)
		return (NULL);
	tab_init(index->begin_word, ft_strlen(str) + 1);
	tab_init(index->end_word, ft_strlen(str) + 1);
	return (index);
}

void	indexing_loop_instruction(char *str, t_split *split, t_index *index,
		int i)
{
	int	j;

	j = 0;
	while (str[i] != 0)
	{
		to_quote_or_not_to_quote(str, i, split);
		if (str[i] != 32 && index->begin_word[j] == -1)
			index->begin_word[j] = i;
		if (str[i] == 32 && index->begin_word[j] != -1 && split->quote == 0)
		{
			if (i > 0)
				index->end_word[j] = i - 1;
			else
				index->end_word[j] = i;
			j++;
		}
		i++;
	}
	if (index->end_word[j] == -1)
		index->end_word[j] = i - 1;
	index->nb_word = j + 1;
}

t_index	*indexing(char *str, t_split *split)
{
	int		i;
	t_index	*index;

	i = 0;
	index = init_indexer(str);
	if (index == NULL)
	{
		perror("indexing(): Error initializing index");
		return (NULL);
	}
	i = skip_space(str);
	indexing_loop_instruction(str, split, index, i);
	return (index);
}
