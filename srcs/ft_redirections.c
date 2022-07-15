#include "minishell.h"

char	*ft_open_file(char *filename)
{
	int	i;

	i = 0;
	if (open(filename) == -1)
		if (open(filename, O_CREAT) == -1)
			return (-1);
}

