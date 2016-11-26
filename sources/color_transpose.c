/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_transpose.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 18:19:21 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/26 16:15:01 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double		modulo(double a, double b)
{
	int		r;

	b = (b > 0) ? b : -b;
	if (a >= 0)
	{
		if (a < b)
			return (a);
		r = (long)(a / b);
		return (a - r * b);
	}
	else
	{
		r = (long)(a / b);
		return (a - ((r - 1)) * b);
	}
}

t_matrix	*tsl_to_rvb_new(double t, double s, double l)
{
	t_matrix	*rvb;

	if (!(rvb = matrix_init(1, 3)))
		return (NULL);
	tsl_to_rvb_in(t, s, l, rvb);
	return (rvb);
}

/*
**	ind[]
**	ix	-> 0
**	ic	-> 1
**	i0	-> 2
**
**	mm[]
**	min	-> 0
**	max	-> 1
*/

void		tsl_to_rvb_in(double t, double s, double l, t_matrix *rvb)
{
	int		ind[3];
	double	mm[2];
	double	croma;
	double	x;
	double	i;

	if (!rvb)
		return ;
	mm[1] = (int)(l * 255);
	mm[0] = (int)((1 - s) * l * 255);
	croma = mm[1] - mm[0];
	i = t / 60;
	x = croma * modulo(i, 2);
	ind[0] = (7 - (int)i) % 3;
	ind[1] = (((int)i % 2) == 0) ? (ind[0] + 2) % 3 : (ind[0] + 1) % 3;
	ind[2] = (3 - ind[1] - ind[0]) % 3;
	rvb->m[ind[1]] = croma + mm[0];
	rvb->m[ind[0]] = x + mm[0];
	rvb->m[ind[2]] = x + mm[0];
}


int			tsl_to_rvb_int(double t, double s, double l)
{
	t_matrix	*rvb;
	int			color;

	if (!(rvb = tsl_to_rvb_new(t, s, l)))
		return (-1);
	color = ((unsigned char)rvb->m[0]); 
	color |= ((unsigned char)rvb->m[1]) << 8; 
	color |= ((unsigned char)rvb->m[2]) << 16; 
	return (color);
}

int			init_range_tsl(t_range_tsl *range)
{
	if (!range)
		return (0);
	range->tmin = 0;
	range->tmax = 1;
	range->smin = 0;
	range->smax = 1;
	range->lmin = 0;
	range->lmax = 1;
	return (1);
}
