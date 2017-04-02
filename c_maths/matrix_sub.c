/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 02:19:40 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/02 20:45:49 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

int			matrix_sub_in(t_matrix *a, t_matrix *b, t_matrix *c)
{
	int			i;
	int			size;

	if (!a || !b || !c)
		return (0);
	if (a->x != b->x || a->y != b->y || c->x != a->x || c->y != a->y)
		return (0);
	size = c->x * c->y;
	i = 0;
	while (i < size)
	{
		c->m[i] = a->m[i] - b->m[i];
		i++;
	}
	return (1);
}

t_matrix	*matrix_sub(t_matrix *a, t_matrix *b)
{
	t_matrix	*c;
	int			i;
	int			size;

	if (!a || !b || a->x != b->x || a->y != b->y)
		return (NULL);
	if (!(c = matrix_init(a->x, a->y)))
		return (NULL);
	size = c->x * c->y;
	i = 0;
	while (i < size)
	{
		c->m[i] = a->m[i] - b->m[i];
		i++;
	}
	return (c);
}
