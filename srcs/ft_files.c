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
	fd = open(pathname2, O_RDWR | O_APPEND * apnd_or_not);
	if (fd == -1)
	{
		fd = open(pathname2, O_RDWR | O_CREAT | O_APPEND * apnd_or_not, S_IRWXU);
		if (fd == -1)
			return (free(pathname2), -1);
	}
	return (free(pathname2), fd);
}
