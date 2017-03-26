/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_calcul_mandel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 00:20:21 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/29 04:57:12 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	si ca a marcher onrenvoie un truc negatif
*/

static	inline	int		calcul_trap(double v0, double v1, int idf, int iter)
{
	double	val;
	double	x2;
	double	y2;
	int		ret;

	ret = 1;
	if (!(idf & 8))
		return (1);
	x2 = 0.4 * (v0 - 1.0) + (v1 + 0.6) + 0.6;
	y2 = -0.2 * (v1 + 1.2) + 1.5 * (v0 - 0.7) + 1.1;
	if ((val = fabs(x2 * x2 + y2 * y2)) < 0.05)
	{
		val = val * ((double)iter) * 1 / 0.15;
		ret = -(val);
	}
	return (ret);
}

static	inline	int		calcul_one_point(const double x, const double y,
														int iter, int idf)
{
	int			i;
	t_mandel_pt	v;
	int			again;
	double		val_trap;

	val_trap = 1;
	again = 1;
	i = -1;
	v.v0 = 0;
	v.v1 = 0;
	while (++i < (iter) && again)
	{
		v.v2 = (v.v0 * v.v0 - v.v1 * v.v1) + x;
		v.v3 = (2 * v.v0 * v.v1) + y;
		if ((v.v2 * v.v2 + v.v3 * v.v3) > 4)
			again = 0;
		if (idf & 16 && ((v.v2 = fabs(v.v2)) >= 0))
			v.v3 = fabs(v.v3);
		v.v0 = v.v2;
		v.v1 = v.v3;
		if (idf & 8 && (val_trap = calcul_trap(v.v0, v.v1, idf, iter)) <= 0)
			return (val_trap);
	}
	return (i);
}

static	inline	int		calcul_one_point_julia(t_cop_julia juju, int iter
		, int idf)
{
	int			i;
	t_mandel_pt	v;
	int			again;
	double		val_trap;

	val_trap = 1;
	again = 1;
	i = 0;
	v.v0 = *(juju.beg_x);
	v.v1 = *(juju.beg_y);
	while (i < (iter) && again)
	{
		v.v2 = (v.v0 * v.v0 - v.v1 * v.v1) + juju.ctx;
		v.v3 = (2 * v.v0 * v.v1) + juju.cty;
		if ((v.v2 * v.v2 + v.v3 * v.v3) > 4)
			again = 0;
		if (idf & 16 && ((v.v2 = fabs(v.v2)) >= 0))
			v.v3 = fabs(v.v3);
		v.v0 = v.v2;
		v.v1 = v.v3;
		if (idf & 8 && (val_trap = calcul_trap(v.v0, v.v1, idf, iter)) <= 0)
			return (val_trap);
		i++;
	}
	return (i);
}

static	inline	int		init_calcul_grid(t_mandel_pt *v, double pos[5]
		, t_pt2d max, int iter)
{
	v->v0 = (pos[2] - pos[0]) / max.x;
	v->v1 = (pos[3] - pos[1]) / max.y;
	v->v3 = pos[1];
	v->max = 0;
	v->min = iter;
	return (-1);
}

void					calcul_grid(double *img, double pos[4],
			t_pt2d max, t_env *e)
{
	t_mandel_pt	v;
	t_calc_gr	cg;
	t_cop_julia	juju;

	cg.iter = e->iter;
	cg.id = init_calcul_grid(&v, pos, max, cg.iter);
	cg.j = -1;
	juju.ctx = e->ctx;
	juju.cty = e->cty;
	juju.beg_x = &(v.v2);
	juju.beg_y = &(v.v3);
	while (++cg.j < max.y && (cg.i = -1))
	{
		v.v2 = pos[0];
		while (++cg.i < max.x && ++cg.id >= 0)
		{
			img[cg.id] = ((e->idf & 4)) ?
	calcul_one_point_julia(juju, cg.iter, e->idf) :
	calcul_one_point(v.v2, v.v3, cg.iter, e->idf);
			(img[cg.id] > v.max) ? v.max = img[cg.id] : 0;
			(img[cg.id] < v.min) ? v.min = img[cg.id] : 0;
			v.v2 += v.v0;
		}
		v.v3 += v.v1;
	}
}
