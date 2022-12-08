/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:29:06 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/28 12:22:14 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

	get_next_word va malloc une chaine de caracteres dans new->str et y inserer
	le prochain "mot", pouvant contenir des espaces a l'interieur de quotes
	
	Args : 	char *buffer, contenant le retour de readline;
			t_lst *new, le nouveau maillon a ajouter a la liste
	
	Return :	 1 si reussi
				-1 malloc error
				-2 missing quotes
				-3 syntax error
				-4 parse error
*/

int	get_next_word(char *buffer, t_lst *new)
{
	int		i;
	int		c;
	char	*tmp;

	i = 0;
	c = ' ';
	tmp = buffer;
	while (*tmp && tmp[i] == ' ')
		tmp++;
	while (tmp[i] && (c != ' ' || (!is_sep(tmp[i]) && tmp[i] != ' ')))
	{
		if (tmp[i] == '\\' && ft_echap(tmp, i) == 0)
			return (-3);
		if (c == ' ' && (tmp[i] == 39 || tmp[i] == 34))
			c = tmp[i];
		else if (c != ' ' && tmp[i] == c)
			c = ' ';
		i++;
	}
	if (c != ' ')
		return (-2);
	new->str = ft_strndup2(tmp, i);
	if (!new->str)
		return (-1);
	return (1);
}

int	push_next_word(t_lst *lst, char *buffer)
{
	t_lst	*new;
	int		ret;
	int		i;

	i = 0;
	while (buffer[i] == ' ')
		i++;
	new = ft_lstnew();
	if (!new)
		return (-1);
	ret = get_next_word(buffer, new);
	if (ret < 0)
		return (ret);
	push_lst(new, lst);
	ret = recover_args(new, buffer + i + ft_strlen(new->str));
	if (ret < 0)
		return (ret);
	return (i + ft_strlen(new->str) + ret);
}

int	push_word(t_lst *lst, char *buffer)
{
	t_lst	*new;
	int		ret;

	new = ft_lstnew();
	if (!new)
		return (-1);
	ret = get_word(buffer, new);
	if (ret < 0)
		return (free_lst(new), ret);
	push_lst(new, lst);
	return (ft_strlen(new->str));
}

static int	push_cmd_lst(t_lst *lst)
{
	t_lst	*new;

	new = ft_lstnew();
	if (!new)
		return (0);
	push_lst(new, lst);
	return (1);
}

int	push_sep(t_lst *lst, char *buffer)
{
	int		i;
	t_lst	*new;
	int		token;

	i = 0;
	if (lst->prev && (lst->prev->str == NULL || lst->prev->token == 1))
		if (!push_cmd_lst(lst))
			return (-1);
	new = ft_lstnew();
	if (!new)
		return (-1);
	while (is_sep(buffer[i]))
		i++;
	new->str = ft_strndup2(buffer, i);
	if (!new->str)
		return (-1);
	token = which_redirect(new->str);
	if (token == -1)
		return (free_lst(new), -3);
	new->token = token;
	push_lst(new, lst);
	if (new->token % 2 == 0 || new->token == 5)
		return (push_next_word(lst, buffer + i) + i);
	return (i);
}
