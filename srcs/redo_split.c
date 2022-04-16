/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redo_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:15:54 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/13 12:36:04 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tab_init(int *tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		tab[i] = -1;
		i++;
	}
}

char	*stridup(char *str, t_index *index, t_split *split)
{
	int		i;
	int		len;
	char	*dup;

	i = 0;
	len = (index->end_word[split->j] - index->begin_word[split->j]) + 2;
	dup = (char *)malloc(sizeof(char) * len);
	if (dup == NULL)
	{
		free(index->end_word);
		free(index->begin_word);
		free(index);
		perror("stridup(): allocation error of dup string");
		return (NULL);
	}
	ft_memset((void *)dup, 0, len);
	while (i < (len - 1))
	{
		dup[i] = str[i + index->begin_word[split->j]];
		i++;
	}
	return (dup);
}

int	check_redo_split(t_split *split, t_index *index, int op)
{
	if (op == 0)
	{
		if (split->split == NULL)
		{
			free(index->end_word);
			free(index->begin_word);
			free(index);
			perror("redo_split(): error allocating 2d char array split->split");
			return (-1);
		}
	}
	else if (op == 1)
	{
		if (split->split[split->j] == NULL)
		{
			perror("redo_split(): error duping sub string");
			return (-1);
		}
	}
	return (0);
}

int	redo_split(char *str, t_split *split)
{
	t_index	*index;
	int		i;

	i = 0;
	index = indexing(str, split);
	if (index == NULL)
		return (-1);
	split->split = (char **)malloc(sizeof(char *) * (index->nb_word + 2));
	if (check_redo_split(split, index, 0) == -1)
		return (-1);
	while (i <= index->nb_word)
		split->split[i++] = NULL;
	while (index->begin_word[split->j] != -1)
	{
		split->split[split->j] = stridup(str, index, split);
		if (check_redo_split(split, index, 1) == -1)
			return (-1);
		split->j++;
	}
	split->nb_split = index->nb_word + 2;
	free(index->begin_word);
	free(index->end_word);
	free(index);
	return (0);
}
