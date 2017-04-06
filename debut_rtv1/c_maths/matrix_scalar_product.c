/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_scalar_product.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/14 00:25:54 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/07 15:24:47 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

t_matrix	*matrix_scalar_product(t_matrix *a, double d)
{
	int		i;
	int		size;

	if (!a)
		return (NULL);
	i = 0;
	size = a->x * a->y;
	while (i < size)
	{
		a->m[i] *= d;
		i++;
	}
	return (a);
}

t_matrix	*matrix_scalar_product_in(t_matrix *a, double d, t_matrix *to)
{
	int		i;
	int		size;

	if (!a || !to)
		return (NULL);
	i = 0;
	size = a->x * a->y;
	while (i < size)
	{
		to->m[i] = a->m[i] * d;
		i++;
	}
	return (to);
}

t_matrix	*matrix_scalar_product_new(t_matrix *a, double d)
{
	int			i;
	int			size;
	t_matrix	*result;

	if (!a || !(result = matrix_init(a->x, a->y)))
		return (NULL);
	i = 0;
	size = a->x * a->y;
	while (i < size)
	{
		result->m[i] = a->m[i] * d;
		i++;
	}
	return (result);
}
