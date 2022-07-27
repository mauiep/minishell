#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*line_buffer;
	t_dynarray	darr;

	(void)av;
	if (ac != 1)
		return (-1);
	if (init_dyn_env(envp, &darr))
		return (-1);
	while (1)
	{
		line_buffer = readline("$admaupie>");
		if (line_buffer == NULL)
			return (0);
		add_history(line_buffer);
		printf("val = %s\n", ft_getenvval(line_buffer, darr.list, darr.nb_cells, 1));
		parse(line_buffer, &darr);
		free(line_buffer);
	}
	return (0);
}
