/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:32:28 by admaupie          #+#    #+#             */
/*   Updated: 2022/11/14 17:32:47 by admaupie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

    ft_echap est appele quand un '\' est rencontre a str[i], on va decaler tous
    les caracteres de un vers la gauche en remplacant ainsi le '\' Le caractere
    suivant sera mis en negatif pour qu'il soit ignore par le parsing.

*/

int ft_echap(char *str, int i)
{
    int     j;
    char    *tmp;

    j = 0;
    tmp = str + i;
    if (tmp[1] == '\0')
        return (0);
    while (tmp[j] != '\0')
    {
        if (j == 0)
            tmp[j] = - tmp[j + 1];
        else
            tmp[j] = tmp[j + 1];
        j++;
    }
    return (1);
}
