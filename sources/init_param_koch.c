/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_param_koch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 01:09:44 by fjanoty           #+#    #+#             */
/*   Updated: 2017/06/15 18:39:11 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "c_maths.h"

t_polygone	*init_segment(double valu[4][2], int nb, t_border *border,
		double min)
{
	int			i;
	t_matrix	*pos;
	t_matrix	*col;
	t_polygone	*beg;
	t_polygone	*node;

	i = 0;
	beg = NULL;
	min = (border->x1 - border->x0 < border->y1 - border->y0) ?
			border->x1 - border->x0 : border->y1 - border->y0;
	while (i < nb)
	{
		if (!(pos = vect_new_vertfd(border->x0 + min * valu[i][0], border->y0
	+ min * valu[i][1], 0))
			|| !(col = vect_new_vertfd(0, 0, 0))
			|| !(node = creat_node_fv(0, pos, col)))
			return (NULL);
		polygone_push_back(&beg, node);
		i++;
	}
	return (beg);
}

void		sliders_set_valu(t_slider *slide, double v1, double v2)
{
	slide->v1 = v1;
	slide->v2 = v2;
}

int			init_statment(t_env *e)
{
	e->max_iter = 4;
	sliders_set_valu(e->sliders[0], 0.6, 0.7);
	sliders_set_valu(e->sliders[1], 0.3, 0.8);
	sliders_set_valu(e->sliders[2], 0.85, 0.1);
	return (1);
}
