/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   koch_generalise.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 04:10:47 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/10 10:23:31 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		init_koch(t_env *e)
{
	e->img_low = NULL;
	e->draw_base = 1;
	e->r_select = 20;
	e->nb_sliders = 3;
	e->id_scrol = -1;
}

void		move_last(int x, int y, t_env *e)
{
	if (e->actif)
	{
		e->actif->pos->m[0] = x;
		e->actif->pos->m[1] = y;
	}
}

void		end_base(t_env *e)
{
	t_polygone	*last;

	if (!e->actif || !e->beg_actif || !(last = copy_node(e->beg_actif, 0)))
		return ;
	e->draw_base = 0;
	e->draw_transform = 1;
	e->base = e->beg_actif;
	e->actif = NULL;
	e->beg_actif = NULL;
}

void		end_transform(t_env *e)
{
	e->draw_transform = 0;
	e->actif = NULL;
	e->transform = transform(e->beg_actif);
	e->beg_actif = NULL;
}

int			init_win_param(t_env *e, int size_x, int size_y, char *name)
{
	if (!(e->param = window_init(e, size_x, size_y, name)))
		return (0);
	return (1);
}
