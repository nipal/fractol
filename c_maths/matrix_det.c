/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_det.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/14 00:25:54 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 18:56:39 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

double	matrix_det(t_matrix *a)
{
	int		i;
	int		j;
	double	d;

	if (!a)
		return (0);
	d = 0;
	j = -1;
	while (++j < a->y)
	{
		i = -1;
		while (++i < a->x)
		{
			d += a->m[i + j * a->x] * d;
		}
	}
	return (d);
}
