/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceatgie <ceatgie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:02:24 by ceatgie           #+#    #+#             */
/*   Updated: 2022/12/08 05:15:04 by ceatgie          ###   ########.fr       */
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

//-----------------------------------------------------------------------------
//										Define
//-----------------------------------------------------------------------------

# define SIMPLE_QUOTE 39

//-----------------------------------------------------------------------------
//										Colors
//-----------------------------------------------------------------------------

# define BLACK "\001\033[1;30m\002"
# define RED "\001\033[1;31m\002"
# define GREEN "\001\033[1;32m\002"
# define YELLOW "\001\033[1;33m\002"
# define BLUE "\001\033[1;34m\002"
# define PURPLE "\001\033[1;35m\002"
# define CYAN "\001\033[1;36m\002"
# define WHITE "\001\033[1;37m\002"
# define RESET "\001\033[0m\002"

//-----------------------------------------------------------------------------
//										Liste chainee
//-----------------------------------------------------------------------------

typedef struct s_lst
{
	char			*str;
	int				token;
	int				num;
	struct s_lst	*next;
	struct s_lst	*prev;
}					t_lst;

//-----------------------------------------------------------------------------
//										Structure
//-----------------------------------------------------------------------------

typedef struct s_mini
{
	int				argc;
	char			*home;
	char			**argv;
	char			**envp;
	char			**env_tab;
	char			**cmd;
	char			*line;
	char			*prompt;
	int				prompt_var;
	pid_t			g_error;
	char			**splitargs;
	char			*converted_path;
	int				**pipefd;
	int				i;
	int				nb_pipes;
	char			*envval;
	pid_t			*list;
	int				pipes_left;
	int				fd_in;
	int				dup;
	int				command_ok;
	struct s_lst	*lst;
	struct s_lst	*start_lst;
}			t_mini;

typedef struct s_joindollard
{
	char	*tmp;
	char	*to_free;
	char	*envval;
	char	*dollard;
	char	*new;
	int		j;
	int		ret;	
}			t_joindollard;

//-----------------------------------------------------------------------------
//										Built-in
//-----------------------------------------------------------------------------

int		ft_is_built_in(char **args, t_mini *data);

//------------------------
//			cd
//------------------------

char	*ft_add_home_path(char **args, t_mini *data);
int		ft_cd_error_manager(char *path, t_mini *data);
int		ft_cd_check_if_arg_is_dash(char **args, t_mini *data);
int		ft_cd(char **args, t_mini *data);
int		ft_change_directory(char *path, t_mini *data);
char	*ft_convert_arg_to_path(char **args, t_mini *data);

//------------------------
//			echo
//------------------------

int		ft_echo(char **args);

//------------------------
//			env
//------------------------

void	ft_env(t_mini *data);

//------------------------
//			exit
//------------------------

int		ft_exit(char **args, t_mini *data);
void	ft_free_all(t_mini *data);

//------------------------
//			env
//------------------------

void	ft_add_env_var(char *arg, t_mini *data);
int		ft_check_export_var(char *arg);
int		ft_export(char **args, t_mini *data);
void	ft_sort_and_print_env(t_mini *data);

//------------------------
//			pwd
//------------------------

void	ft_pwd(void);

//------------------------
//			unset
//------------------------

int		ft_check_unset_arg(char *arg);
char	**ft_realloc_env(int index, t_mini *data);
int		ft_unset(char **args, t_mini *data);

//-----------------------------------------------------------------------------
//										Env
//-----------------------------------------------------------------------------

void	ft_change_env(char *pwd, char *env_var, t_mini *data);
void	ft_create_env(t_mini *data);
char	**ft_create_temp_env(t_mini *data, int size);
int		ft_env_len(t_mini *data);
int		ft_find_env(char *to_find_env_var, t_mini *data);
char	*ft_get_env_var(char	*env_var, t_mini *data);
void	ft_replace_env(char **temp_env, t_mini *data);

//-----------------------------------------------------------------------------
//										Exec
//-----------------------------------------------------------------------------

int		ft_handle_exec(t_lst *lst, t_mini *data);
int		**create_pipe_arr(int nb_pipes);
void	free_pipe_array(int **pipefd, int nb_pipes);
int		ft_close_pipes(int **pipefd, int nb_pipes);
char	*ft_check_bin_path(char *bin, char *paths);
int		ft_len_bef_col(char *paths);
char	*ft_find_bin(char *bin, char *paths, char **argv, char **envp);
int		ft_handle_pipe(int **pipefd, int pipes_left, int nb_pipes, int *fd_in);
void	sig_null(int signal);
void	sig_handler(int signal);
void	define_signals(void);

//-----------------------------------------------------------------------------
//										LIBFT
//-----------------------------------------------------------------------------

int		ft_strlen(char *str);
int		ft_isalpha(int character);
int		ft_isdigit(int digit);
char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char *s, char *charset);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strndup(const char *s, int n);

//-----------------------------------------------------------------------------
//										Minishell
//-----------------------------------------------------------------------------

