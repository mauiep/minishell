#include "../minishell.h"

char	*ft_check_bin_path(char *bin, char *paths)
{
	char	*bin_path;
	char	*init_path;

	if (paths[0] != '/')
		bin_path = malloc(ft_strlen(bin) + ft_len_bef_col(paths) + 5);
	else
		bin_path = malloc(ft_strlen(bin) + ft_len_bef_col(paths) + 4);
	if (bin_path == NULL)
		return ((char *)NULL);
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
	//printf("init path = %s addr=%p\n", init_path, init_path);
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
	if (!paths) //DANGEROUS??
		return (NULL);
	//	if (access(bin, F_OK & X_OK) == 0)
	//		execve(bin, argv, envp);
	while (*paths)
	{
		bin_path = ft_check_bin_path(bin, paths);
		if (bin_path == (char *)3)
			return (NULL);
		if (access(bin_path, F_OK & X_OK) == 0)
		{
			dprintf(2, "argv[0] = %s, argv[1] = %s, envp[0] = %s\n",
					argv[0], argv[1], envp[0]);
			execve(bin_path, argv, NULL);
			perror("execve");
			free(bin_path);
			return ((char *)1);
		}
		else
			free(bin_path);
		paths += ft_len_bef_col(paths) + 1;
		if (*paths)
			paths += 1;
		i++;
	}
	return ((char *)0);
}

int	ft_handle_exec(t_lst *lst, t_mini *data)
{
	char	**args;
	char	*tmp;

	dprintf(2, "BEFORE SPLITARGS\nlst->str = %s\n", lst->str);
	args = ft_splitargs(lst);
	while (args && lst && lst->token != 1)
	{
		if (lst->token == 0 && lst->str != NULL)
		{
			//ici faire un strcmp de la str avec les builtins et si > 0 lancer le builtin associe
			tmp = ft_find_bin(args[0], ft_get_env_var("PATH", data), args, data->env_tab);
			if (!tmp)
				return (dprintf(2, "ft bin return 0\n"), -1);
		}
		lst = lst->next;
	}
	return (0);
}
