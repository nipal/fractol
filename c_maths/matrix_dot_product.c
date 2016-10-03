/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_dot_product.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 02:36:17 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/15 09:18:24 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

double	matrix_dot_product(t_matrix *a, t_matrix *b)
{
	double	sum;
	int		i;
	int		size;

	if (a->x * a->y != b->y * b->x)
		return (0);
	i = 0;
	sum = 0;
	size = a->x * a->y;
	while (i < size)
	{
		sum += a->m[i] * b->m[i];
		i++;
	}
	return (sum);
}
