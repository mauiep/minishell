#ifndef NIKISHELL_H

# include "dynarray.h"

char	*ft_get_dir(char *path);
char	*ft_make_prompt(char *dir);
int	init_dyn_env(char **envp, t_dynarray *darr);
void	ft_dyn_env(t_dynarray *darr);
int	ft_getenv_index(char **envp, uint64_t len, char *str, bool un_exp);
int	ft_export(t_dynarray *darr, char *str);
int	ft_envcmp(char *str, char *str2);
int	ft_unset(t_dynarray *darr, char *str);
bool	ft_has_eq(char *str);
int	ft_cd(char *str, char *home);
int	ft_readline(t_dynarray *darr);
char	*ft_check_bin_path(char *bin, char *paths);
char	*ft_getenvval(char *str, char **envp, uint64_t len);
char	*ft_find_bin(char *bin, char *paths, char **argv, char **envp);
int	ft_len_bef_col(char *paths);

#endif
