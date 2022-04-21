#ifndef GUIGUISHELL_H

typedef struct s_doublequote
{
	int		id_dq;
	int		nb_elem;
	int		is_env;
	int		is_arg;
	char	*dq_elem;
}	t_dq;

typedef struct s_subtoken
{
	int		id_subtoken;
	int		father_token;
	int		is_redirection_input;
	int		is_redirection_output;
	int		is_here_doc;
	int		is_append_output;
	int		is_pipe;
	int		is_word;
	int		is_wrong;
	char	*sub_elem;
	t_dq	*dq;
}	t_subtoken;

typedef struct s_token
{
	int			is_redirection_input;
	int			is_redirection_output;
	int			is_here_doc;
	int			is_append_output;
	int			is_pipe;
	int			is_word;
	int			is_wrong;
	int			nb_subtoken;
	char		*elem;
	t_subtoken	*subtoken;
	t_dq		*dq;
}	t_token;

typedef struct s_split
{
	char	**split;
	int		i;
	int		j;
	char	quote;
	int		single_quote;
	int		double_quote;
	int		nb_split;
}	t_split;

typedef struct s_indexer
{
	int	*begin_word;
	int	*end_word;
	int	nb_word;
}	t_index;

/*
 *	ft_token.c
 */

t_token	*ft_token(t_split *split);

/*
 *	string_utils.c
 */

void	count_quotes(char *str, t_split *split);
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
int		skip_space(char *str);

/*
 *	ft_quote.c
 */

void	to_quote_or_not_to_quote(char *str, int i, t_split *split);
int		is_quoted_good(char *str);

/*
 *	parser.c
 */

void	parse(char *line_buffer);

/*
 *	redo_split.c
 */

void	tab_init(int *tab, int len);
int		redo_split(char *str, t_split *split);

/*
 *	indexer.c
 */

t_index	*init_indexer(char *str);
t_index	*indexing(char *str, t_split *split);

/*
 *	ft_is.c
 */

int		is_meta_char(t_token *token, int i);
void	which_is(t_token *token, int i);

/*
 *	unload.c
 */

void	unload(t_split *split, t_token *token);
void	unload_indexer(t_index *index);

/*
 *	seek_meta_char.c
 */

int		which_meta_char(t_token *token, int i_tok, int i_str);
int		seek_meta_char(t_token *token, int i);
int		seek_and_count_meta_char(t_token *token, int i);

/*
 *	sub_indexer.c
 */

t_index	*subindexing(t_token *token, int i_tok);

/*
 *	sub_token.c
 */

int		subtokenize(t_token *token, int i_tok);

/*
 *	ft_sub_is.c
 */

void	which_sub_is(t_token *token, int i_tok, int i_subtok);

/*
 *	isolate_env_indexer.c
 */

int		is_space_or_null_or_dquote(char c);
t_index	*env_indexing(t_token *token, int i_tok);

/*
 *	isolate_env.c
 */

int		double_quoted_arg_has_env(char *str);

/*
 *	doublequote_token.c
 */

int		double_quote_tokenize(t_token *token, int i_tok);

#endif
