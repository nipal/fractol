/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_param_koch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 01:09:44 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/09 01:50:05 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "c_maths.h"

/*
**	On veux faire une forme:  
**		-position des curseur
**			-> couleur
**		-nombre d'iteration
**		-position de la base et de la transfrmatin
*/

t_polygone	*init_segment(double valu[4][2], int nb, t_border *border)
{
	int			i;
	t_matrix	*pos;
	t_matrix	*col;
	t_polygone	*beg;
	t_polygone	*node;
	double		min;

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
	static	double	pos_trans[4][2] =
							{{0.2, 0.2}, {0.15, 0.17}, {0.65, 0.4}, {0.3, 0.9}};
	static	double	pos_base[4][2] =
							{{0.1, 0.1}, {0.7, 0.2}, {0.6, 0.5}, {0.5, 0.5}};

	e->max_iter = 4;
	if (!(e->base_model = init_segment(pos_base, 4, &(e->border_b)))
		|| !(e->trans_model = init_segment(pos_trans, 4, &(e->border_t))))
{
	if (!e->trans_model)
		printf("wooops somhing crash\n");
	if (!e->base_model)
		printf("BOUYA somhing crash\n");
		return (0);
}
	e->trans_add = 1;
	e->base_add = 1;
	e->draw_base = 1;
	e->draw_transform = 1;
	sliders_set_valu(e->sliders[0], 0.6, 0.7);
	sliders_set_valu(e->sliders[1], 0.3, 0.8);
	sliders_set_valu(e->sliders[2], 0.95, 0.1);
	actu_base(e, e->base_model);	
	actu_transform(e, e->trans_model);	
	return (1);
}
