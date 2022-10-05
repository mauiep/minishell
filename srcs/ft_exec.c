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
	if (!paths)
		if (access(bin, F_OK & X_OK) == 0)
			execve(bin, argv, envp);
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

int	ft_handle_exec(t_lst *lst, t_dynarray *darr, pid_t *list)
{
	int	i;

	i = 0;
	while (lst && lst->token != 1)
	{
		if (lst->token == 0 && lst->str != NULL)
		{
			list[i] = fork();
			if (list[i] == 0)
			{
				if (ft_find_bin(ft_splitargs(lst)[0], ft_getenvval("PATH", darr,
					darr->nb_cells, 1), ft_splitargs(lst), darr->list) == NULL) //A FINIR APRES
					return (dprintf(2, "BAD EXEC BAD\n"), -1);
			}
			i++;
		}
		lst = lst->next;
	}
	return (i);
}
