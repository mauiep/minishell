/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:00:34 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/16 03:35:13 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_is_null(t_split *split)
{
	perror("parse(): Error during split");
	free(split->split);
	free(split);
}

void	parse_split_ret_error(t_split *split, int i)
{
	perror("parse(): Error encountered, freeing and exiting");
	while (split->split[i] != NULL)
		free(split->split[i++]);
	free(split->split);
	free(split);
}

void	display_dq_token(t_token *token, int i)
{
	int	i_dq;

	i_dq = 0;
	while (i_dq < token[i].nb_subtoken)
	{
		printf("\tfrom token[%d]->double quoted token[%d] = %s\n", i, i_dq,
			token[i].dq[i_dq].dq_elem);
		i_dq++;
	}
}

/*
 *
void	display_token_properties(t_token *token, int i)
{
	if (token[i].is_redirection_input == 1)
		printf("\t->token %d is redirection input\n", token[i].id_token);
	if (token[i].is_redirection_output == 1)
		printf("\t->token %d is redirection output\n", token[i].id_token);
	if (token[i].is_here_doc == 1)
		printf("\t->token %d is here documents\n", token[i].id_token);
	if (token[i].is_append_output == 1)
		printf("\t->token %d is append output\n", token[i].id_token);
	if (token[i].is_cmd == 1)
		printf("\t->token %d is command\n", token[i].id_token);
	if (token[i].is_arg == 1)
		printf("\t->token %d is argument\n", token[i].id_token);
	if (token[i].is_single_quoted == 1)
		printf("\t->token %d is single quoted\n", token[i].id_token);
	if (token[i].is_double_quoted == 1)
	{
		printf("\t->token %d is double quoted\n", token[i].id_token);
		display_dq_token(token, i);
	}
	if (token[i].is_pipe == 1)
		printf("\t->token %d is pipe\n", token[i].id_token);
	if (token[i].is_env_variable == 1)
		printf("\t->token %d is env variable\n", token[i].id_token);
}

void	display_sub_token_properties(t_token *token, int i_tok, int i_subtok)
{
	if (token[i_tok].subtoken[i_subtok].is_redirection_input == 1)
		printf("\t\t->subtoken %d is redirection input\n", i_subtok);
	if (token[i_tok].subtoken[i_subtok].is_redirection_output == 1)
		printf("\t\t->subtoken %d is redirection output\n", i_subtok);
	if (token[i_tok].subtoken[i_subtok].is_here_doc == 1)
		printf("\t\t->subtoken %d is here documents\n", i_subtok);
	if (token[i_tok].subtoken[i_subtok].is_append_output == 1)
		printf("\t\t->subtoken %d is append output\n", i_subtok);
	if (token[i_tok].subtoken[i_subtok].is_cmd == 1)
		printf("\t\t->subtoken %d is command\n", i_subtok);
	if (token[i_tok].subtoken[i_subtok].is_arg == 1)
		printf("\t\t->subtoken %d is argument\n", i_subtok);
	if (token[i_tok].subtoken[i_subtok].is_single_quoted == 1)
		printf("\t\t->subtoken %d is single quoted\n", i_subtok);
	if (token[i_tok].subtoken[i_subtok].is_double_quoted == 1)
		printf("\t\t->token %d is double quoted TODO isolate quoted env variable\n",
			i_subtok);
	if (token[i_tok].subtoken[i_subtok].is_pipe == 1)
		printf("\t\t->subtoken %d is pipe\n", i_subtok);
	if (token[i_tok].subtoken[i_subtok].is_env_variable == 1)
		printf("\t\t->subtoken %d is env variable\n", i_subtok);
}
 *
 */

void	display_subtoken(t_token *token, int i_tok)
{
	int	i_subtok;

	i_subtok = 0;
	while (i_subtok < token[i_tok].nb_subtoken)
	{
		printf("\ttoken[%d]->subtoken[%d] = %s\n", i_tok, i_subtok,
			token[i_tok].subtoken[i_subtok].sub_elem);
		//which_sub_is(token, i_tok, i_subtok);
		//display_sub_token_properties(token, i_tok, i_subtok);
		i_subtok++;
	}
}

void	process_split(t_split *split, int i)
{
	t_token	*token;

	token = ft_token(split);
	if (token == NULL)
	{
		perror("process_split(): token scuffed");
		return ;
	}
	while (token[i].elem != NULL)
	{
		which_is(token, i);
		printf("token[%d] = %s\n", i, token[i].elem);
		//display_token_properties(token, i);
		if (seek_and_count_meta_char(token, i) != 0)
		{
			subtokenize(token, i);
			//display_subtoken(token, i);
		}
		i++;
	}
	unload(split, token);
}

void	parse(char *line_buffer)
{
	t_split	*split;
	int		i;

	i = 0;
	split = (t_split *)malloc(sizeof(t_split));
	if (split == NULL)
	{
		perror("parse(): Error allocating split structure");
		return ;
	}
	ft_memset((void *)split, 0, sizeof(t_split));
	count_quotes(line_buffer, split);
	if (redo_split(line_buffer, split) == -1)
		parse_split_ret_error(split, i);
	else
	{
		if (split->split[i] == NULL && line_buffer == NULL)
			split_is_null(split);
		else
			process_split(split, i);
	}
}
