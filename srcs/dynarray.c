/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikotikcho <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 18:11:57 by nikotikch         #+#    #+#             */
/*   Updated: 2022/04/03 16:34:01 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dynarray.h"

int	init_dynarray(t_dynarray *dynarray, uint64_t nb_cells, size_t cell_size)
{	
	if (dynarray == NULL || cell_size == 0)
		return (-1);
	ft_memset(dynarray, 0, sizeof(t_dynarray));
	dynarray->byte_size = cell_size * nb_cells;
	dynarray->list = malloc(dynarray->byte_size);
	if (!(dynarray->list))
		return (-1);
	dynarray->tmp = malloc(dynarray->byte_size);
	if (!(dynarray->tmp))
	{
		free(dynarray->list);
		return (-1);
	}
	if (nb_cells == 0)
		dynarray->byte_size = 1;
	dynarray->cell_size = cell_size;
	return (0);
}

void	clear_dynarray(t_dynarray *dynarray)
{
	if (dynarray == NULL)
		return ;
	dynarray->nb_cells = 0;
}

void	free_dynarray(t_dynarray *dynarray)
{
	if (dynarray == NULL)
		return ;
	if (dynarray->list != NULL)
	{
		free(dynarray->list);
		dynarray->list = NULL;
	}
	if (dynarray->tmp != NULL)
	{
		free(dynarray->tmp);
		dynarray->tmp = NULL;
	}
	ft_memset(dynarray, 0, sizeof(t_dynarray));
}

int	pop_dynarray(t_dynarray *dynarray, uint64_t nb_cells_pop, bool way)
{
	void	*ptr;
	size_t	size;

	if (nb_cells_pop > dynarray->nb_cells || !dynarray || !nb_cells_pop)
		return (-1);
	if (way == true)
	{
		size = dynarray->byte_size - dynarray->cell_size * nb_cells_pop;
		ptr = dynarray->list + dynarray->cell_size * nb_cells_pop;
		ft_memcpy(dynarray->tmp, ptr, size);
		ptr = dynarray->list;
		dynarray->list = dynarray->tmp;
		dynarray->tmp = ptr;
	}
	dynarray->nb_cells -= nb_cells_pop;
	return (0);
}

int	push_dynarray(t_dynarray *darr, void *new_cells, uint64_t nb_ncells,
				bool way)
{
	uint64_t	nb_cells;
	uint64_t	new_size;

	if (!darr || !new_cells || !nb_ncells || !darr->list || !darr->tmp)
		return (-1);
	nb_cells = darr->nb_cells;
	new_size = nb_ncells * darr->cell_size;
	if ((nb_cells + nb_ncells) * darr->cell_size > darr->byte_size)
		if (dynarray_realloc(darr, (nb_cells + nb_ncells) * darr->cell_size))
			return (-1);
	if (way)
	{
		ft_memcpy(darr->tmp, darr->list, nb_cells * darr->cell_size);
		ft_memcpy(darr->list, new_cells, new_size);
		ft_memcpy(darr->list + new_size, darr->tmp, nb_cells * darr->cell_size);
	}
	else
		ft_memcpy(darr->list + nb_cells * darr->cell_size, new_cells, new_size);
	darr->nb_cells += nb_ncells;
	return (0);
}
