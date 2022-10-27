#include "minishell.h"

void	sigintHandler(int sig)
{
	(void)sig;
	write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*ft_make_prompt(char *dir)
{
	char	*str;

	str = malloc(ft_strlen(dir) + 2);
	ft_strcpy(dir, str);
	ft_strcpy(" ", str + ft_strlen(dir));
	return (str);
}

char	*ft_get_dir(char *path)
{
	int	i;

	i = 0;
	if (!path)
		return (NULL);
	while (path[i])
		i++;
	i--;
	if (path[i] == '/' && path[i + 1] == '\0')
		return ("/");
	while (i >= 0)
	{
		if (path[i] == '/')
			return (path + i + 1);
		i--;
	}
	return (NULL);
}

int	ft_readline(t_dynarray *darr)
{
	char		*line;
	char		*prompt;
	char		pwd[1000];

	while (1)
	{
		prompt = ft_make_prompt(ft_get_dir(getcwd(pwd, 1000)));
		if (!prompt)
			return (printf("getcwd fail\n"), -1);
		line = readline(prompt);
		free(prompt);
		if (line == NULL || ft_strcmp(line, "exit") == 0)
			return (printf("exit\n"), 0);
		if (*line)
		{
			add_history(line);
			parse(line, darr);
		}
		free(line);
	}
	return (0);
}
