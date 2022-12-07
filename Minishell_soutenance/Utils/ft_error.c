/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:26:43 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/29 13:30:17 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *str, char *color, int error)
{
	ft_putstr_fd(color, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(RESET, 2);
	return (error);
}
