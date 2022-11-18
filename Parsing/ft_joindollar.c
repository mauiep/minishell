/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joindollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:21:18 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/18 15:51:36 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static int	ft_init_joindollard(t_joindollard *join_dol, t_lst *ptr,
	int i, t_mini *data)
{
	join_dol->j = 1;
	join_dol->tmp = ptr->str;
	join_dol->to_free = ft_strndup2(join_dol->tmp, i);
	if (!join_dol->to_free)
		return (-42);
	join_dol->dollard = ft_strndup2(join_dol->tmp + i + 1, join_dol->j - 1);
	if (!join_dol->dollard)
		return (-42);
	join_dol->envval = ft_get_env_var(join_dol->dollard, data);
	if (!join_dol->envval)
		join_dol->envval = "";
	join_dol->ret = ft_strlen(join_dol->envval);
	join_dol->new = ft_strjoinneg(join_dol->to_free, join_dol->envval);
	if (!join_dol->new)
		return (-42);
	return (1);
}*/

/*

	ft_joindollar sert a remplacer dans la string ptr->str un $ARG par
	sa valeur recuperee dans l'env, ou une string vide si la variable
	n'est pas dans l'env

	Args : 	ptr, le maillon de la liste a traiter
			i, index du $ dans la string
			darr, la copie de l'environnement
	Return : la taille de la string de l'env - 1 ou -42 si malloc error

*/
/*
int	ft_joindollar(t_lst *ptr, int i, t_mini *data)
{
	t_joindollard	join_dol;
	int				init;

	init = ft_init_joindollard(&join_dol, ptr, i, data);
	if (init < 0)
		return (-42);
	free(join_dol.to_free);//						free la valeur du debut
	join_dol.to_free = join_dol.new;//							on pointe to_free sur new
	join_dol.envval = ft_strndup2(join_dol.tmp + i + join_dol.j,
			ft_strlen(join_dol.tmp + i + join_dol.j));
	if (!join_dol.envval)
		return (-42);
	join_dol.new = ft_strjoin2(join_dol.new, join_dol.envval);//	new est un join 
	if (!join_dol.new)
		return (-42);
	ptr->str = join_dol.new;
	ft_quadrafree(join_dol.tmp, join_dol.dollard, join_dol.envval, NULL);
	return (join_dol.ret - 1);
}*/

int	end_dollar(char c)
{
	if (c && c != '\t' && c != 39 && c != ' ' && c != 34 && c != '$'
		&& c > 0)
		return (0);
	return (1);
}

int	ft_joindollar(t_lst *ptr, int i, t_mini *data)
{
	char	*tmp;
	char	*to_free;
	char	*envval;
	char	*dollar;
	char	*new;
	int		j;
	int		ret;

	j = 1;
	tmp = ptr->str;//					tmp est le pointeur vers le premier ptr->str
	to_free = ft_strndup2(tmp, i);//			to free est un strndup de tmp jusqu'au dollar
	if (!to_free)
		return (-42);
	while (end_dollar(tmp[i + j]) == 0)
		j++;
	dollar = ft_strndup2(tmp + i + 1, j - 1);//		dollar  est un strdup de la fin de tmp 
	if (!dollar)
		return (-42);
	envval = ft_get_env_var(dollar, data);//	envval est la valeur correspondant a dollar dans le envp
	if (!envval)
		envval = "";
	ret = ft_strlen(envval);
	new = ft_strjoinneg(to_free, envval);//			new est un join du to_free et du envval
	if (!new)
		return (-42);
	free(to_free);//						free la valeur du debut
	to_free = new;//							on pointe to_free sur new
	envval = ft_strndup2(tmp + i + j, ft_strlen(tmp + i + j));
	if (!envval)
		return (-42);
	new = ft_strjoin2(new, envval);//	new est un join 
	if (!new)
		return (-42);
	ptr->str = new;
	ft_quadrafree(tmp, dollar, envval, NULL);
	return (ret - 1);
}

void	ft_quadrafree(void *s1, void *s2, void *s3, void *s4)
{
	free(s1);
	free(s2);
	free(s3);
	free(s4);
}

