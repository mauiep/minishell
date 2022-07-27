#ifndef NIKISHELL_H

# include "parse.h"
# include "dynarray.h"

typedef struct s_safe
{
	t_dynarray	*darr;
}	t_safe;

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
char	*ft_getenvval(char *str, char **envp, uint64_t len, bool un_or_exp);
char	*ft_find_bin(char *bin, char *paths, char **argv, char **envp);
int		ft_len_bef_col(char *paths);
void	sigintHandler(int sig);
void	ft_signal();
void	ft_free_all(t_dynarray *darr);
char	*ft_pipes(t_lst *lst, int nb_pipes, t_dynarray *darr);
int		ft_wait_procs(int ac, pid_t *list);
int		ft_close_pipes(int ac, int **pipefd);
int		ft_close_unused_fd(int nb_cmd, int **pipefd, int i);
int		**create_pipe_arr(int nb_pipes);
void	free_pipe_array(int **pipefd, int	nb_pipes);
int		ft_open_file(char *filename);
int		ft_pipes_left(t_lst *lst);
int		close_pipe_array(int **pipefd, int	nb_pipes);

#endif
