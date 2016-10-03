/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_product.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 09:57:43 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 23:58:58 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

#define X 0
#define Y 1
#define Z 2

void		vector_product_in(t_matrix *a, t_matrix *b, t_matrix *result)
{
	if (!a || !b || !result)
	{
		return ;
	}
	if (MIN(a->x * a->y, b->x * b->y) < 3)
	{
		return ;
	}
	result->m[X] = (a->m[Y] * b->m[Z]) - (a->m[Z] * b->m[Y]);
	result->m[Y] = (a->m[Z] * b->m[X]) - (a->m[X] * b->m[Z]);
	result->m[Z] = (a->m[X] * b->m[Y]) - (a->m[Y] * b->m[X]);
}

t_matrix	*vector_product_s(t_matrix *a, t_matrix *b, int x, int y)
{
	t_matrix	*result;

	if (!a || !b || x * y < 3 || x < 0)
	{
		return (NULL);
	}
	if (MIN(a->x * a->y, b->x * b->y) < 3
		|| !(result = matrix_init(x, y)))
		return (NULL);
	vector_product_in(a, b, result);
	return (result);
}

t_matrix	*vector_product(t_matrix *a, t_matrix *b)
{
	t_matrix	*result;

	if (!a || !b)
	{
		return (NULL);
	}
	if (MIN(a->x * a->y, b->x * b->y) < 3
		|| !(result = matrix_init(3, 1)))
		return (NULL);
	vector_product_in(a, b, result);
	return (result);
}
