/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:57:13 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/08 02:23:23 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long	ft_exit_atoi(char *str)
{
	long long		sign;
	int				cpt;
	long long		atoi_var;

	sign = 1;
	atoi_var = 0;
	cpt = ft_isspace(str);
	if (str[cpt] == '-' || str[cpt] == '+')
		if (str[cpt++] == '-')
			sign *= -1;
	while (str[cpt] >= '0' && str[cpt] <= '9')
	{
		atoi_var *= 10;
		atoi_var += str[cpt] - '0';
		cpt++;
	}
	return (atoi_var *= sign);
}

static int	ft_check_plus_and_less(char **args)
{
	if ((args[1][0] == '+' && args[1][1] == '+')
		|| (args[1][0] == '+' && args[1][1] == '-')
		|| (args[1][0] == '-' && args[1][1] == '-')
		|| (args[1][0] == '-' && args[1][1] == '+'))
		return (-3);
	return (1);
}

static int	ft_check_exit_args(char **args, t_mini *data)
{
	int			i;
	long long	error;

	i = 0;
	if (!args[1])
		return (-1);
	if (args[1] && args[2])
		return (-2);
	while (args[1][i])
	{
		if (ft_check_plus_and_less(args) == -3)
			return (-3);
		else
			i++;
		if (!ft_isdigit(args[1][i]))
			return (-3);
		i++;
	}
	error = (ft_exit_atoi(args[1]));
	ft_free_all(data);
	if (data->pipes_left)
		ft_free(args);
	ft_putstr_fd("exit\n", 2);
	exit(error);
}

static void	ft_exit_else(int ret, t_mini *data, char **args)
{
	if (ret == -3)
	{
		ft_putstr_fd("exit\n", 2);
		ft_error("minishell: exit: numeric argument required\n", RED, 1);
		ft_free_all(data);
		if (data->pipes_left)
			ft_free(args);
		exit(2);
	}
}

int	ft_exit(char **args, t_mini *data)
{
	int			ret;
	long long	error;

	error = 0;
	ret = ft_check_exit_args(args, data);
	if (ret == -2)
		return (data->g_error = 1,
			ft_error("minishell: exit: too many arguments\n", RED, 1));
	ft_exit_else(ret, data, args);
	ft_free_all(data);
	if (data->pipes_left)
		ft_free(args);
	ft_putstr_fd("exit\n", 2);
	(void)error;
	exit(data->g_error);
	return (1);
}
