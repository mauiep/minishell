#include "minishell.h"

int	ft_cd(char *str, char *home)
{
	if (!str)
		return (-1);
	printf("str = %s\n", str);
	if (!*str)
	{
		if (home)
			chdir(home);
		else
			printf("HOME NOT SET\n");
	}
	else if (chdir(str) == -1)
		return (printf("%s does not exist\n", str), -1);
	return (0);
}

int	ft_unset(t_dynarray *darr, char *str)
{
	int	index;
	char	**envp;

	envp = darr->list;
	index = ft_getenv_index(envp, darr->nb_cells, str, 0);
	if (index != -1)
	{
		free(envp[index]);
		dynarray_extract(darr, index, 1);
	}
	else
		return (-1);
	return (0);
}

int	ft_export(t_dynarray *darr, char *str)
{
	int	index;
	char	**envp;
	char	*envpi;

	envp = darr->list;
	if (!ft_has_eq(str))
		return (0);
	index = ft_getenv_index(envp, darr->nb_cells, str, 1);
	if (index >= 0)
	{
		envpi = malloc(ft_strlen(str) + 1);
		ft_strcpy(str, envpi);
		free(envp[index]);
		envp[index] = envpi;
	}
	else if (index == -1)
	{
		envpi = malloc(ft_strlen(str) + 1);
		ft_strcpy(str, envpi);
		push_dynarray(darr, &envpi, 1, 0);
	}
	return (0);
}

void	ft_pwd()
{
	char	*pwd;

	pwd = NULL;
	if (!getcwd(pwd, 1000))
		printf("Unable to retrieve path\n");
	else
		printf("%s\n", pwd);
}

void	ft_echo(char **args)
{
	int	i;
	bool	flag;

	i = 0;
	flag = 0;
	if (args && args[0])
	{
		if (ft_strcmp(args[0], "-n"))
		{
				flag = 1;
				i++;
		}
		while (args[i])
		{
				printf("%s", args[i]);
				i++;
		}
	}
	if (!flag)
		printf("\n");
}