char	*ft_prompt(t_mini *data);
int		minishell(t_mini *data);
void	launch_minishell(int argc, char **argv, char **envp);

//-----------------------------------------------------------------------------
//										Parsing
//-----------------------------------------------------------------------------

int		get_word(char *buffer, t_lst *new);
int		expand(t_lst *lst, t_mini *data);
int		ft_check_redir(char *line);
void	lst_remove_spaces(t_lst *lst);
int		ft_is_inside_quote(char	*line, int i);
int		ft_wrong_syntax_newline_check(char *line);
int		ft_wrong_syntax_redir_check(char *line, char character);
int		ft_cleanfile(t_lst *lst);
int		ft_echap(char *str, int i);
int		end_dollar(char c);
char	*dollarval(char *tmp, int i, int j, t_mini *data);
int		return_dollar(char *str, char *tmp, char *envval, t_lst *ptr);
int		ft_joindollar(t_lst *ptr, int i, t_mini *data);
void	ft_quadrafree(void *s1, void *s2, void *s3, void *s4);
int		lst_remove_quotes(t_lst *l);
int		remove_quotes(char **tab);
char	*without_quotes(char *src, int i, int j);
char	*ft_strpos(char *src);
int		ft_negtopos(char **tab);
int		spe_count_words(char *str);
int		spe_lenword(char *str);
char	*spe_get_word(char *str, int n);
char	**ft_splitargs(t_lst *lst);
int		parse(char *line_buffer, t_mini *data);

//-----------------------------------------------------------------------------
//										Redirect
//-----------------------------------------------------------------------------

int		ft_heredoc(t_lst *lst, t_mini *data, int fd);
int		ft_handle_heredoc(t_lst *lst, t_mini *data);
int		mini_expand(t_lst *tmp, t_mini *data);
int		ft_open_create(char *filename, bool apnd_or_not, int token);
t_lst	*ft_next_pipe(t_lst *lst);
int		ft_pipes_left(t_lst *lst);
int		ft_init_pipe_var(t_mini *data, int nb_pipes, t_lst *lst);
int		ft_pipes(t_lst *lst, int nb_pipes, t_mini *data);
int		ft_wait_procs(int ac, pid_t *list, t_mini *data);
int		ft_handle_redirections(t_lst *lst, t_mini *data);
int		ft_open_dup(t_lst *lst, int token, t_mini *data);
int		ft_for_token2(t_lst *lst, t_mini *data, int fd);
int		ft_for_token3(t_lst *lst, t_mini *data, int fd);
int		ft_for_token4(t_lst *lst, t_mini *data, int fd);
int		ft_for_token5(t_lst *lst, t_mini *data, int fd);

//-----------------------------------------------------------------------------
//										Utils
//-----------------------------------------------------------------------------

int		ft_is_inside_quote(char	*line, int i);
int		ft_error(char *str, char *color, int error);
void	ft_free(char **tab);
char	**ft_if_malloc_issue(char **tab, int i);
void	ft_init(t_mini *data, int argc, char **argv, char **envp);
void	ft_print_minishell(void);
int		ft_error_msg(char *line, char character, int i);
int		ft_error_token(char	*msg, char *line, char character, int i);
char	*ft_strndup2(const char *src, int n);
int		push_first_lst(t_lst *new, t_lst *lst);
t_lst	*pick_the_lst(t_lst *last);
t_lst	*first_lst(t_lst *lst);
int		get_next_word(char *buffer, t_lst *new);
int		push_next_word(t_lst *lst, char *buffer);
int		push_word(t_lst *lst, char *buffer);
int		push_sep(t_lst *lst, char *buffer);
int		ft_strcpy(char *str, char *str2);
int		nk_strcmp(char const *str, char const *str2);
bool	ft_has_eq(char *str);
int		ft_strncpy2(char *str, char *str2, int n);
char	*ft_strjoin2(char *str, char *str2);
int		ft_verif(t_lst *lst, char *linebuffer);
int		edit_maillon(char *buffer, int i, t_lst *tmp);
int		recover_args(t_lst *last, char *buffer);
int		is_sep(char c);
int		print_err(int err);
int		which_redirect(char *str);
int		ft_negstrcpy(char *str, char *str2);
char	*ft_strjoinneg(char *str, char *str2);
int		free_lst(t_lst *src);
t_lst	*ft_lstnew(void);
void	push_lst(t_lst *new, t_lst *lst);
void	ft_tab_to_spaces(char *str);
int		command_ok(char *str);
void	ft_printlst(t_lst *lst);
void	ft_quadrafree(void *s1, void *s2, void *s3, void *s4);
int		ft_for_error_directory(char *line);
void	ft_free_all_exec(t_mini *data);
int		ft_isspace(const char *str);
int		ft_error_for_executable(char **args, t_mini *data);
int		program_exec(char **args, t_mini *data);
int		ft_error_for_executable(char **args, t_mini *data);
int		ft_for_error_directory(char *line);

#endif
