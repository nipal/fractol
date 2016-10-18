/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_koch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 13:27:00 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/18 19:50:46 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	reset_base(t_env *e)
{
	polygone_destroy(&(e->beg_actif));
	polygone_destroy(&(e->trans_controle));
	polygone_destroy(&(e->base));
	e->actif = NULL;
	e->beg_actif = NULL;
	return (0);
}

int	reset_transform(t_env *e)
{
	polygone_destroy(&(e->transform));
	polygone_destroy(&(e->beg_actif));
	polygone_destroy(&(e->trans_controle));
	e->actif = NULL;
	e->beg_actif = NULL;
	return (0);
}

/*
**	quand on reset l'un au l'aure on remet tout a zero
**	quand on clique dans un cadrde ET que base OU transform == null
*/

void	init_koch_param_border(t_env *e, t_win *win_param)
{
	int	border = 5;
	int	top = win_param->size_y * 0.5;

	e->border_b.x0 = border;
	e->border_b.y0 = top;
	e->border_b.x1 = win_param->size_x * 0.5 - border;
	e->border_b.y1 = win_param->size_y - border;
	e->border_t.x0 = win_param->size_x * 0.5 + border;
	e->border_t.y0 = top;
	e->border_t.x1 = win_param->size_x - border;
	e->border_t.y1 = win_param->size_y - border;
}

void	draw_border(t_win *w, t_border *border, t_matrix *color)
{
	t_matline	mat_line;
	t_matrix	*pt1;
	t_matrix	*pt2;

	if (!(pt1 = matrix_init(1, 3))
		|| !(pt2 = matrix_init(1, 3)))
		return ;
	pt1->m[0] = border->x0;
	pt1->m[1] = border->y0;
	pt2->m[0] = border->x1;
	pt2->m[1] = border->y1;
	mat_line.pt1 = pt1;
	mat_line.pt2 = pt2;
	mat_line.c1 = color;
	mat_line.c2 = color;
	draw_line3(&mat_line, w);
	matrix_free(&pt1);
	matrix_free(&pt2);
}
