#include "minishell.h"

int	ft_open_create(char *filename, bool apnd_or_not)
{
	int	fd;

	fd = open(filename, O_APPEND * apnd_or_not);
	if (fd == -1)
	{
		fd = open(filename, O_CREAT & O_APPEND * apnd_or_not);
		if (fd == -1)
			return (-1);
	}
	return (fd);
}
