#ifndef NIKISHELL_H

//# include "parse.h"
# include "dynarray.h"

typedef struct s_safe
{
	t_dynarray	*darr;
	int			**pipefd;
	int			nb_pipes;
}	t_safe;

extern t_safe	g_vrac;

char	*ft_get_dir(char *path);
char	*ft_make_prompt(char *dir);
int		init_dyn_env(char **envp, t_dynarray *darr);
void	ft_dyn_env(t_dynarray *darr);
int		ft_getenv_index(char **envp, uint64_t len, char *str, bool un_exp);
int		ft_export(t_dynarray *darr, char *str);
int		ft_envcmp(char *str, char *str2);
int		ft_unset(t_dynarray *darr, char *str);
bool	ft_has_eq(char *str);
int		ft_cd(char *str, char *home);
int		ft_readline(t_dynarray *darr);
char	*ft_check_bin_path(char *bin, char *paths);
char	*ft_getenvval(char *str, t_dynarray *darr, bool val_or_all, bool un_or_exp);
char	*ft_find_bin(char *bin, char *paths, char **argv, char **envp);
int		ft_len_bef_col(char *paths);
void	ft_free_all(t_dynarray *darr);
void	sigd_handler(int i);
int		ft_pipes(t_lst *lst, int nb_pipes, t_dynarray *darr);
int		ft_wait_procs(int ac, pid_t *list);
int		ft_close_pipes(int **pipefd, int nb_pipes);
int		**create_pipe_arr(int nb_pipes);
void	free_pipe_array(int **pipefd, int	nb_pipes);
int		ft_pipes_left(t_lst *lst);
char	*ft_strjoin(char *str, char *str2);
int		ft_check_env(t_dynarray *darr);
int		ft_open_create(char *filename, bool apnd_or_not, int token);
t_lst	*ft_next_pipe(t_lst *lst);
int		ft_handle_pipe(int **pipefd, int pipes_left, int nb_pipes, int *fd_in);
void	ft_print_pipes(int **pipefd, int nb_pipes);
void	ft_print_token(t_lst token);
void	ft_print_list(t_lst *token);
int		ft_handle_redirections(t_lst *lst, t_dynarray *darr);
int		ft_handle_exec(t_lst *lst, t_dynarray *darr);
int		ft_open_dup(t_lst *lst, int token, t_dynarray *darr);

#endif
