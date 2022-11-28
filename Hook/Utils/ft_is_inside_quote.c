#include "minishell.h"

/*
**	Cette fonction prend en parametre
**	
**	-La ligne donnee par GNL
**	-L'index dans line
**	
**	========================================
**	
**	Avance l'index de la ligne donnee par GNL tant que l'on est entre quote
*/

int	ft_is_inside_quote(char	*line, int i)
{
	char	quote;																		// On creer une variable quote qui vaudra une simple ou double quote

	while (line[i] && ((line[i] == '\'') || line[i] == '"'))						  // Tant que la ligne donnee par gnl est une simple ou double quote
	{
		quote = line[i];															// La variable quote vaut une simple ou une double quote
		i++;																	   // On passe au caractere suivant
		while (line[i] && line[i] != quote)									  	  // Tant que le caractere actuel n'est pas egal a la variable quote
		{
			if (line[i] && line[i] == '\\')
				i++;														   // Si le caractere est un \ alors on incremente de 1 car la quote derriere ce dernier ne sera pas une fin de quote									 	  
			i++;														  	  // On passe sinon au caractere suivant 
		}
		if (i == ((int)ft_strlen(line)))									// Si on est a la fin de la string
			break ;														   // Alors on quitte la boucle
		else															  // Sinon	
			i++;														 // On passe au caractere suivant
	}
	return (i);														   // On return (i);
}