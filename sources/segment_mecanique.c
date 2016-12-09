/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_mecanique.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 20:02:23 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/07 00:12:50 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		set_2d_landmark_incpy(t_matrix *diff, t_matrix *dx, t_matrix *dy
			, double *dist)
{
	if (!diff || !dx || !dy || !dist)
		return ;
	*dist = sqrt(matrix_dot_product(diff, diff));
	matrix_scalar_product(diff, 1.0 / *dist);
	dx->m[0] = diff->m[0];
	dx->m[1] = diff->m[1];
	dy->m[0] = dx->m[1];
	dy->m[1] = -dx->m[0];
}

double		min_fabs(double a, double b)
{
	a = (a < 0) ? -a : a;
	b = (a < 0) ? -b : b;
	return ((a < b) ? a : b);
}

double		max_fabs(double a, double b)
{
	a = (a < 0) ? -a : a;
	b = (a < 0) ? -b : b;
	return ((a > b) ? a : b);
}

double		set_dist_sepc(double *data, t_matrix *dx, t_matrix *dy
		, t_polygone *node)
{
	t_matrix	*pos;
	t_matrix	*inter;
	double		dist;
	double		distx_2;

	if (!data || !dx || !dy || !node || !node->next
			|| !(pos = vect_new_vertfd(data[2], data[3], 0))
			|| !(inter = matrix_sub(pos, node->pos)))
		return (2147483647);
	data[0] = matrix_dot_product(dx, inter);
	data[1] = matrix_dot_product(dy, inter);
	if (matrix_free(&inter) && !(inter = matrix_sub(pos, node->next->pos)))
		return (2147483647);
	dx->m[0] *= -1;
	dx->m[1] *= -1;
	distx_2 = matrix_dot_product(dx, inter);
	if ((fabs(data[0]) >= data[6] || fabs(distx_2) >= data[6])
		&& ((data[0] = min_fabs(data[0], distx_2)) >= 0))
		dist = max_fabs(data[0], data[1]);
	else
		dist = fabs(data[1]);
	matrix_free(&pos);
	matrix_free(&inter);
	return (dist);
}

void		draw_prewiew(t_win *w)
{
	t_polygone	*close_node;
	t_polygone	*cpy;

	close_node = NULL;
	if (mouse_in_border(&(w->e->border_b), w->mouse))
		close_node = get_cluster_seg(w->e->base_model
					, w->mouse->m[0], w->mouse->m[1]);
	else if (mouse_in_border(&(w->e->border_t), w->mouse))
		close_node = get_cluster_seg(w->e->trans_model
					, w->mouse->m[0], w->mouse->m[1]);
	if (!close_node)
		return ;
	if (!(cpy = copy_node(close_node, 0))
		|| !(cpy->next = copy_node(w->e->actif, 0))
		|| !(cpy->next->next = copy_node(close_node->next, 0)))
		return ;
	set_in_grey(cpy, 150);
	draw_simple_polygone(w, cpy);
	polygone_destroy(&cpy);
}
