/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_dot_product.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/14 00:25:54 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/07 18:33:32 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

t_matrix	*matrix_add(t_matrix *a, t_matrix *b)
{
	t_matrix	*c;
	int			i;
	int			size;

	if (!a || !b)
		return (NULL);
	if (a->x != b->x || a->y != b->y)
		return (NULL);
	if ((!(c = matrix_init(a->x, a->y))))
		return (NULL);
	size = c->x * c->y;
	i = 0;
	while (i < size)
	{
		c->m[i] = a->m[i] + b->m[i];
		i++;
	}
	return (c);
}

t_matrix	*matrix_add_in(t_matrix *a, t_matrix *b, t_matrix *c)
{
	int			i;
	int			size;

	if (!a || !b || !c)
		return (NULL);
	if (a->x != b->x || a->y != b->y)
		return (NULL);
	size = c->x * c->y;
	i = 0;
	while (i < size)
	{
		c->m[i] = a->m[i] + b->m[i];
		i++;
	}
	return (c);
}
