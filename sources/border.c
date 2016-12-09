/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 04:58:27 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/07 01:04:32 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int						check_border_io(t_env *e, t_win *w, t_border *b)
{
	(void)e;
	if (mouse_in_border(b, w->mouse) && !mouse_in_border(b, w->prev_mouse))
		return (1);
	if (!mouse_in_border(b, w->mouse) && mouse_in_border(b, w->prev_mouse))
		return (-1);
	return (0);
}

void					init_koch_param_border(t_env *e, t_win *win_param)
{
	int	border;
	int	top;

	border = 5;
	top = MIN(win_param->size_y * 0.5, win_param->size_x * 0.5);
	e->border_b.x0 = border;
	e->border_b.y0 = top;
	e->border_b.x1 = win_param->size_x * 0.5 - border * 0.5;
	e->border_b.y1 = win_param->size_y - border;
	e->border_t.x0 = win_param->size_x * 0.5 + border * 0.5;
	e->border_t.y0 = top;
	e->border_t.x1 = win_param->size_x - border;
	e->border_t.y1 = win_param->size_y - border;
}

void					draw_border(t_win *w, t_border *border, t_matrix *color)
{
	t_matline	mat_line;
	t_matrix	*pt1;
	t_matrix	*pt2;

	if (!(pt1 = vect_new_vertfd(border->x0, border->y0, 0))
			|| !(pt2 = vect_new_vertfd(border->x0, border->y1, 1)))
		return ;
	mat_line.pt1 = pt1;
	mat_line.pt2 = pt2;
	mat_line.c1 = color;
	mat_line.c2 = color;
	draw_line3(&mat_line, w);
	pt2->m[0] = border->x1;
	pt2->m[1] = border->y0;
	draw_line3(&mat_line, w);
	pt1->m[0] = border->x1;
	pt1->m[1] = border->y1;
	draw_line3(&mat_line, w);
	pt2->m[0] = border->x0;
	pt2->m[1] = border->y1;
	draw_line3(&mat_line, w);
	matrix_free(&pt1);
	matrix_free(&pt2);
}

int						mouse_in_border(t_border *bor, t_matrix *mouse)
{
	if (!bor || !mouse || mouse->m[0] < bor->x0 || mouse->m[0] > bor->x1
			|| mouse->m[1] < bor->y0 || mouse->m[1] > bor->y1)
		return (0);
	return (1);
}

void					draw_the_2_border(t_env *e)
{
	t_matrix	*color;

	if (!(color = tsl_to_rvb_new(120, (mouse_in_border(&((e->border_b))
							, e->param->mouse) ? 0.8 : 0.3), 0.8)))
		return ;
	matrix_free(&color);
	draw_border(e->param, &(e->border_b), color);
	if (!(color = tsl_to_rvb_new(250, (mouse_in_border((&(e->border_t))
							, e->param->mouse) ? 0.8 : 0.3), 0.8)))
		return ;
	draw_border(e->param, &(e->border_t), color);
	matrix_free(&color);
}
