/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_link_face.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 03:51:20 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 06:02:04 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "fdf.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

void	draw_face_map(t_env *e, t_matrix ***map, t_matrix *mat_l)
{
	int			j;
	int			i;
	t_matrix	*c;
	t_matrix	*c2;

	j = -1;
	while (++j < e->size_map_y)
	{
		i = -1;
		while (++i < e->size_map_x)
		{
			if (i <= e->size_map_x - 2 && j <= e->size_map_y - 2
				&& (c = e->color_map[j][i])
				&& (c2 = e->color_map[j + 1][i + 1])
				&& (mat_l = init_mat_line(map[j][i], map[j + 1][i + 1], c, c2))
				&& (c2 = e->color_map[j][i + 1])
				&& draw_triangle(e, mat_l, map[j][i + 1], c2) > -1
				&& (c2 = e->color_map[j + 1][i])
				&& draw_triangle(e, mat_l, map[j + 1][i], c2) > -1)
				;
			matrix_free(&mat_l);
		}
	}
}

void	draw_link_map(t_env *e, t_matrix ***map)
{
	int			j;
	int			i;
	t_matrix	*mat_l;
	t_matrix	*c1;
	t_matrix	*c2;

	j = -1;
	while (++j < e->size_map_y)
	{
		i = -1;
		while (++i < e->size_map_x)
		{
			c1 = e->color_map[j][i];
			if (i <= (e->size_map_x - 2) && (c2 = e->color_map[j][i + 1])
				&& (mat_l = init_mat_line(map[j][i], map[j][i + 1], c1, c2))
				&& (!ato(map[j][i], map[j][i + 1], e) || matrix_free(&mat_l))
				&& draw_line(e, mat_l) > -1 && matrix_free(&mat_l))
				;
			if (j <= (e->size_map_y - 2) && (c2 = e->color_map[j + 1][i])
				&& (mat_l = init_mat_line(map[j][i], map[j + 1][i], c1, c2))
				&& (!ato(map[j][i], map[j + 1][i], e) || matrix_free(&mat_l))
				&& draw_line(e, mat_l) && matrix_free(&mat_l))
				;
		}
	}
}

void	draw_link_map2(t_env *e, t_matrix ***map, t_matrix *c1, t_matrix *c2)
{
	int			j;
	int			i;
	t_matrix	*mat_l;

	j = 0;
	while (j < e->size_map_y)
	{
		i = 0;
		while (i < e->size_map_x)
		{
			if (i <= (e->size_map_x - 2)
				&& (mat_l = init_mat_line(map[j][i], map[j][i + 1], c1, c2))
				&& (!ato(map[j][i], map[j][i + 1], e) || matrix_free(&mat_l))
				&& draw_line(e, mat_l) > -1 && matrix_free(&mat_l))
				;
			if (j <= (e->size_map_y - 2)
				&& (mat_l = init_mat_line(map[j][i], map[j + 1][i], c1, c2))
				&& (!ato(map[j][i], map[j + 1][i], e) || matrix_free(&mat_l))
				&& draw_line(e, mat_l) && matrix_free(&mat_l))
				;
			i++;
		}
		j++;
	}
}
