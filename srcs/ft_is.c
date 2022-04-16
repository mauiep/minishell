/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 11:54:14 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/16 02:22:07 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_meta_char(t_token *token, int i)
{
	if (token[i].elem[0] == '<' && token[i].elem[1] == 0)
		return (token[i].is_redirection_input = 1);
	else if (token[i].elem[0] == '>' && token[i].elem[1] == 0)
		return (token[i].is_redirection_output = 1);
	else if (token[i].elem[0] == '|' && token[i].elem[1] == 0)
		return (token[i].is_pipe = 1);
	else if (token[i].elem[0] == '<' && token[i].elem[1] == '<'
		&& token[i].elem[2] == 0)
		return (token[i].is_here_doc = 1);
	else if (token[i].elem[0] == '>' && token[i].elem[1] == '>'
		&& token[i].elem[2] == 0)
		return (token[i].is_append_output = 1);
	else
		return (0);
}

/*
 *			INVALIDE AU CINQUIEME POINT DE LA PARTIE OBLIGATOIRE DU SUJET
 void	is_env_variable(t_token *token, int i)
 {
 	int	i_str;
 
 	i_str = 0;
 	while (token[i].elem[i_str] != 0)
 	{
 		if (i_str > 0 && token[i].elem[i_str - 1] != '\\'
 			&& token[i].elem[i_str] == '$' && token[i].elem[i_str + 1])
 			token[i].is_env_variable = 1;
 		i_str++;
  	}
 }
 *
 */

void	which_is(t_token *token, int i)
{
	if (is_meta_char(token, i) == 0)
		token[i].is_word = 1;
}
