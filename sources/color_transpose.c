/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_transpose.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 18:19:21 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/12 03:29:38 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	rgb	->	tsl:
**				new t_matrix	t_matrix	*rgb_to_tsl(double r, double g, double b);
**				modif_inside	void		rgb_to_tsl(t_matrix *color);
**
**	tsl	->	rvb:
**				new t_matrix
**				modif_inside
**
*/

/*
**	RVB			TSL
**	[0, 255] -> [0, 1] 
*/
t_matrix	*rgb_to_tsl_new(double r, double g, double b);
void		rgb_to_tsl_mod(t_matrix *color);

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

t_matrix	*rgb_to_tsl_new(double r, double g, double b)
{
	double		max;
	double		min;
	double		croma;
	t_matrix	*tsl;

	r /= 255.0;
	g /= 255.0;
	b /= 255.0;
	if (!(tsl = matrix_init(1, 3)))
		return (NULL);
	max = MAX(r, g);
	max = MAX(max, b);
	min = MIN(r, g);
	min = MIN(min, b);
	croma = max - min;
	if ((!croma && !(tsl->m[0] = 0))
		|| (max == r && ((tsl->m[0] = 60 * modulo((((g - b) / croma) + 6.0),  6.0)) > -1))
		|| ((max == g) && ((tsl->m[0] = 60 * (((b - r) / croma) + 2.0) > -1)))
		|| ((tsl->m[0] = 60 * (((r - g) / croma) + 4.0)) > -1 ))
	tsl->m[2] = max;
	tsl->m[1] = (max == 0) ? 0 : croma / max;
	return (tsl);
}

void		rgb_to_tsl_mod(t_matrix *rgb)
{
	double		max;
	double		min;
	double		croma;
	t_matrix	*tsl;

	rgb->m[0] /= 255.0;
	rgb->m[1] /= 255.0;
	rgb->m[2] /= 255.0;
	if (!(tsl = matrix_init(1, 3)))
		return ;
	max = MAX(rgb->m[0], rgb->m[1]);
	max = MAX(max, rgb->m[2]);
	min = MIN(rgb->m[0], rgb->m[1]);
	min = MIN(min, rgb->m[2]);
	croma = max - min;
	if ((!croma && !(tsl->m[0] = 0))
		|| (max == rgb->m[0] && ((tsl->m[0] = 60 * (modulo((((rgb->m[1] - rgb->m[2]) / croma) + 6.0),  6.0))) > -1))
		|| ((max == rgb->m[1]) && ((tsl->m[0] = 60 * (((rgb->m[2] - rgb->m[0]) / croma) + 2.0) > -1)))
		|| ((tsl->m[0] = 60 * (((rgb->m[0] - rgb->m[1]) / croma) + 4.0)) > -1 ))
	tsl->m[2] = max;
	tsl->m[1] = (max == 0) ? 0 : croma / max;
	rgb->m[0] = tsl->m[0];
	rgb->m[1] = tsl->m[1];
	rgb->m[2] = tsl->m[2];
}

t_matrix	*tsl_to_rvb_new_old(double t, double s, double l)
{
	int		a, b, c;
	int		i;
	double	x;
	double	m;
	t_matrix	*rvb;

	t = modulo(t, 360);
	if (!(rvb = matrix_init(1, 3)))
		return (NULL);
	x = (l * s) * (modulo((1 - ABS(t / 60.0)), 2) - 1);
	m = l * (1 - s);
	i = (int)((modulo(t, 360)) / 60.0);

	a = (1 - i + 9) % 3;
	b = (((i + 1) % 6) / 2);
	c = 3 - a - b;
	a %= 3;
	b %= 3;
	c %= 3;
	rvb->m[a] = modulo((x + m) * 255, 255);
	rvb->m[b] = modulo(((l * s) + m) * 255, 255);
	rvb->m[c] = modulo(m * 255, 255);
//	dprintf(1, "a:%.d	b:%d	c:%d\n", a, b, c);
//	dprintf(1, "r:%.2f	v:%.2f	b:%.2f\n", rvb->m[0], rvb->m[1], rvb->m[2]);
//	dprintf(1, "t:%.2f	s:%.2f	l:%.2f\n", t, s, l);
	return (rvb);
}
//	0 + 1 + 2

t_matrix	*tsl_to_rvb_new(double t, double s, double l)
{
	t_matrix	*rvb;
	double	min, max, croma, x, i;

//	t = modulo(t, 360);
	if (!(rvb = matrix_init(1, 3)))
		return (NULL);
	max = l * 255;
	min = (1 - s) * l * 255;
	croma = max - min;
	i = t / 60;
	x = croma * modulo(i, 2);
//	dprintf(1, "i:%.2f\n", i);
	if (i < 1)
	{
//		dprintf(1, "[%d, %d[\n", (int)i, (int)(i + 1));
		rvb->m[0] = croma + min;
		rvb->m[1] = x + min;
		rvb->m[2] = min;
	}
	else if (i >= 1 && i < 2)
	{
//		dprintf(1, "[%d, %d[\n", (int)i, (int)(i + 1));
		rvb->m[0] = x + min;
		rvb->m[1] = croma + min;
		rvb->m[2] = min;
	}
	else if (i >= 2 && i < 3)
	{
//		dprintf(1, "[%d, %d[\n", (int)i, (int)(i + 1));
		rvb->m[0] = min;
		rvb->m[1] = croma + min;
		rvb->m[2] = x + min;
	}
	else if (i >= 3 && i < 4)
	{
//		dprintf(1, "[%d, %d[\n", (int)i, (int)(i + 1));
		rvb->m[0] = min;
		rvb->m[1] = x + min;
		rvb->m[2] = croma + min;
	}
	else if (i >= 4 && i < 5)
	{
//		dprintf(1, "[%d, %d[\n", (int)i, (int)(i + 1));
		rvb->m[0] = x + min;
		rvb->m[1] = min;
		rvb->m[2] = croma + min;
	}
	else
	{
//		dprintf(1, "[%d, %d[\n", (int)i, (int)(i + 1));
		rvb->m[0] = croma + min;
		rvb->m[1] = min;
		rvb->m[2] = x + min;
	}
//	dprintf(1, "t:%.2f	s:%.2f	l:%.2f\n", t, s, l);
//	dprintf(1, "r:%.2f	v:%.2f	b:%.2f\n", rvb->m[0], rvb->m[1], rvb->m[2]);
//	rvb->m[a] = modulo((x + m) * 255, 255);
//	rvb->m[b] = modulo(((l * s) + m) * 255, 255);
//	rvb->m[c] = modulo(m * 255, 255);
	return (rvb);
}