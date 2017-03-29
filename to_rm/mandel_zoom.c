/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel_zoom.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 22:57:11 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/05 06:32:24 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		do_the_zoom_simple(t_env *e, int x, int y, double mult)
{
	t_pt2d	max;
	t_pt2d	size;

	size.x = x;
	size.y = y;
	max.x = e->x_maxl;
	max.y = e->y_maxl;
	resize_window(e->pos_low, mult, size, e);
	calcul_grid(e->img_low, e->pos_low, max, e);
	set_color_fractal(e->fractal);
	return (1);
}

int		do_the_translation(t_env *e, double ux, double uy)
{
	double	add_x;
	double	add_y;

	add_x = (e->pos_low[2] - e->pos_low[0]) * ux;
	add_y = (e->pos_low[3] - e->pos_low[1]) * uy;
	e->pos_low[0] += add_x;
	e->pos_low[2] += add_x;
	e->pos_low[1] += add_y;
	e->pos_low[3] += add_y;
	return (1);
}
