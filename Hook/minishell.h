/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:02:34 by ceatgie           #+#    #+#             */
/*   Updated: 2022/11/11 15:19:38 by ceatgie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/stat.h>
# include <stdarg.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

//------------------------------------------------------------------------------------
//										Define
//------------------------------------------------------------------------------------

# define SIMPLE_QUOTE 39

//------------------------------------------------------------------------------------
//										Colors
//------------------------------------------------------------------------------------

# define RED	"\033[0;31m"
# define YELLOW	"\033[0;33m"
# define GREEN	"\033[1;32m"
# define BLUE "\033[1;34m"
# define RESET	"\033[0m"

//------------------------------------------------------------------------------------
//										Structure
//------------------------------------------------------------------------------------

typedef struct s_mini
{
	int		argc;
	char	*home;
	char	**argv;
	char	**envp;
	char	**env_tab;
	char	**cmd;
	char	*line;
	char	*prompt;
	int		prompt_var;
	char	*converted_path;
}			t_mini;

//------------------------------------------------------------------------------------
//										Liste chainee
//------------------------------------------------------------------------------------

typedef struct s_lst
{
	char			*str;
	int				token;
	struct s_lst	*next;
	struct s_lst	*prev;
}					t_lst;


//------------------------------------------------------------------------------------
//										Adrien
//------------------------------------------------------------------------------------

// cleanfile
//==========

int	ft_cleanfile(t_lst *lst);

// Exec
//==========

char	*ft_check_bin_path(char *bin, char *paths);
int		ft_len_bef_col(char *paths);
char	*ft_find_bin(char *bin, char *paths, char **argv, char **envp);
int		ft_handle_exec(t_lst *lst, t_mini *data);

// Fd
//==========

int		**create_pipe_arr(int nb_pipes);
void	free_pipe_array(int **pipefd, int nb_pipes);
int		ft_close_pipes(int **pipefd, int nb_pipes);

// cleanfile
//==========

int	ft_open_create(char *filename, bool apnd_or_not, int token);

// Joindollar
//==========

int		ft_joindollar(t_lst *ptr, int i, t_mini *data);
int		ft_strjoindollar(t_lst *l, char *var, int k, int dollar);
int		ft_replacedollar(t_lst *l, int k, int c, t_mini *data);

// Lst_spe
//==========

int	push_first_lst(t_lst *new, t_lst *lst);
t_lst	*pick_the_lst(t_lst *last);
t_lst	*first_lst(t_lst *lst);

// Lst
//==========

int		free_lst(t_lst *src);
void	push_lst(t_lst *new, t_lst *lst);
void	ft_printlst(t_lst *a);
int		lst_len(t_lst *lst);
t_lst	*ft_lstnew(void);

// Minishell
//==========

int	ft_handle_pipe(int **pipefd, int pipes_left, int nb_pipes, int *fd_in);

// Pipe
//==========

t_lst	*ft_next_pipe(t_lst *lst);
int		ft_pipes_left(t_lst *lst);
int		ft_pipes(t_lst *lst, int nb_pipes, t_mini *data);
int		ft_wait_procs(int ac, pid_t *list);

// Push
//==========

int	get_next_word(char *buffer, t_lst *new);
int	push_next_word(t_lst *lst, char *buffer);
int	push_word(t_lst *lst, char *buffer);
int	push_sep(t_lst *lst, char *buffer);

// Quote
//==========

char	*without_quotes(char *src, int i, int j);
char	*ft_strpos(char *src);
int		ft_negtopos(char **tab);
int		lst_remove_quotes(t_lst *l);
int 	remove_quotes(char **tab);

// Redirection
//==========

int		ft_handle_redirections(t_lst *lst);
int		ft_open_dup(t_lst *lst, int token);
char	**ft_splitargs(t_lst *lst);

// splitarg
//==========

int		spe_count_words(char *str);
int		spe_lenword(char *str);
char	*spe_get_word(char *str, int n);

// str
//==========

int		ft_strcpy(char *str, char *str2);
int		nk_strcmp(char const *str, char const *str2);
bool	ft_has_eq(char *str);
int		ft_strncpy(char *str, char *str2, int n);
char	*ft_strjoin2(char *str, char *str2);

// Verif
//==========

int	ft_verif(t_lst *lst);
int	edit_maillon(char *buffer, int i, t_lst *tmp);
int	recover_args(t_lst *last, char *buffer);
int	last_redirect(t_lst *lst);

// Parse
//==========

int	get_word(char *buffer, t_lst *new);
int	expand(t_lst *lst, t_mini *data);
int	parse(char *line_buffer, t_mini *data);

// Utils
//==========

int	is_sep(char c);
int	print_err(int err);
int	which_redirect(char *str);

// Utils2
//==========

int		ft_negstrcpy(char *str, char *str2);
char	*ft_strjoinneg(char *str, char *str2);

//------------------------------------------------------------------------------------
//										Built-in
//------------------------------------------------------------------------------------

int		ft_is_built_in(t_mini *data);
//	cd
//========

int		ft_cd_error_manager(char *path, t_mini *data);
int		ft_cd(t_mini *data);
int		ft_change_directory(char *path, t_mini *data);
char	*ft_convert_arg_to_path(t_mini *data);

//	env
//========

void	ft_env(t_mini *data);

//	export
//========

void	ft_add_env_var(t_mini *data, int arg);
int		ft_check_export_var(char *arg);
int		ft_export(t_mini *data);
void	ft_sort_and_print_env(t_mini *data);

//	pwd
//========

void	ft_pwd(void);

//	unset
//========

int	ft_unset(t_mini *data);

//------------------------------------------------------------------------------------
//										Env
//------------------------------------------------------------------------------------

void	ft_change_env(char *pwd, char *env_var, t_mini *data);
void	ft_create_env(t_mini *data);
char	**ft_create_temp_env(t_mini *data, int size);
int		ft_env_len(t_mini *data);
int		ft_find_env(char *to_find_env_var, t_mini *data);
char	*ft_get_env_var(char	*env_var, t_mini *data);
void	ft_replace_env(char **temp_env, t_mini *data);

//------------------------------------------------------------------------------------
//										LIBFT
//------------------------------------------------------------------------------------


void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t elementCount, size_t elementSize);
int			ft_isalpha(int character);
int			ft_isdigit(int digit);
void		*ft_memset(void *b, int c, size_t len);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char *s, char *charset);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strndup(const char *s, int n);

//------------------------------------------------------------------------------------
//										Minishell
//------------------------------------------------------------------------------------

char	*ft_prompt(t_mini *data);
int		minishell(t_mini *data);

//------------------------------------------------------------------------------------
//										Parsing
//------------------------------------------------------------------------------------

int	ft_is_inside_quote(char	*line, int i);
int	ft_parse_quote(char *line, t_mini *data);
int ft_wrong_syntax_final_check(char *line, char character, int i);
int	ft_wrong_syntax_newline_check(char *line);
int	ft_wrong_syntax_redir_check(char *line, char character);
int	ft_wrong_syntax(char *line, char character, int i);

//------------------------------------------------------------------------------------
//										Utils
//------------------------------------------------------------------------------------

int		ft_error(char *str, char *color, int error);
void	ft_exit(t_mini *data);
void	ft_free(char **tab);
char	**ft_if_malloc_issue(char **tab, int i);
void	ft_init(t_mini *data, int argc, char **argv, char **envp);
void	ft_print_minishell(void);


#endif