/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:57:02 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 22:55:06 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	define_color(t_matrix *point, t_matrix *color)
{
	if (point && color)
	{
		color->m[R] = 100;
		color->m[G] = 100;
		color->m[B] = 128 - 2 * point->m[Z];
	}
}

void	get_point(t_matrix ***map, t_matrix **point, int i, int j)
{
	int	k;

	if (!(point[0] = (i < 10 && j < 10) ? matrix_copy(map[j][i]) : NULL)
		|| !(point[1] = (i < 9 && j < 10) ? matrix_copy(map[j][i + 1]) : NULL)
		|| !(point[2] = (j < 9 && i < 10) ? matrix_copy(map[j + 1][i]) : NULL)
		|| !(point[3] =
			(j < 9 && i < 9) ? matrix_copy(map[j + 1][i + 1]) : NULL))
		;
	k = 0;
	while (k < 4)
	{
		if (point[k])
			define_color(point[k], point[k + 4]);
		else
			point[k] = NULL;
		k++;
	}
}
