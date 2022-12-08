/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_check_if_arg_is_dash.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:10:47 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/08 03:04:00 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- Les arguments de cd
**	- Le pointeur sur structure data
**	
**	========================================
**	
**	Cette fonction sert a gerer le cas ou l'argument est "-"
**	Et fonctionne ainsi :
**	
**	- Si l'argument est "-"
**	- On associe la variable OLDPWD a PWD
**	- On lance ft_error_manager() qui va s'occuper de changer de directory
**	- On ecrit le path actuel sur la sortie standard
**	
**	========================================
**	
**	- Si l'argument n'est pas "-"
**	- On converti l'argument en path comprehensible pour chdir()
**	- Puis on return ft_cd_error_manager qui s'occupe de changer de directory
*/

int	ft_cd_check_if_arg_is_dash(char **args, t_mini *data)
{
	char	*pwd;

	pwd = NULL;
	if (!ft_strcmp(args[1], "-"))
	{
		pwd = ft_get_env_var("OLDPWD", data);
		if (pwd)
		{
			ft_cd_error_manager(pwd, data);
			free(pwd);
		}
		pwd = ft_get_env_var("PWD", data);
		if (pwd)
		{
			ft_putendl_fd(pwd, 1);
			free(pwd);
		}
		return (1);
	}
	data->converted_path = ft_convert_arg_to_path(args, data);
	return (ft_cd_error_manager(data->converted_path, data));
}
