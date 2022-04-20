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
			dprintf(2, "BEFORE EXEC:\n      bin_path = %s, argv[0] = %s, argv[1] = %s, envp[0] = %s\n",
					bin_path, argv[0], argv[1], envp[0]);
			execve(bin_path, argv, envp);
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
	int			fd_in;
	pid_t		list[3];
	pid_t		main_pid;
	char		*nul;

	(void)ac;
	nul = NULL;
	main_pid = fork();
	if (main_pid != 0)
		return NULL;
	fd_in = dup(STDIN_FILENO);
	argv[2] = NULL;
	argv[5] = NULL;
	argv[8] = NULL;
	i = 0;
	while (i < ac / 3)
	{
		pipe(pipefd);
		main_pid = fork();
		list[i] = main_pid;
		if (main_pid == 0)
		{
			if (i != 0)
				dup2(fd_in, STDIN_FILENO);
			if ((i + 1) != ac / 3)
				dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			close(fd_in);
			push_dynarray(darr, &nul, 1, 0);
			ft_find_bin(argv[i * 3], ft_getenvval("PATH", darr->list, darr->nb_cells), &argv[i * 3], darr->list);
		}
		dup2(pipefd[0], fd_in);
		//close(pipefd[0]);
		//close(pipefd[1]);
		i++;
	}
	i = 0;
	int status = 0;
	while (i < ac / 3)
	{
		waitpid(list[i], &status, 0);
		i++;
	}
	return (NULL);
}
