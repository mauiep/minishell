#include "minishell.h"

int	ft_open_create(char *filename, bool apnd_or_not)
{
	int		fd;
	char	*pathname;
	char	*pathname2;
	char	buffer[10000];

	pathname = ft_strjoin(getcwd(buffer, 10000), "/");
	pathname2 = ft_strjoin(pathname, filename);
	free(pathname);
	dprintf(2, "PATHNAME2 = %s\n", pathname2);
	fd = open(pathname2, O_APPEND * apnd_or_not);
	if (fd == -1)
	{
		fd = open(pathname2, O_CREAT & O_APPEND * apnd_or_not);
		dprintf(2, "CREATING\n");
		if (fd == -1)
			return (-1);
	}
	return (fd);
}
