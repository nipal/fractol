/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_calcul_mandel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 00:20:21 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/26 20:07:59 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

typedef	struct	s_mandel_pt
{
	double		min;
	double		max;
	double		v0;	// pt[0]
	double		v1;	// pt[1]
	double		v2;	//tmp[0]
	double		v3;	//tmp[1]
}				t_mandel_pt;


/*
 	
	(a + ib)^2 :

		a^2 + 2*a*ib -b^2



	(a + ib) * (a + ib) * (a + ib)
	=	a^3 - 3a*b^2 
 +i( 3*a^2*b - b^3)
	=	a^3 - 3a*b^2
	+ 3*a^2*ib  + -ib^3
*/

static	inline	int		calcul_one_point(const double x, const double y, int iter, int idf)
{
	int			i;
	t_mandel_pt	v;
	int			again;
	double		x2;
	double		y2;
	double		val;
	double		val2;
	double		sum_val;
	double		num_val;

	(void)idf;
	(void)x2;
	(void)y2;
	(void)val;
	ft_bzero(&v, sizeof(t_mandel_pt));
//	val2 = iter;
	val2 = 0;
	sum_val = 0;
	num_val = 0;


	again = 1;
	i = 0;
	v.v0 = 0;
	v.v1 = 0;
	while (i < (iter) && again)
	{
		v.v2 = (v.v0 * v.v0 - v.v1 * v.v1) + x;
		v.v3 = (2 * v.v0 * v.v1) + y;
		if ((v.v2 * v.v2 + v.v3 * v.v3) > 4)
			again = 0;
//		printf("dist:%f\n", (v.v2 * v.v2 + v.v3 * v.v3));
		if (idf & 16)
		{
			v.v2 = fabs(v.v2);
			v.v3 = fabs(v.v3);
		}
		v.v0 = v.v2;
		v.v1 = v.v3;
		i++;

		if (idf & 8)
		{
			x2 = 0.4 * (v.v0 - 1.0) + (v.v1 + 0.6) - 0.6;
			y2 = -0.2 * (v.v1 + 1.2) * - 1.5 * (v.v0 - 0.7) + 1.1;
			if ((val = fabs(x2 * x2 + y2 * y2)) < 0.05)
			{
				val = val * ((double)iter) * 1 / 0.15;
				if (val > val2)
				{
					val2 = val;
					sum_val += val;
					++num_val;
				}
//				return (val);
			}
		}
	}
//	ft_putnbr(i);
//	ft_putstr("\n");
	if (idf & 8 && sum_val)
		return (val2);
	return (i);
//	return (val2);
//	return (val2);
//	return (val2);
//	return ((sum_val / (num_val)));
}

static	inline	int		calcul_one_point_julia(double beg_x, double beg_y,  double x, double y, int iter, int idf)
{
	int			i;
	t_mandel_pt	v;
	int			again;
	double		x2;
	double		y2;
	double		val;
	double		val2;
	double		sum_val;
	double		num_val;

	(void)idf;
	(void)x2;
	(void)y2;
	(void)val;
	ft_bzero(&v, sizeof(t_mandel_pt));
//	val2 = iter;
	val2 = 0;
	sum_val = 0;
	num_val = 0;


	again = 1;
	i = 0;
	v.v0 = beg_x;
	v.v1 = beg_y;
	while (i < (iter) && again)
	{
		v.v2 = (v.v0 * v.v0 - v.v1 * v.v1) + x;
		v.v3 = (2 * v.v0 * v.v1) + y;
		if ((v.v2 * v.v2 + v.v3 * v.v3) > 4)
			again = 0;
		if (idf & 16)
		{
			v.v2 = fabs(v.v2);
			v.v3 = fabs(v.v3);
		}
//		printf("dist:%f\n", (v.v2 * v.v2 + v.v3 * v.v3));
		v.v0 = v.v2;
		v.v1 = v.v3;
		i++;

		if (idf & 8)
		{
			x2 = 0.4 * (v.v0 - 1.0) + (v.v1 + 0.6) - 0.6;
			y2 = -0.2 * (v.v1 + 1.2) * - 1.5 * (v.v0 - 0.7) + 1.1;
			if ((val = fabs(x2 * x2 + y2 * y2)) < 0.05)
			{
				val = val * ((double)iter) * 1 / 0.15;
				if (val > val2)
				{
					val2 = val;
					sum_val += val;
					++num_val;
				}
			}
		}
	}
//	ft_putnbr(i);
//	ft_putstr("\n");
	if (idf & 8 && sum_val)
		return (val2);
	return (i);
//	return (val2);
//	return (val2);
//	return (val2);
//	return ((sum_val / (num_val)));
}

void	calcul_grid(double *img, double pos[4], double max_x, double max_y)
{
	int			i;
	int			j;
	t_mandel_pt	v;
	int			iter;
	int			id;
	t_env		*e;

	/*
	if (!(e = get_env(NULL))
		|| !(iter = get_iter(0)))
		return ;
		*/
	e = get_env(NULL);
	iter = get_iter(0);
	v.v0 = (pos[2] - pos[0]) / max_x;
	v.v1 = (pos[3] - pos[1]) / max_y;
	v.v3 = pos[1];
	j = -1;
	id = 0;
	v.max = 0;
	v.min = iter;
	while (++j < max_y)
	{
		v.v2 = pos[0];
		i = -1;
		while (++i < max_x)
		{
			if ((e->idf & 4))
			{
//				ft_putstr("julia\n");
//				ft_putnbr();
//				printf("julia: (re):%f	(im):%f\n", e->ctx, e->cty);
//				printf("x:%f	y:%f\n", v.v2, v.v3);
				img[id] = calcul_one_point_julia(v.v2, v.v3, (e->ctx), (e->cty), iter, e->idf);
			}
			else
			{
//				ft_putstr("mandelbrot\n");
				img[id] = calcul_one_point(v.v2, v.v3, iter, e->idf);
			}

	//		/*
			if (img[id] > v.max)
				v.max = img[id];
			else if (img[id] < v.min)
				v.min = img[id];
//*/
			v.v2 += v.v0;
		id++;
		}
		v.v3 += v.v1;
	}
	
}
