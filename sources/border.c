/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 04:58:27 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/27 21:12:37 by fjanoty          ###   ########.fr       */
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

/*
**	visiblement les bordure sont paremetrer en dure
**	on va voir sa change quelauechose d'en rajouter une, si j'ai bien fait
**	les choses ca devrai le faire
*/
void					init_koch_param_border(t_env *e, t_win *win_param)
{
	int		border;
	int		top;
	double	nb_bord;

	nb_bord = 3;
	border = 5;
	top = MIN(win_param->size_y * 0.5, win_param->size_x * 0.5);

	e->border_b.x0 = border;
	e->border_b.x1 = win_param->size_x * (1.0 / nb_bord) - border * (0.5);
	e->border_b.y0 = top;
	e->border_b.y1 = win_param->size_y - border;

	e->border_t.x0 = win_param->size_x * (1.0 / nb_bord) + border * (0.5);
	e->border_t.x1 = win_param->size_x * (2.0 / nb_bord) - border * (0.5);
	e->border_t.y0 = top;
	e->border_t.y1 = win_param->size_y - border;

	e->border_p.x0 = win_param->size_x * (2.0 / nb_bord) + border * (0.5);
	e->border_p.x1 = win_param->size_x * (3.0 / nb_bord) - border * (0.5);
	e->border_p.y0 = top;
	e->border_p.y1 = win_param->size_y - border;
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
	if (!bor || !mouse || !mouse->m
		|| mouse->m[0] < bor->x0
		|| mouse->m[0] > bor->x1
		|| mouse->m[1] < bor->y0
		|| mouse->m[1] > bor->y1)
		return (0);
	return (1);
}

void					draw_the_2_border(t_env *e)
{
	t_matrix	*color;

//	bordure pour la base
	if (!(color = tsl_to_rvb_new(120, (mouse_in_border(&((e->border_b))
							, e->param->mouse) ? 0.8 : 0.3), 0.8)))
		return ;
	draw_border(e->param, &(e->border_b), color);
	matrix_free(&color);

//	bordure pour la transformation
	if (!(color = tsl_to_rvb_new(250, (mouse_in_border((&(e->border_t))
							, e->param->mouse) ? 0.8 : 0.3), 0.8)))
		return ;
	draw_border(e->param, &(e->border_t), color);
	matrix_free(&color);

//	bordure pour la transformation
	if (!(color = tsl_to_rvb_new(200, 0.6, (mouse_in_border((&(e->border_p))
							, e->param->mouse) ? 0.6 : 0.8))))
		return ;
	draw_border(e->param, &(e->border_p), color);
	matrix_free(&color);
}

t_border	*creat_border(int x0, int x1, int y0, int y1)
{
	t_border	*b;

	if ((b = (t_border*)malloc(sizeof(t_border))))
		return (NULL);
	b->x0 = x0;
	b->x1 = x1;
	b->y0 = y0;
	b->y1 = y1;
	return (b);
}

void		init_border(t_border *b, int x0, int x1, int y0, int y1)
{
	if (!b)
		return ;
	b->x0 = x0;
	b->x1 = x1;
	b->y0 = y0;
	b->y1 = y1;
}

