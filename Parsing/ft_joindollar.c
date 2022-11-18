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

char	*dollarval(char *tmp, int i, int j, t_mini *data)
{
	char	*dollar;
	char	*envval;

	dollar = ft_strndup2(tmp + i + 1, j - 1);//		dollar  est un strdup contenant la string suivant le '$' exemple: PWD 
	if (!dollar)
		return (NULL);
	envval = ft_get_env_var(dollar, data);//	envval est la valeur correspondant a dollar dans le envp 
	if (!envval)
		envval = "";
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

