/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 14:38:59 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 23:18:49 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "fdf.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

t_matrix	**init_color_base(void)
{
	static	t_matrix	**color_base = NULL;
	int					i;

	if (!color_base)
	{
		if (!(color_base = (t_matrix**)malloc(sizeof(color_base) * 3)))
			return (NULL);
		i = -1;
		while (++i < 3)
			if (!(color_base[i] =
				vect_new_vertfd(255 * (i == 0),
				255 * (i == 1), 255 * (i == 2))))
				return (NULL);
	}
	return (color_base);
}

void		draw_base_cam(t_env *e, t_matrix *pt1, t_matrix *pt2)
{
	int			i;
	int			coef_base;
	t_matrix	*mat_line;
	t_matrix	**color_base;

	if (!(color_base = init_color_base())
		|| !(pt1 = matrix_init(1, 3))
		|| !(pt2 = matrix_init(1, 3)))
		return ;
	coef_base = 50;
	pt1->m[0] = -(e->ecr_x * 0.5) + 2 * coef_base;
	pt1->m[1] = -(e->ecr_y * 0.5) + 2 * coef_base;
	i = 0;
	while (i < 3)
	{
		pt2->m[0] = e->cam->base[i]->m[0] * coef_base + pt1->m[0];
		pt2->m[1] = e->cam->base[i]->m[1] * coef_base + pt1->m[1];
		if (!(mat_line = init_mat_line(pt1, pt2, color_base[i], color_base[i])))
			return ;
		draw_line(e, mat_line);
		matrix_free(&mat_line);
		i++;
	}
	matrix_free(&pt1);
	matrix_free(&pt2);
}

t_matrix	***copy_vect_map(t_env *e)
{
	int			i;
	int			j;
	t_matrix	***map;

	if (!(map = (t_matrix***)malloc(sizeof(t_matrix**) * e->size_map_y)))
		return (NULL);
	j = 0;
	while (j < e->size_map_y)
	{
		i = 0;
		if (!(map[j] = (t_matrix**)malloc(sizeof(t_matrix*) * e->size_map_x)))
			return (NULL);
		while (i < e->size_map_x)
		{
			map[j][i] = matrix_copy(e->vect_map[j][i]);
			i++;
		}
		j++;
	}
	return (map);
}

void		main_work(t_env *e)
{
	t_matrix	*color;
	t_matrix	*color2;
	t_matrix	***map;

	if (!(map = get_map(e)))
		return ;
	base_change(e, e->cam, map, NULL);
	e->vect_map = map;
	if (e->draw % 2 == 0)
		draw_link_map(e, e->vect_map);
	else
	{
		color = vect_new_vertfd(0, 0, 0);
		color2 = vect_new_vertfd(0, 0, 0);
		draw_face_map(e, e->vect_map, NULL);
		draw_link_map2(e, e->vect_map, color, color2);
		matrix_free(&color);
		matrix_free(&color2);
	}
	draw_base_cam(e, NULL, NULL);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_do_sync(e->mlx);
	free_map(&map, e);
}
