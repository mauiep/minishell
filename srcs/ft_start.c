#include "minishell.h"

int	ft_complete_env(t_dynarray *darr)
{
	char	*str;
	char	*path;

	if (ft_getenv_index(darr, darr->nb_cells, "PWD", 0) == -1)
	{
		path = ft_get_dir(getcwd(pwd, 1000));
		if (path == NULL)
			return (-1);
		str = ft_strjoin("PWD", path);
		free(path);
		if (str == NULL);
			return (-1);
		if (ft_export(darr, str) == -1); 
			return (free(str), -1);
	}
}
