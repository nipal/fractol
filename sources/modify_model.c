/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_model.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 07:00:18 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/05 11:14:55 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <mlx.h>

t_polygone	*get_closer_node(t_polygone *beg, t_matrix *mouse, double min_dist)
{
	t_matrix	*diff;
	t_polygone	*closer;
	double		dist;

	closer = NULL;
	min_dist *= min_dist;
	if (!beg || !beg->next || !mouse || !(diff = matrix_copy(beg->pos)))
		return (NULL);
	while (beg)
	{
		matrix_sub_in(beg->pos, mouse, diff);
		diff->m[2] = 0;
		dist = (matrix_dot_product(diff, diff));
		if (dist < min_dist)
		{
			min_dist = dist;
			closer = beg;
		}
		beg = beg->next;
	}
	matrix_free(&diff);
	return (closer);
}

void		translate_node(t_env *e, t_polygone *poly)
{
	t_polygone *node;

	if ((node = get_closer_node(poly, e->prev_mouse, e->r_select)))
	{
		node->pos->m[0] += e->mouse->m[0] - e->prev_mouse->m[0];
		node->pos->m[1] += e->mouse->m[1] - e->prev_mouse->m[1];
		polygone_destroy(&(e->transform));
		e->transform = transform(poly);
	}
}
