#include "minishell.h"

t_safe	g_vrac;

int	main(int ac, char **av, char **envp)
{
	t_dynarray	darr;

	(void)av;
	if (ac != 1)
		return (-1);
	if (init_dyn_env(envp, &darr) == -1)
		return (-1);
	g_vrac.darr = &darr;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, sigd_handler);
	printf("start darr.list = %p\n", darr.list);
	if (!ft_readline(&darr))
		return (ft_free_all(&darr), printf("RETURN MAIN\n"), 0);
}
