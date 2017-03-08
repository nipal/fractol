/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone_transfrom.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 18:35:03 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/10 07:27:28 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double						dist_to_end(t_polygone *seg)
{
	t_polygone	*last;
	double		dist;

	dist = -1;
	if (seg && (last = get_last(seg)))
	{
		dist = matrix_dot_product(seg->pos, seg->pos);
		dist += matrix_dot_product(last->pos, last->pos);
		dist = sqrt(dist);
	}
	return (dist);
}

t_polygone					*adate_to_unite(t_matrix *ux, t_matrix *uy
		, t_matrix *org, t_polygone *src)
{
	t_polygone	*node;
	t_matrix	*pos;

	if (!(node = (t_polygone*)malloc(sizeof(t_polygone)))
		|| !(node->pos = matrix_init(1, 3))
		|| !(node->col = matrix_copy(src->col))
		|| !(pos = matrix_sub(src->pos, org)))
		return (NULL);
	node->lvl = src->lvl;
	node->pos->m[0] = matrix_dot_product(ux, pos) + org->m[0];
	node->pos->m[1] = matrix_dot_product(uy, pos) + org->m[1];
	matrix_free(&pos);
	return (node);
}

/*
**	on defini la "matrice" de transformation d'un segment
*/

static	inline	t_polygone	*bcl_transform(t_matrix *unite_x
		, t_matrix *unite_y, t_polygone *seg_beg, double dist)
{
	t_polygone	*unite_beg;
	t_polygone	*node_u;
	t_polygone	*node_s;

	node_s = seg_beg;
	unite_beg = NULL;
	while (node_s->next && (node_s->next)->next)
	{
		if (!(node_u = adate_to_unite(unite_x, unite_y, seg_beg->pos
						, node_s->next)))
			return (NULL);
		node_u->pos->m[0] /= dist * dist;
		node_u->pos->m[1] /= dist * dist;
		node_u->next = NULL;
		push_back(&unite_beg, node_u);
		node_s = node_s->next;
	}
	return (unite_beg);
}

t_polygone					*transform(t_polygone *seg_beg)
{
	double		dist;
	t_polygone	*seg_end;
	t_polygone	*unite_beg;
	t_matrix	*unite_x;
	t_matrix	*unite_y;

	seg_end = get_last(seg_beg);
	if (!seg_beg || !(unite_x = matrix_sub(seg_end->pos, seg_beg->pos))
		|| !(unite_y = matrix_init(1, 3))
		|| !(dist = matrix_dot_product(unite_x, unite_x)))
		return (NULL);
	dist = sqrt(dist);
	unite_y->m[0] = unite_x->m[1];
	unite_y->m[1] = -unite_x->m[0];
	unite_beg = bcl_transform(unite_x, unite_y, seg_beg, dist);
	matrix_free(&unite_x);
	matrix_free(&unite_y);
	return (unite_beg);
}
