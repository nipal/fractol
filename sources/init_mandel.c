/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mandel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 01:09:44 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/10 07:31:39 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	-on va initialiser les variable de depart
**	-faire leuus fontion
*/

#include "fractol.h"
#include <mlx.h>

double	**init_data_tab(int size_x, int size_y)
{
	int		j;
	double	**tab;
	double	*data_line;

	if (!(tab = (double**)malloc(sizeof(double*) * (size_y)))
		|| !(data_line = (double*)malloc(sizeof(double) * (size_x * size_y))))
		return (NULL);
	j = 0;
	while (j < size_y)
	{
		tab[j] = data_line + (j * size_x);
		j++;
	}
	return (tab);
}

int		bcl_mandel(void)
{
	return (0);
}

int		init_mandel_event(t_win *w)
{
	mlx_hook(w->win, KEY_PRESS, (1 << 24) - 1, mandel_press_key, w);
	mlx_hook(w->win, KEY_RELEASE, (1 << 24) - 1, mandel_release_key, w);
	mlx_hook(w->win, BUTTON_PRESS, (1 << 24) - 1, mandel_press_button, w);
	mlx_hook(w->win, BUTTON_RELEASE, (1 << 24) - 1, mandel_release_button, w);
	mlx_hook(w->win, MOTION_NOTIFY, (1 << 24) - 1, mandel_motion_cursor, w);
	return (1);
}

int		init_mandel(t_env *e, int id)
{
	t_pt2d	max;

	e->idf = id;
	e->iter = ITER;
	if (!(e->mlx = mlx_init())
		|| !(e->fractal = window_init(e, SIZE_X, SIZE_Y, "fractal"))
		|| !(e->img_height = init_data_tab(SIZE_X2 + 8, SIZE_Y2 + 8))
		|| !(e->img_low = (double*)malloc(sizeof(double) * SIZE_X * SIZE_Y))
		|| !(init_mandel_event(e->fractal)))
		return (0);
	e->y_maxl = SIZE_Y;
	e->x_maxl = SIZE_X;
	max.x = e->x_maxl;
	max.y = e->y_maxl;
	e->zoom = ZOOM;
	e->zoom_finished = 1;
	e->ctx = 0.3;
	e->cty = -0.4;
	init_pos_ecr(e);
	calcul_grid(e->img_low, e->pos_low, max, e);
	set_color_fractal(e->fractal);
	mlx_put_image_to_window(e->mlx, e->fractal->win, e->fractal->img, 0, 0);
	actu_win(e->fractal);
	mlx_loop(e->mlx);
	return (0);
}
