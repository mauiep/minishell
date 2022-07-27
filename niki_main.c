#include "minishell.h"

t_safe	g_vrac;

int	main(int ac, char **av, char **envp)
{
	char		*line_buffer;
	t_dynarray	darr;

	(void)av;
	if (ac != 1)
		return (-1);
	if (init_dyn_env(envp, &darr))
		return (-1);
	g_vrac.darr = &darr;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, sigd_handler);
	while (1)
	{
		line_buffer = readline("$admaupie>");
		if (line_buffer == NULL)
			return (free_dynarray(&darr), 0);
		add_history(line_buffer);
		printf("val = %s\n", ft_getenvval(line_buffer, darr.list, darr.nb_cells, 1));
		parse(line_buffer, &darr);
		free(line_buffer);
	}
	return (0);
}
