#include "minishell.h"

int	ft_open_file(char *filename)
{
	int	fd;

	fd = open(filename, 0);
	if (fd == -1)
	{
		fd = open(filename, O_CREAT);
		if (fd == -1)
			return (-1);
	}
	return (fd);
}

int	ft_write_file(
