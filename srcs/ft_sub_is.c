/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_is.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 11:54:14 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/16 03:32:38 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sub_defined(t_token *token, int i_tok, int i_subtok)
{
	if (token[i_tok].subtoken[i_subtok].is_redirection_output == 1
		|| token[i_tok].subtoken[i_subtok].is_redirection_input == 1
		|| token[i_tok].subtoken[i_subtok].is_append_output == 1
		|| token[i_tok].subtoken[i_subtok].is_here_doc == 1
		|| token[i_tok].subtoken[i_subtok].is_word == 1
		|| token[i_tok].subtoken[i_subtok].is_pipe == 1)
		return (1);
	else
		return (0);
}

int	is_sub_meta_char(t_token *token, int i_tok, int i_subtok)
{
	if (token[i_tok].subtoken[i_subtok].sub_elem[0] == '>'
		&& token[i_tok].subtoken[i_subtok].sub_elem[1] == 0)
		return (token[i_tok].subtoken[i_subtok].is_redirection_output = 1);
	else if (token[i_tok].subtoken[i_subtok].sub_elem[0] == '<'
		&& token[i_tok].subtoken[i_subtok].sub_elem[1] == 0)
		return (token[i_tok].subtoken[i_subtok].is_redirection_input = 1);
	else if (token[i_tok].subtoken[i_subtok].sub_elem[0] == '>'
		&& token[i_tok].subtoken[i_subtok].sub_elem[1] == '>'
		&& token[i_tok].subtoken[i_subtok].sub_elem[2] == 0)
		return (token[i_tok].subtoken[i_subtok].is_append_output = 1);
	else if (token[i_tok].subtoken[i_subtok].sub_elem[0] == '<'
		&& token[i_tok].subtoken[i_subtok].sub_elem[1] == '<'
		&& token[i_tok].subtoken[i_subtok].sub_elem[2] == 0)
		return (token[i_tok].subtoken[i_subtok].is_here_doc = 1);
	else if (token[i_tok].subtoken[i_subtok].sub_elem[0] == '|'
		&& token[i_tok].subtoken[i_subtok].sub_elem[1] == 0)
		return (token[i_tok].subtoken[i_subtok].is_pipe = 1);
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

void	which_sub_is(t_token *token, int i_tok, int i_subtok)
{
	if (is_sub_meta_char(token, i_tok, i_subtok) == 0)
		token[i_tok].subtoken[i_subtok].is_word = 1;
}
