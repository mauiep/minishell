/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_meta_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 12:41:39 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/16 03:36:45 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	which_meta_char(t_token *token, int i, int i_str)
{
	if (token[i].elem[i_str] == '<' && token[i].elem[i_str + 1] != '<')
		return (1);
	else if (token[i].elem[i_str] == '>' && token[i].elem[i_str + 1] != '>')
		return (2);
	else if (token[i].elem[i_str] == '|')
		return (3);
	else if (token[i].elem[i_str] == '<' && token[i].elem[i_str + 1] == '<')
		return (4);
	else if (token[i].elem[i_str] == '>' && token[i].elem[i_str + 1] == '>')
		return (5);
	else
		return (0);
}

int	seek_and_count_meta_char(t_token *token, int i)
{
	int	i_str;
	int	meta_char_count;
	int	double_arrow;

	i_str = 0;
	meta_char_count = 0;
	double_arrow = 0;
	while (token[i].elem[i_str])
	{
		if (which_meta_char(token, i, i_str) == 4
			|| which_meta_char(token, i, i_str) == 5)
		{
			meta_char_count++;
			double_arrow = 1;
		}
		else if (double_arrow == 0
			&& which_meta_char(token, i, i_str) != 0)
			meta_char_count++;
		i_str++;
	}
	printf("seek_and_count_meta_char(): %d metachar found\n", meta_char_count);
	return (meta_char_count);
}

/*
 *
		DEBUG a supprimer/mettre en commentaire norme avant le rendu
void	display_which_meta(int ret)
{
	if (ret == 1)
		printf("seek_meta: ret value is %d -> redirection input found\n", ret);
	else if (ret == 2)
		printf("seek_meta: ret value is %d -> redirection output found\n", ret);
	else if (ret == 3)
		printf("seek_meta: ret value is %d -> pipe found\n", ret);
	else if (ret == 4)
		printf("seek_meta: ret value is %d -> here_doc meta found\n", ret);
	else if (ret == 5)
		printf("seek_meta: ret value is %d -> append output found\n", ret);
}
 *
 */

int	seek_meta_char(t_token *token, int i)
{
	int	i_str;
	int	ret;

	i_str = 0;
	ret = 0;
	while (token[i].elem[i_str])
	{
		ret = which_meta_char(token, i, i_str);
		if (ret == 4 || ret == 5)
			i_str = i_str + 2;
		if (ret != 0)
			return (ret);
		i_str++;
	}
	return (0);
}
