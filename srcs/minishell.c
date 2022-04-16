#include "minishell.h"
#include <signal.h>

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
	while (i > 0)
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

	(void)darr;
	prompt = ft_make_prompt(ft_get_dir(getcwd(pwd, 1000)));
	if (!prompt)
		return (printf("getcwd fail\n"), -1);
	while (1)
	{
		line = readline(prompt);
		ft_cd(line);
		ft_dyn_env(darr);
		prompt = ft_make_prompt(ft_get_dir(getcwd(pwd, 1000)));
		if (!prompt)
			return (printf("getcwd fail\n"), -1);
		if (line && *line)
			add_history(line);
		else
			break;
	}
	return (0);
}

int	main(int ac, char **argv, char **envp)
{
	t_dynarray	darr;
	int			pid;
	int			pipefd[2];

	(void)ac;
	(void)argv;

	//printf("pwd = %s\n", getcwd(pwd, 100));
	init_dyn_env(envp, &darr);
	ft_export(&darr, "NIKI=BOSS");
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		ft_find_bin("ls", ft_getenvval("PATH", darr.list, darr.nb_cells), argv, envp);
	}
	return (0);
}
