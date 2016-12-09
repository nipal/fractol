/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_koch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 06:15:10 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/04 22:53:55 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	0 <----> 1
**
**  0
**  ^
**  |
**  |
**  v
**	1
*/

static	inline	int	define_intersect(t_win *w, t_matrix *in, t_matrix *out
		, t_matrix *new_out)
{
	t_lim		l;
	double		coef[2];
	double		data[3];
	double		*new_v;
	t_matrix	diff;

	if (!w || !in || !out || !new_out)
		return (0);
	matrix_asembly(&diff, 1, 3, data);
	new_v = new_out->m;
	matrix_sub_in(out, in, &diff);
	l.h = (data[0] > 0) ? 1 : 0;
	l.v = (data[1] > 0) ? 1 : 0;
	coef[0] = (!data[0]) ? 0 : data[1] / data[0];
	coef[1] = (!data[1]) ? 0 : data[0] / data[1];
	new_v[0] = (data[1]) ? (l.v * w->size_y - in->m[1])
		* coef[1] + in->m[0] : -1;
	if (new_v[0] >= 1 && new_v[0] < w->size_x
			&& ((new_v[1] = l.v * w->size_y) == l.v * w->size_y))
		return (1);
	new_v[1] = (data[0]) ? (l.h * w->size_x - in->m[0])
		* coef[0] + in->m[1] : -1;
	new_v[0] = l.h * w->size_x;
	return ((new_v[1] < 0 || new_v[1] > w->size_y) ? 0 : 1);
}

static	inline	int	is_printable(t_win *w, double *pta, double *ptb)
{
	if (!w || !pta || !ptb)
		return (0);
	if ((pta[0] <= 0 && ptb[0] <= 0)
		|| (pta[1] <= 0 && ptb[1] <= 0)
		|| (pta[0] >= w->size_x && ptb[0] >= w->size_x)
		|| (pta[1] >= w->size_y && ptb[1] >= w->size_y))
		return (0);
	return (1);
}

static	inline	int	is_in_window(t_win *w, double *pt)
{
	if (pt[0] <= 0 || pt[1] <= 0 || pt[0] >= w->size_x || pt[1] >= w->size_y)
		return (0);
	return (1);
}

int					get_pos_to_draw(t_win *w, t_polygone *node, t_matrix *pos_a
		, t_matrix *pos_b)
{
	int		a_in;
	int		b_in;
	double	*pta;
	double	*ptb;

	if (!w || !node || !node->next || !pos_a || !pos_b)
		return (0);
	pta = node->pos->m;
	ptb = node->next->pos->m;
	a_in = is_in_window(w, pta);
	b_in = is_in_window(w, ptb);
	if ((a_in && matrix_copy_in(node->pos, pos_a))
		|| (b_in && define_intersect(w, node->next->pos, node->pos, pos_a)))
		;
	if ((b_in && matrix_copy_in(node->next->pos, pos_b))
		|| (a_in && define_intersect(w, node->pos, node->next->pos, pos_b)))
		;
	if (!a_in && !b_in && is_printable(w, pta, ptb))
	{
		if (!((define_intersect(w, node->next->pos, node->pos, pos_a))
			&& (define_intersect(w, node->pos, node->next->pos, pos_b))))
			return (0);
	}
	return (1);
}

void				zoom_border(t_border *b, double x, double y, double scale)
{
	b->x0 = (b->x0 - x) * scale + x;
	b->x1 = (b->x1 - x) * scale + x;
	b->y0 = (b->y0 - y) * scale + y;
	b->y1 = (b->y1 - y) * scale + y;
}
