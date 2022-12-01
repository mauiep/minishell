/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:05:52 by admaupie          #+#    #+#             */
/*   Updated: 2021/11/29 16:22:02 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_swap(char *tab, int sign)
{
	size_t			i;
	unsigned char	tmp;
	size_t			size;

	size = ft_strlen(tab) - 1;
	if (sign == 1)
		i = 1;
	else
		i = 0;
	tmp = 0;
	while (i < size)
	{
		tmp = tab[i];
		tab[i] = tab[size];
		tab[size] = tmp;
		i++;
		size--;
	}
	return (tab);
}

static int	ft_size_itoa(long n)
{
	int	cpt;

	cpt = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		cpt = 1;
	}
	while (n > 0)
	{
		n /= 10;
		cpt++;
	}
	return (cpt);
}

static void	ft_norminette(char *tab, long nb, int i)
{
	if (nb == 0)
	{
		tab[0] = '0';
		tab[1] = '\0';
		return ;
	}
	while (nb > 0)
	{
		tab[i] = (nb % 10) + '0';
		nb /= 10;
		i++;
	}
	tab[i] = '\0';
}

char	*ft_itoa(int n)
{
	int		i;
	char	*tab;
	int		sign;
	long	nb;

	i = 0;
	nb = n;
	sign = 0;
	tab = malloc(sizeof(char) * (ft_size_itoa(nb) + 1));
	if (!tab)
		return (NULL);
	if (nb < 0)
	{
		nb *= -1;
		i = 1;
		tab[0] = '-';
		sign = 1;
	}
	ft_norminette(tab, nb, i);
	ft_swap(tab, sign);
	return (tab);
}
