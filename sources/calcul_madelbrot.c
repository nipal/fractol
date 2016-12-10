/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_madelbrot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 02:31:41 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/10 07:31:02 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"

double				*get_lst_color(int val)
{
	int				i;
	static	double	*valu = NULL;

	if (valu == NULL)
	{
		valu = (double*)malloc(sizeof(double) * (val + 2));
		i = 0;
		while (i < val + 2)
		{
			valu[i] = log(i);
			i++;
		}
	}
	return (valu);
}

static	inline	int	get_gray_color(double valu, double max_iter)
{
	t_pix	pix;
	int		val;

	if (valu < 0)
		valu *= -1;
	val = 255 - (250 * (((valu)) / (max_iter)));
	pix.comp[0] = val;
	pix.comp[1] = val;
	pix.comp[2] = val;
	return (pix.nb);
}

void				set_color_fractal(t_win *w)
{
	double			*img_low;
	t_mandel_color	mc;
	int				id;
	double			val;

	img_low = w->e->img_low;
	mc.y_maxl = w->e->y_maxl;
	mc.x_maxl = w->e->x_maxl;
	mc.j = -1;
	mc.iter = w->e->iter;
	id = 0;
	get_gray_color(img_low[id], mc.iter);
	while (++mc.j < mc.y_maxl && (mc.i = -1))
	{
		while (++mc.i < mc.x_maxl)
		{
			if (img_low[id] >= 0)
				val = log((double)img_low[id] + 1) / log((double)mc.iter + 1);
			else
				val = ((double)(-img_low[id])) / ((double)mc.iter + 1);
			w->data[id].nb = tsl_to_rvb_int(((1 - (0.4 + val * 0.6)
				* val)) * 360, val, 1 - (0.2 + val * 0.8));
			++id;
		}
	}
}

double				get_iter_average(double mult[2], double **val)
{
	int		i;
	int		j;
	double	coef_x;
	double	coef_y;
	double	coef_xy;

	i = (int)mult[0];
	j = (int)mult[1];
	coef_x = mult[0] - (double)((int)mult[0]);
	coef_y = mult[1] - (double)((int)mult[1]);
	coef_xy = coef_x * coef_y;
	return (((1 - coef_x - coef_y + coef_xy) * val[j][i]
		+ (coef_x - coef_xy) * val[j][i + 1]
		+ (coef_y - coef_xy) * val[j + 1][i]
		+ coef_xy * val[j + 1][i + 1]));
}

int					resize_window(double pos[4], double mult, t_pt2d size
		, t_env *e)
{
	double	new_pos[4];

	new_pos[0] = pos[0] + ((pos[2] - pos[0]) / e->x_maxl)
		* ((1 - mult) * size.x);
	new_pos[2] = pos[0] + ((pos[2] - pos[0]) / e->x_maxl)
		* ((e->x_maxl - size.x) * mult + size.x);
	new_pos[1] = pos[1] + ((pos[3] - pos[1]) / e->y_maxl)
		* ((1 - mult) * size.y);
	new_pos[3] = pos[1] + ((pos[3] - pos[1]) / e->y_maxl)
		* ((e->y_maxl - size.y) * mult + size.y);
	pos[0] = new_pos[0];
	pos[1] = new_pos[1];
	pos[2] = new_pos[2];
	pos[3] = new_pos[3];
	return (1);
}
