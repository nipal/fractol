/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 09:25:33 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/10 10:02:57 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

t_matrix	*matrix_copy(t_matrix *src)
{
	t_matrix	*copy;
	int			i;
	int			size;

	copy = NULL;
	if (!src || !(copy = matrix_init(src->x, src->y)))
		return (NULL);
	i = 0;
	copy->x = src->x;
	copy->y = src->y;
	size = src->x * src->y;
	while (i < size)
	{
		copy->m[i] = src->m[i];
		i++;
	}
	return (copy);
}

t_matrix	*matrix_copy_in(t_matrix *src, t_matrix *copy)
{
	int			i;
	int			size;

	if (!src || !copy || copy->x != src->x || copy->y != src->y)
	{
		(!src) ? ft_putstr("no src\n") : 0;
		(!copy) ? ft_putstr("no copy\n") : 0;
		(copy && src && copy->x != src->x) ? ft_putstr("size_x diff\n") : 0;
		(copy && src && copy->y != src->y) ? ft_putstr("size_y diff\n") : 0;
		return (NULL);
	}
	i = 0;
	size = src->x * src->y;
	while (i < size)
	{
		copy->m[i] = src->m[i];
		i++;
	}
	return (copy);
}
