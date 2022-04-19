#include "minishell.h"
#include <signal.h>

t_safe	safe;

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

	(void)darr;
	while (1)
	{
		prompt = ft_make_prompt(ft_get_dir(getcwd(pwd, 1000)));
		if (!prompt)
			return (printf("getcwd fail\n"), -1);
		line = readline(prompt);
		free(prompt);
		if (line == NULL)
			return (0);
		if (ft_strcmp(line, "end") == 0)
			return (0);
		ft_cd(line, ft_getenvval("HOME", darr->list, darr->nb_cells));
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

	(void)ac;
	(void)argv;

	//printf("pwd = %s\n", getcwd(pwd, 100));
	if (init_dyn_env(envp, &darr))
		return (-1);
	safe.darr = &darr;
	signal(SIGINT, sigintHandler);
	signal(SIGQUIT, SIG_IGN);
	ft_readline(&darr);
	ft_free_all(&darr);
	return (0);
}
