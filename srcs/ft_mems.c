#include "dynarray.h"

void	ft_memset(void *mem, int c, int size)
{
	int	i;
	char	*ptr;

	if (!mem)
		return ;
	i = 0;
	ptr = (char *)mem;
	while (i < size)
	{
		ptr[i] = c;
		i++;
	}
}

void	ft_memcpy(void *dest, void *src, size_t size)
{
	char	*d;
	char	*s;

	d = dest;
	s = src;
	while (size--)
		*d++ = *s++;
}

void	ft_free_all(t_dynarray *darr)
{
	char		**env;
	uint64_t	i;

	i = 0;
	env = darr->list;
	while (i < darr->nb_cells)
	{
		free(env[i]);
		i++;
	}
	free_dynarray(darr);
	rl_clear_history();
}
