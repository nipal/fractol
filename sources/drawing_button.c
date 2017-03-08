/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_button.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 04:47:24 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/07 00:58:08 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

void		draw_slider(t_win *w, t_slider *s)
{
	double		dist;
	double		r;
	t_matrix	*mat_line;
	t_matrix	*pt1;
	t_matrix	*pt2;

	if (!(pt1 = vect_new_vertfd(s->border->x0
					, 0.5 * (s->border->y0 + s->border->y1), 0))
		|| !(pt2 = vect_new_vertfd(s->border->x1
					, 0.5 * (s->border->y0 + s->border->y1), 0))
		|| !(mat_line = init_mat_line(pt1, pt2, s->color, s->color)))
		return ;
	dist = abs(s->border->x1 - s->border->x0);
	r = s->border->y0 - s->border->y1;
	draw_line2(w, mat_line);
	matrix_free(&mat_line);
	pt1->m[0] = s->v1 * dist + s->border->x0;
	pt2->m[0] = s->v2 * dist + s->border->x0;
	paint_circle(pt1, s->color, r * 0.7, w);
	paint_circle(pt2, s->color, r * 0.7, w);
	matrix_free(&pt1);
	matrix_free(&pt2);
}

void		draw_the_sliders(t_win *w, t_slider **sliders)
{
	int	i;

	i = 0;
	while (sliders[i])
	{
		draw_slider(w, sliders[i]);
		i++;
	}
}
