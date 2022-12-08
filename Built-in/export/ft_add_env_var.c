/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:35:57 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/08 01:54:50 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- L'argument de export
**	- Le pointeur sur structure data
**
**	========================================
**	
**	Cette fonction sert a verifier si
** Le nom de variable que l'on veut export existe deja
** Et fonctionne ainsi :
**	
**	- Si il y a un "=" dans la ligne de declaration de la variable d'environement
**	- On affiche la variable d'environement;
**	
**	========================================
**	
**	- Exemple : export FOO=145
**	- On garde en memoire le nom jusqu'au "="
**	- On compare grace a strncmp avec le env
**	- Si le nom existe deja on return (l'index de la variable dans env)
**	- Sinon on return (0);
*/

static int	ft_does_export_name_already_exists(char *arg, t_mini *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arg[i] && !(arg[i] == '='))
		i++;
	while (data->env_tab[j])
	{
		if (!ft_strncmp(arg, data->env_tab[j], i))
			return (j);
		j++;
	}
	return (0);
}

/*
**	Cette fonction prend en parametre :
**	
**	- L'argument de export
**	- Le pointeur sur structure data
**
**	========================================
**	
**	Cette fonction sert faire fonctionner export si l'arg ne comporte pas de "="
** Exemple : export FOO
** Et fonctionne ainsi :
**	
**	- On verifie si le nom de variable existe deja,
**	 Si oui on quitte la fonction
**	- On creer une nouvelle copie de env avec une place en plus
**	 Pour ajouter la variable d'environement
**	- On ajoute la variable d'environement a env
*/

static void	ft_add_env_var_with_no_equal(char *arg, t_mini *data)
{
	int		i;

	if (ft_does_export_name_already_exists(arg, data))
		return ;
	i = 0;
	data->env_tab = ft_create_temp_env(data, ft_env_len(data));
	while (data->env_tab[i])
		i++;
	data->env_tab[i] = ft_strdup(arg);
	data->env_tab = ft_if_malloc_issue(data->env_tab, i);
	if (!data->env_tab)
		return ;
}

/*
**	Cette fonction prend en parametre :
**	
**	- L'argument de export
**	- Le pointeur sur structure data
**
**	========================================
**	
**	Cette fonction sert faire fonctionner export si l'arg comporte un "="
** Exemple : export FOO=142
** Et fonctionne ainsi :
**	
**	- On verifie si le nom de variable existe deja
**	
**	========================================
**	
**	- Si le nom de variable existe deja 
**	- On modifie la valeur de la variable deja presente dans env
**	
**	========================================
**	
**	- Si le nom de variable n'existe pas deja
**	- On creer une nouvelle copie de env avec une place en plus
**	- On copie l'arg de export dans env
*/

static void	ft_add_env_var_with_equal(char *arg, t_mini *data)
{
	int	i;
	int	pos;

	i = 0;
	pos = ft_does_export_name_already_exists(arg, data);
	if (pos)
	{
		free(data->env_tab[pos]);
		data->env_tab[pos] = ft_strdup(arg);
		data->env_tab = ft_if_malloc_issue(data->env_tab, pos);
		if (!data->env_tab)
			return ;
		return ;
	}
	data->env_tab = ft_create_temp_env(data, ft_env_len(data));
	i = 0;
	while (data->env_tab[i])
		i++;
	data->env_tab[i] = ft_strdup(arg);
	data->env_tab = ft_if_malloc_issue(data->env_tab, i);
	if (!data->env_tab)
		return ;
}

/*
**	Cette fonction prend en parametre :
**	
**	- L'argument de export
**
**	========================================
**	
**	Cette fonction sert a verifier si il y a un "=" dans l'arg de export
** Et fonctionne ainsi :
**	
**	- On parcours l'arg
**	- Si il y a un "="
**	- On return (1)
**	- Si il n'y a pas de "="
**	- On return (0)
*/

static int	ft_is_equal_in_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (-1);
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

/*
**	Cette fonction prend en parametre :
**	
**	- L'argument de export
**	- Le pointeur sur la structure data
**
**	========================================
**	
**	Cette fonction sert a ajouter une variable d'environement dans env
** Et fonctionne ainsi :

**	- Si il n'y a pas d'argument on return (-1)
**	- Si il y a un "=" dans l'argument on lance ft_add_env_var_with_equal()
**	- Si il n'y a pas de "=" dans l'argument
**	 On lance ft_add_env_var_with_no_equal()
*/

void	ft_add_env_var(char *arg, t_mini *data)
{
	if (ft_is_equal_in_arg(arg) == -1)
		return ;
	else if (ft_is_equal_in_arg(arg) == 1)
		ft_add_env_var_with_equal(arg, data);
	else if (ft_is_equal_in_arg(arg) == 0)
		ft_add_env_var_with_no_equal(arg, data);
}
