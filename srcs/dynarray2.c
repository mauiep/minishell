/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarray2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikotikcho <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 13:28:59 by nikotikch         #+#    #+#             */
/*   Updated: 2022/04/03 16:32:48 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dynarray.h"

int	dynarray_realloc(t_dynarray *dynarray, size_t new_byte_size)
{
	void	*ptr;

	ptr = malloc(new_byte_size);
	if (!(ptr))
		return (-1);
	free(dynarray->tmp);
	dynarray->tmp = malloc(new_byte_size);
	if (!(dynarray->tmp))
	{
		free(ptr);
		return (-1);
	}
	ft_memcpy(ptr, dynarray->list, dynarray->cell_size * dynarray->nb_cells);
	free(dynarray->list);
	dynarray->list = ptr;
	dynarray->byte_size = new_byte_size;
	return (0);
}

int	dyn_insr(t_dynarray *darr, void *ncells, uint64_t index, uint64_t nb_ncells)
{
	uint64_t	cl_s;
	uint64_t	lf_cl_s;

	if (darr == NULL || index == 0)
		if ((push_dynarray(darr, ncells, nb_ncells, true)))
			return (-1);
	if (index == darr->nb_cells)
		if ((push_dynarray(darr, ncells, nb_ncells, false)))
			return (-1);
	if (index != darr->nb_cells && index != 0)
	{
		if (!ncells || index + 1 > darr->nb_cells || !nb_ncells)
			return (-1);
		cl_s = darr->cell_size;
		lf_cl_s = (darr->nb_cells - index) * cl_s;
		if ((darr->nb_cells + nb_ncells) * cl_s > darr->byte_size)
			if (dynarray_realloc(darr, (darr->nb_cells + nb_ncells) * cl_s))
				return (-1);
		ft_memcpy(darr->tmp, darr->list + (index * cl_s), lf_cl_s);
		ft_memcpy(darr->list + index * cl_s, ncells, nb_ncells * cl_s);
		ft_memcpy(darr->list + (index + nb_ncells) * cl_s, darr->tmp, lf_cl_s);
		darr->nb_cells += nb_ncells;
	}
	return (0);
}

int	dynarray_extract(t_dynarray *darr, uint64_t index, uint64_t nb_ext)
{
	void		*ptr;
	uint64_t	cell_size;

	if (!darr || !darr->nb_cells || !nb_ext
		|| index + 1 > darr->nb_cells || nb_ext + index > darr->nb_cells)
		return (-1);
	if (index == darr->nb_cells || index + nb_ext == darr->nb_cells)
		pop_dynarray(darr, nb_ext, false);
	else if (index == 0)
		pop_dynarray(darr, nb_ext, true);
	else
	{
		cell_size = darr->cell_size;
		ptr = darr->list + (index + nb_ext) * cell_size;
		ft_memcpy(darr->tmp, ptr, (darr->nb_cells - nb_ext - index) * cell_size);
		ft_memcpy(darr->list + index * cell_size, darr->tmp, nb_ext * cell_size);
		darr->nb_cells -= nb_ext;
	}
	return (0);
}

void	*dynacc(t_dynarray *darr, uint64_t index)
{
	if (darr == NULL || darr->list == NULL || index + 1 > darr->nb_cells)
		return (NULL);
	return (darr->list + index * darr->cell_size);
}
