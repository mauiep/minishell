#include "minishell.h"

int	init_dyn_env(char **envp, t_dynarray *darr)
{
	int		i;
	char	*str;

	i = 0;
	while (envp[i])
		i++;
	init_dynarray(darr, i, sizeof(char*)); // A SECURE
	i = 0;
	while (envp[i])
	{
		str = malloc(ft_strlen(envp[i]) + 1);
		ft_strcpy(envp[i], str);
		push_dynarray(darr, &str, 1, 0);
		i++;
	}
	return (0);
}

int	ft_getenv_index(char **envp, uint64_t len, char *str, bool un_exp)
{
	uint64_t	i;
	int			cmp;

	i = 0;
	while (i < len)
	{
		//printf("envp[%ld] = %s, str = %s\n", i, envp[i], str);
		cmp = ft_envcmp(envp[i], str);
		if (cmp == -1)
			i++;
		else if (cmp == -2)
		{
			if (un_exp == 0)
				return (i);
			else
				return (-2);
		}
		else
			return (i);
	}
	return (-1);
}

int	ft_envcmp(char *str, char *str2)
{
	int	i;

	i = 0;
	while (str[i] && str2[i] && str[i] != '=' && str2[i] != '=')
	{
		if (str[i] != str2[i])
			return (-1);
		i++;
	}
	if (str[i] == '=' && str2[i] == '=')
		return (0);
	else
		return (-2);
}

char	*ft_getenvval(char *str, char **envp, uint64_t len)
{
	int	i;
	int	index;

	i = 0;
	index = ft_getenv_index(envp, len, str, 0);
	printf("index = %d\n", index);
	if (index == -1)
		return (NULL);
	printf("envp[%d] = %s\n", index, envp[index]);
	while (envp[index][i] && envp[index][i] != '=')
		i++;
	return (&envp[index][i + 1]);
}
