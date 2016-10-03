/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/14 00:25:54 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 18:56:44 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"
#include <stdio.h>

t_matrix	*matrix_init(int x, int y)
{
	t_matrix	*mat;
	double		*m;
	int			i;
	int			max;

	max = x * y;
	if (!(mat = malloc(sizeof(t_matrix))))
		return (NULL);
	if (!(m = malloc(sizeof(double) * max)))
		return (NULL);
	mat->x = x;
	mat->y = y;
	mat->m = m;
	i = 0;
	while (i < max)
	{
		mat->m[i] = 0;
		i++;
	}
	return (mat);
}
