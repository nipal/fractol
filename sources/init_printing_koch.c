/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_printing_koch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nperrin <nperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 23:23:51 by fjanoty           #+#    #+#             */
/*   Updated: 2017/06/15 19:23:50 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static	inline	t_koch_changing	init_kch(t_polygone *seg, double iteration
		, double dist, double prev_du)
{
	t_koch_changing	kch;

	kch.seg = seg;
	kch.iter = iteration;
	kch.dist = dist;
	kch.prev_du = prev_du;
	return (kch);
}

void							init_koch_const(t_koch_const *kco
		, t_polygone *transform, t_win *w, double *data)
{
	kco->trans = transform;
	kco->w = w;
	kco->max_iter = data[0];
	kco->len_seg = data[1];
	kco->len_seg_beg = data[2];
	kco->min_print = data[3];
}

void							print_fractal(t_env *e)
{
	double			data_koch[4];
	t_koch_const	kco;
	t_data_nw		data;
	float col[6] = {e->sliders[0]->v1, e->sliders[0]->v2,
					e->sliders[1]->v1, e->sliders[1]->v2,
					e->sliders[2]->v1, e->sliders[2]->v2};

	if (e->transform && e->base)
	{
		if (e->status == SERVEUR)
		{
			ocl_render_run(e);
		}
		data_koch[0] = e->max_iter;
		data_koch[1] = get_polygone_len(e->transform);
		data_koch[2] = get_polygone_len(e->base);
		data_koch[3] = 400;	//	ne sert a rien
//		init_koch_const(&kco, e->transform, e->fractal, data_koch);
//		print_koch_fractale(&kco, init_kch(e->base, 0, 0, 1), 0);
//		actu_win_rest(e->fractal);
	}
}

