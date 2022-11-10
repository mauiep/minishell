/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joindollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:21:18 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/08 15:51:28 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_joindollar(t_lst *ptr, int i, t_dynarray *darr)
{
	char	*tmp;
	char	*to_free;
	char	*envval;
	char	*dollar;
	char	*new;
	int		j;
	int		ret;

	j = 1;
	tmp = ptr->str;
	to_free = ft_strndup(tmp, i);
	if (!to_free)
		return (-42);
	while (tmp[i + j] && tmp[i + j] != '\t' && tmp[i + j] != 39
		&& tmp[i + j] != ' ' && tmp[i + j] != 34 && tmp[i + j] != '$')
		j++;
	dollar = ft_strndup(tmp + i + 1, j - 1);
	if (!dollar)
		return (-42);
	envval = ft_getenvval(dollar, darr, 0, 0);
	if (!envval)
		envval = "";
	ret = ft_strlen(envval);
	new = ft_strjoinneg(to_free, envval);//ft_strjoinneg // mettre envval en neg dans new
	if (!new)
		return (-42);
	free(to_free);
	to_free = new;
	envval = ft_strndup(tmp + i + j, ft_strlen(tmp + i + j));
	if (!envval)
		return (-42);
	new = ft_strjoin(new, envval);
	if (!new)
		return (-42);
	free(to_free);
	free(dollar);
	free(envval);
	ptr->str = new;
	printf("apres join ptr->str=%s\n", ptr->str);
	free(tmp);
	return (ret - 1);
}

int	ft_strjoindollar(t_lst *l, char *var, int k, int dollar)
{
	int		i;
	char	*tmp;
	char	*new;

	i = ft_strlen(var);
	tmp = l->str;
	printf("strjoining $ :\n* tmp/l->str = %s\n* var = %s\n* i=%d\n* dollar=%d\n**************\n", tmp, var, i, dollar);
	new = malloc(sizeof(char) * (ft_strlen(tmp) + i + 1 - dollar));
	if (!new)
		return(-1);
	i = -1;
	while (++i >= 0 && tmp[i] && i < k)
		new[i] = tmp[i];
	i--;
	while (++i && var[i - k])
		new[i] = var[i - k];
	i--;
	k--;
	while (++i && ++k && tmp[k + dollar] != '\0')
		new[i] = tmp[k + dollar];
	new[i] = '\0';
	free(tmp);
	tmp = NULL;
	l->str = new;
	return (1);
}

int	ft_replacedollar(t_lst *l, int k, int c, t_dynarray *darr)
{
	int		i;
	int		dollar;
	char	*var;

	(void)c;
	var = NULL;
	dollar = 0;
	k++;
	while (l->str[k + dollar] && l->str[k + dollar] != '\t'
		&& l->str[k + dollar] != 39 && l->str[k + dollar] != ' '
		&& l->str[k + dollar] != 34)
		dollar++;
	if (dollar && dollar++)
		var = ft_getenvval(l->str + k, darr, 0, 0);
	else if (l->str[k] == 34 || l->str[k] == SIMPLE_QUOTE)
	{
		var = "$";
		dollar++;
	}
	i = ft_strlen(var);
	if (!i)
		var = "";
	ft_strjoindollar(l, var, k - 1, dollar);
	return (i - 1);
}
