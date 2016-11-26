/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_koch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 06:15:10 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/26 18:55:22 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
static	inline	double	solve_deg1(double x0, double coef)
{
	if (coef == 0)
		return (-1);
	return (x0 / coef);
}
*/

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


static	inline	int	define_intersect(t_win *w, t_matrix *in, t_matrix *out, t_matrix *new_out)
{
	int			v;
	int			h;
	double		coef[2];
	double		data[3];
	double		*new_v;
	t_matrix	diff;

	if (!w || !in || !out || !new_out)
		return (0);
	diff.x = 1;
	diff.y = 3;
	diff.m = data;
	new_v = new_out->m;
	matrix_sub_in(out, in, &diff);
	h = (data[0] > 0) ? 1 : 0;
	v = (data[1] > 0) ? 1 : 0;
	coef[0] = (!data[0]) ? 0 : data[1] / data[0];
	coef[1] = (!data[1]) ? 0 : data[0] / data[1];
	new_v[0] = (data[1]) ? (v * w->size_y - in->m[1]) * coef[1] + in->m[0]: -1;
	if (new_v[0] >= 0 && new_v[0] < w->size_x)
		new_v[1] = v * w->size_y;
	else
	{
		new_v[1] = (data[0]) ? (h * w->size_x - in->m[0]) * coef[0] + in->m[1]: -1;
		new_v[0] = h * w->size_x;
		return ((new_v[1] < 0 || new_v[1] > w->size_y) ? 0: 1);
	}
	return (1);	
}

static	inline	int	is_printable(t_win *w, double *pta, double *ptb)
{
	if (!w || !pta || !ptb)
		return (0);
	if ((pta[0] <= 0 && ptb[0] <= 0)
		|| (pta[1] <= 0 && ptb[1] <= 0)
		|| (pta[0] >= w->size_x && ptb[0] >=  w->size_x)
		|| (pta[1] >= w->size_y && ptb[1] >=  w->size_y))
		return (0);
	return (1);
}

static	inline	int is_in_window(t_win *w, double *pt)
{
	if (pt[0] <= 0 || pt[1] <= 0 || pt[0] >= w->size_x || pt[1] >= w->size_y)
		return (0);
	return (1);
}

int		get_pos_to_draw(t_win *w, t_polygone *node, t_matrix *pos_a, t_matrix *pos_b)
{
	int		a_inside;
	int		b_inside;
//	int		traversed;
	double	*pta;
	double	*ptb;

//	printf("il est passer par ici\n");
	if (!w || !node || !node->next || !pos_a || !pos_b)
	{
		printf("you go fucked\n");
		return (0);
	}
	pta = node->pos->m;
	ptb = node->next->pos->m;
	a_inside = is_in_window(w, pta);
	b_inside = is_in_window(w, ptb);

	
//	matrix_copy_in(node->pos, pos_a);
//	matrix_copy_in(node->next->pos, pos_b);
//*
	
	if (a_inside)
		matrix_copy_in(node->pos, pos_a);
	else if (b_inside)
		define_intersect(w, node->next->pos, node->pos, pos_a);

	if (b_inside)
		matrix_copy_in(node->next->pos, pos_b);
	else if (a_inside)
		define_intersect(w, node->pos, node->next->pos, pos_b);

	if (!a_inside && !b_inside && is_printable(w, pta, ptb))
	{
		if (!(define_intersect(w, node->next->pos, node->pos, pos_a)))
			return (0);
		if (!(define_intersect(w, node->pos, node->next->pos, pos_b)))
			return (0);
	}
//	*/
//	is_printable(NULL, NULL, NULL);
//	define_intersect(NULL, NULL, NULL, NULL);
	return (1);
}

void	zoom_border(t_border *b, double x, double y, double scale)
{
	b->x0 = (b->x0 - x) * scale + x;
	b->x1 = (b->x1 - x) * scale + x;
	b->y0 = (b->y0 - y) * scale + y;
	b->y1 = (b->y1 - y) * scale + y;
}
