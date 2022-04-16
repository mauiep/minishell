#include "minishell.h"

int	ft_strcpy(char *str, char *str2)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str2[i] = str[i];
		i++;
	}
	str2[i] = '\0';
	return (0);
}

int	ft_strcmp(char *str, char *str2)
{
	int	i;

	i = 0;
	while (str[i] && str2[i])
	{
		if (str[i] != str2[i])
			return (-1);
		i++;
	}
	return (0);
}

bool	ft_has_eq(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i != 0 && str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strncpy(char *str, char *str2, int n)
{
	int	i;

	i = 0;
	while (str[i] && i < n)
	{
		str2[i] = str[i];
		i++;
	}
	str2[i] = '\0';
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
