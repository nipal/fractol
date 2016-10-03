/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 09:25:33 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/14 19:25:40 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

t_matrix	*matrix_copy(t_matrix *src)
{
	t_matrix	*copy;
	int			i;
	int			size;

	copy = NULL;
	if (src && !(copy = matrix_init(src->x, src->y)))
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
