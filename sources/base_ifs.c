/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_ifs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 05:01:48 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/05 05:10:06 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int						reset_base(t_env *e)
{
	e->base_add = 0;
	polygone_destroy(&(e->base_model));
	polygone_destroy(&(e->base));
	e->base_model = e->actif;
	return (1);
}

int						reset_transform(t_env *e)
{
	e->trans_add = 0;
	polygone_destroy(&(e->trans_model));
	polygone_destroy(&(e->transform));
	e->trans_model = e->actif;
	return (1);
}

int						actu_base(t_env *e, t_polygone *src)
{
	polygone_destroy(&(e->base));
	e->base = scale_segment(src, &(e->border_b), &(e->base_cadre), e->tr_base);
	print_fractal(e);
	return (1);
}

int						actu_transform(t_env *e, t_polygone *src)
{
printf("transform->%p\n", e->transform);
	polygone_destroy(&(e->transform));
	e->transform = transform(src);
	print_fractal(e);
	return (1);
}

void					redefine_base(t_polygone *new_base, t_border *from
		, t_win *to)
{
	double		coef_x;
	double		coef_y;
	t_polygone	*tmp;

	if (!new_base)
		return ;
	polygone_destroy(&(to->e->base));
//	to->e->base = NULL;
	coef_x = (to->size_x) / (from->x1 - from->x0);
	coef_y = (to->size_y) / (from->y1 - from->y0);
	while (new_base)
	{
		tmp = copy_node(new_base, 0);
		tmp->pos->m[0] = (tmp->pos->m[0] - from->x0) * coef_x;
		tmp->pos->m[1] = (tmp->pos->m[1] - from->y0) * coef_y;
		polygone_push_back(&(to->e->base), tmp);
		new_base = new_base->next;
	}
}
