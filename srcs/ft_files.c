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
	if (access(pathname2, F_OK)) /*no file found*/
	{
		fd = open(pathname2, O_RDWR | O_CREAT | O_APPEND * apnd_or_not, S_IRWXU);
		if (fd == -1)
			return (free(pathname2), dprintf(2, "Cannot create file\n"), 0);
	}
	else if (!access(pathname2, R_OK | W_OK)) /*ask if we can r/w on file*/
	{
		fd = open(pathname2, O_RDWR | O_APPEND * apnd_or_not);
		if (fd == -1)
			return (free(pathname2), dprintf(2, "Cannot Open File\n"));
	}
	else
		return (free(pathname2), dprintf(2, "File permission denied\n"));
	return (free(pathname2), fd);
}
