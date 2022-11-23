/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joindollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:21:18 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/22 14:14:23 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_dollar(char c)
{
	if (c && c != '\t' && c != 39 && c != ' ' && c != 34 && c != '$'
		&& c > 0)
		return (0);
	return (1);
}

char	*dollarval(char *tmp, int i, int j, t_mini *data)
{
	char	*dollar;
	char	*envval;

	dollar = ft_strndup2(tmp + i + 1, j - 1);//		dollar  est un strdup contenant la string suivant le '$' exemple: PWD 
	if (!dollar)
		return (NULL);
	envval = ft_get_env_var(dollar, data);//	envval est la valeur correspondant a dollar dans le envp 
	if (!envval)
		envval = ft_strndup2("", 0);
	free(dollar);
	return (envval);
}

int	return_dollar(char *str, char *tmp, char *envval, t_lst *ptr)
{
	int		ret;
	char	*to_free;

	to_free = ptr->str;
	ptr->str = ft_strjoin2(ptr->str, str);//	new est un join entre le new (debut + dollarval) et envval (apres le $)
	if (!ptr->str)
		return (-42);
	ret = ft_strlen(envval) - 1;
	ft_quadrafree(str, envval, tmp, to_free);
	return (ret);
}

int	ft_joindollar(t_lst *ptr, int i, t_mini *data)
{
	char	*tmp;
	char	*to_free;
	char	*envval;
	int		j;

	j = 1;
	tmp = ptr->str;//					tmp est le pointeur vers le premier ptr->str
	ptr->str = ft_strndup2(tmp, i);//			la on a un strndup de tmp jusqu'au dollar
	if (!ptr->str)
		return (-42);
	to_free = ptr->str;//						TO_FREE = 'echo '
	while (end_dollar(tmp[i + j]) == 0)
		j++;
	envval = dollarval(tmp, i, j, data);
	if (!envval)
		return (-42);
	ptr->str = ft_strjoinneg(to_free, envval);//			new est un join du to_free et du envval
	if (!ptr->str)
		return (-42);
	free(to_free);//						free la valeur du debut
	to_free = ft_strndup2(tmp + i + j, ft_strlen(tmp + i + j));//	ici on dup la fin de la chaine (apres le $)
	if (!ptr->str)
		return (-42);
	return (return_dollar(to_free, tmp, envval, ptr));
}

void	ft_quadrafree(void *s1, void *s2, void *s3, void *s4)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	if (s4)
		free(s4);
}

