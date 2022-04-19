#include "minishell.h"

char	*ft_check_bin_path(char *bin, char *paths)
{
	char	*bin_path;
	char	*init_path;

	if (paths[0] != '/')
		bin_path = malloc(ft_strlen(bin) + ft_len_bef_col(paths) + 5);
	else
		bin_path = malloc(ft_strlen(bin) + ft_len_bef_col(paths) + 4);
	if (bin_path == NULL)
		return ((char *)3);
	init_path = bin_path;
	if (paths[0] != '/')
	{
		bin_path[0] = '~';
		bin_path[1] = '/';
		bin_path += 2;
	}
	ft_strncpy(paths, bin_path, ft_len_bef_col(paths) + 1);
	bin_path[ft_len_bef_col(paths) + 1] = '/';
	ft_strcpy(bin, bin_path + 2 + ft_len_bef_col(paths));
	if (paths[0] != '/')
		bin_path -= 1;
	return (init_path);
}

int	ft_len_bef_col(char *paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (paths[i] == ':')
			return (i - 1);
		i++;
	}
	return (i - 1);
}

char	*ft_find_bin(char *bin, char *paths, char **argv, char **envp)
{
	char	*bin_path;
	int		i;

	i = 0;
	(void)argv;
	while (*paths)
	{
		bin_path = ft_check_bin_path(bin, paths);
		if (bin_path == (char *)3)
			return (NULL);
		if (access(bin_path, F_OK & X_OK) == 0)
		{
			execve(bin_path, argv + 1, envp);
			return (bin_path);
		}
		else
			free(bin_path);
		paths += ft_len_bef_col(paths) + 1;
		if (*paths)
			paths += 1;
		i++;
	}
	return (NULL);
}

char	*ft_pipes(int ac, char **argv, t_dynarray *darr)
{
	int			pipefd[2];
	int			i;
	int			fd;

	i = 0;
	argv += 1;
	ac -= 1;
	fd = dup(STDIN_FILENO);
	pipe(pipefd);
	while (i < ac)
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			dup2(pipefd[1], STDOUT_FILENO);
			ft_find_bin(argv[1], ft_getenvval("PATH", darr.list, darr.nb_cells), argv, envp);
		}
		i++;
	}
}
