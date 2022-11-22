/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:27:24 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/21 15:16:55 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Cette fonction prend en parametre :
**	
**	- rien
**	
**	========================================
**	
**	Cette fonction sert a indiquer le path ou l'on se situe actuellement
*/

void	ft_pwd(void)
{
	char	*buffer;										// On creer un buffer qui contiendra le path actuel donner par getcwd()

	buffer = NULL;										  // On l'initialise a NULL
	buffer = getcwd(NULL, 0);							 // On l'associe a resultat de getcwd()
	if (buffer)											// Si il n'y a aucune erreur de malloc
		ft_putendl_fd(buffer, 1);					   // On affiche le path actuel contenu dans le buffer 
	else											  // Sinon
	{
		write(2, RED, ft_strlen(RED));				// On ecrit en rouge sur la sortie erreur
		write(2, "minishell: pwd: ", 16);		   // minishell: pwd:
		ft_putendl_fd(strerror(errno), 2);		  // Suivi du retour de l'erreur gerer par errno
		ft_putstr_fd(RESET, 2);					 // On reset la couleur sur la sortie erreur
	}
	free(buffer);							   // On free le buffer pour eviter les fuites de memoires
}
