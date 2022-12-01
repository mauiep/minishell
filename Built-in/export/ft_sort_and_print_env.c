/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_and_print_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:45:53 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/25 12:23:38 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- L'env temporaire pour trier dans l'ordre ascii
**	- L'index de la variable que l'on veut swap dans env
**
**	========================================
**	
**	Cette fonction sert a echanger la variable d'environement
** Avec celle d'apres
**	Et fonctionne ainsi :
**	
**	- On echange la variable d'environement avec celle d'apres
*/

static void	ft_swap(char **temp_env, int j)
{
	char	*tmp;

	tmp = temp_env[j];
	temp_env[j] = temp_env[j + 1];
	temp_env[j + 1] = tmp;
}

/*
**	Cette fonction prend en parametre :
**	
**	- L'env temporaire pour trier dans l'ordre ascii
**	- L'index de la variable que l'on veut swap dans env
**
**	========================================
**	
**	Cette fonction sert a afficher l'env
** Avec chaque variable precedee de "declare -x"
**	Et fonctionne ainsi :
**	
**	- Tant que on est pas a la fin de env
**	- On ecrit "declare -x" suivi d'un espace
**	- On ecrit le nom de la variable
**	- On ecrit "=""
**	- On ecrit la valeur de la variable
**	- On ecrit """ suivi d'un saut a la ligne
**	- Exemple : FOO=456
**	- declare -x FOO="456"
*/

static void	ft_print_env(char **temp_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (temp_env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		while (temp_env[i][j] && !(temp_env[i][j] == '='))
		{
			write(1, &temp_env[i][j], 1);
			j++;
		}
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(temp_env[i] + (j + 1), 1);
		ft_putstr_fd("\"\n", 1);
		j = 0;
		i++;
	}
	ft_free(temp_env);
}

/*
**	Cette fonction prend en parametre :
**	
**	- Le pointeur sur structure data
**
**	========================================
**	
**	Cette fonction sert a trier l'env par ordre ascii et a l'afficher ensuite
**	Et fonctionne ainsi :
**	
**	- On creer une env temporaire pour trier dedans
**	- Si la valeur ascii de la variable actuelle est plus grande que la suivante
**	- On ft_swap() les deux
**	- On print l'env grace a ft_print_env()
*/

void	ft_sort_and_print_env(t_mini *data)
{
	char	**temp_env;
	int		i;
	int		j;

	temp_env = ft_create_temp_env(data, ft_env_len(data));
	if (!temp_env)
	{
		ft_free(temp_env);
		return ;
	}
	i = 0;
	j = 0;
	while (temp_env[i])
	{
		while (temp_env[j + 1])
		{
			if (ft_strcmp(temp_env[j], temp_env[j + 1]) > 0)
				ft_swap(temp_env, j);
			j++;
		}
		i++;
		j = 0;
	}
	ft_print_env(temp_env);
}
