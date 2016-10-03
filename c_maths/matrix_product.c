/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_product.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 08:27:05 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/27 08:27:08 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

void		matrix_product_in(t_matrix *a, t_matrix *b, t_matrix *c)
{
	int		i;
	int		j;
	int		k;

	if (!a || !b)
		return ;
	if (a->x != b->y)
		return ;
	j = -1;
	while (++j < c->y)
	{
		i = -1;
		while (++i < c->x)
		{
			k = -1;
			c->m[i + (j * c->x)] = 0;
			while (++k < a->x)
				c->m[i + (j * c->x)] +=
					a->m[k + (j * a->x)] * b->m[i + (k * b->x)];
		}
	}
}

t_matrix	*matrix_product(t_matrix *a, t_matrix *b)
{
	int			i;
	int			j;
	int			k;
	t_matrix	*c;

	if (!a || !b)
		return (NULL);
	if (a->x != b->y)
		return (NULL);
	if (!(c = matrix_init(b->x, a->y)))
		return (NULL);
	j = -1;
	while (++j < c->y)
	{
		i = -1;
		while (++i < c->x)
		{
			k = -1;
			while (++k < a->x)
				c->m[i + (j * c->x)] +=
					a->m[k + (j * a->x)] * b->m[i + (k * b->x)];
		}
	}
	return (c);
}
