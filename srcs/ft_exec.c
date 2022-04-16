#include "minishell.h"

char	*ft_check_bin_path(char *bin, char *paths)
{
	char	*bin_path;

	if (paths[0] != '/')
		bin_path = malloc(ft_strlen(bin) + ft_len_bef_col(paths) + 5);
	else
		bin_path = malloc(ft_strlen(bin) + ft_len_bef_col(paths) + 4);
	if (bin_path == NULL)
		return ((char *)3);
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
	return (bin_path);
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
	char *bin_path;
	int		i;

	i = 0;
	(void)argv;
	while (*paths)
	{
		bin_path = ft_check_bin_path(bin, paths);
		printf("bin_path = %s\n", bin_path);
		printf("paths = %s\n", paths);
		if (bin_path == (char *)3)
			return (NULL);
		if (access(bin_path, F_OK & X_OK) == 0)
		{
			printf("EXECUTING\n");
			execve(bin_path, argv, envp);
			break;
		}
		paths += ft_len_bef_col(paths) + 1;
		if (*paths)
			paths += 1;
		i++;
	}
	return (paths);
}
