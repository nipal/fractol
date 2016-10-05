/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_madelbrot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 02:31:41 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/05 02:51:47 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"


# define X 0
# define Y 1
int		calcul_one_point(double ct[2], int iter)
{
	int		i;
	double	tmp[2];
	double	pt[2];

	i = 0;
	pt[0] = 0;
	pt[1] = 0;
	while (i < iter)
	{
		tmp[0] = pt[0] * pt[0] - pt[1] * pt[1] + ct[0];
		tmp[1] = 2 * pt[0] * pt[1] + ct[1];
		if (tmp[0] * tmp[0] + tmp[1] * tmp[1] > 4)
			break ;
		pt[0] = tmp[0];
		pt[1] = tmp[1];
		i++;
	}
	return i;
}

void	calcul_hgrid(t_env *e, double pos[4])
{
	int		i;
	int		j;
	double	add[2];
	double	curs[2];

	add[0] = (pos[2] - pos[0]) / e->x_maxh;
	add[1] = (pos[3] - pos[1]) / e->y_maxh;
	curs[1] = pos[1];
	j = 0;
	while (j < e->y_maxh)
	{
		curs[0] = pos[0];
		i = 0;
		while (i < e->x_maxh)
		{
			e->img_height[j][i] = calcul_one_point(curs, e->iter);
			curs[0] += add[0];
			i++;
		}
		curs[1] += add[1];
		j++;
	}
}

int		get_gray_color(int valu, int max_iter)
{
	t_pix	pix;
	int		val;

	val = 250 * valu / max_iter;
	pix.comp[0] = val;
	pix.comp[1] = val;
	pix.comp[2] = val;
	return (pix.nb);;
}

void	set_color_fractal(t_env *e)
{
	int		i;
	int		j;

void	calc_average(double pos[8], double max[4], t_env *e);
	j = 0;
	while (j < e->y_maxl)
	{
		i = 0;
		while (i < e->x_maxl)
		{
			e->data[i + j * e->x_maxl].nb = get_gray_color(e->img_low[j][i], e->iter);
			i++;
		}
		j++;
	}
}

/*
**	add		=>	increment
**	curs	=>	position
**	mult	=>	proportion de surcoupe
*/

/*
**	pos	=> 	0	l_x1
**			1	l_y1
**			2	l_x2
**			3	l_y2
**
**			4	h_x1
**			5	h_y1
**			6	h_x2
**			7	h_y2
**
**	max	=>	0	l_x_max
**			1	l_y_max
**			2	h_x_max
**			3	h_y_max
*/

int		get_iter_average(double mult[2], int val[SIZE_Y * 2 + 2][SIZE_X * 2 + 2])
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
	return((int) ((1 - coef_x - coef_y + coef_xy) * val[j][i]
		+ (coef_x - coef_xy) * val[j][i + 1]
		+ (coef_y - coef_xy) * val[j + 1][i]
		+ coef_xy * val[j + 1][i + 1]));
}

//	foncctionne que si on fait une moyenne de 4 au max et que la fenettre low
//	est comnpletement inclus dans la height au point de s'en foutre du i + 1 et j + 1
void	calc_average(double pos[8], double max[4], t_env *e)
{
	int		ind[2];
	double	add[2];
	double	beg[2];
	double	curs[2];
	
	add[0] = ((pos[2] - pos[0]) * max[2]) / (max[0] * (pos[6] - pos[4]));
	add[1] = ((pos[3] - pos[1]) * max[3]) / (max[1] * (pos[7] - pos[5]));
	beg[0] = (pos[0] - pos[4]) * (max[2] / (pos[6] - pos[4]));
	beg[1] = (pos[1] - pos[5]) * (max[3] / (pos[7] - pos[5]));
	curs[1] = beg[1];
	ind[1] = 0;
	while (curs[1] < pos[2])
	{
		curs[0] = beg[0];
		ind[0] = 0;
		while (curs[0] < pos[3])
		{
			e->img_low[ind[0]][ind[1]] = get_iter_average(curs, e->img_height);
			ind[0]++;
			curs[0] += add[0];
		}
		ind[1]++;
		curs[1] += add[1];
	}
}
//	les point calculer sont tout le temps a haute resolution
//		c'est quand on imprime  une image que l'on fait une moyenne ou pas

void	resize_window(double pos[4], double mult, double x, double y)
{
	double	new_pos[4];
	t_env	*e;

	e = get_env(NULL);
	new_pos[0] = pos[0] + ((pos[2] - pos[0]) / e->x_maxl) * ((1 - mult) * x); 
	new_pos[2] = pos[0] + ((pos[2] - pos[0]) / e->x_maxl)
		* ((e->x_maxl - x) * mult + x); 
	new_pos[1] = pos[1] + ((pos[3] - pos[1]) / e->y_maxl) * ((1 - mult) * y); 
	new_pos[3] = pos[1] + ((pos[3] - pos[1]) / e->y_maxl)
		* ((e->y_maxl - y) * mult + y); 
	pos[0] = new_pos[0];
	pos[1] = new_pos[1];
	pos[2] = new_pos[2];
	pos[3] = new_pos[3];
}

int		averaging_height(double coef[6], int img_h[SIZE_Y * 2 + 2][SIZE_X * 2 + 2], int i, int j)
{
	double	result;
	int		k;

	result = 0;
	k = 0;
	while (k < 9)
	{
		result += coef[3 + (k / 3)] * coef[k % 3] * (double)(img_h[j + (k / 3) - 1][i + (k % 3) - 1]);
		k++;
	}
	return ((int)result);
}

void	end_average_calc(double du, double pack[12], int img_height[SIZE_Y * 2 + 2][SIZE_X * 2 + 2]
		, int img_low[SIZE_Y][SIZE_X])
{
	double	result;
	int		k;

	pack[10] = 0;
	while (pack[10] < SIZE_X)
	{
		pack[0] = pack[6];
		pack[1] = (1 - pack[6] > du) ? du : 1 - pack[6];
		pack[2] = (1 - pack[6] > du) ? 1 - du - pack[6] : 0;
		result = 0;
		k = 0;
		while (k < 9)
		{
			result += pack[3 + (k / 3)] * pack[k % 3]
				* (double)(img_height[(int)pack[9] + (k / 3) - 1][(int)pack[8] + (k % 3) - 1]);
			k++;
		}
		img_low[(int)pack[11]][(int)pack[10]] = (int)result;
		pack[6] += (1 - pack[6] > du) ? 2 * du - 1: -du;
		pack[8] += (1 - pack[6] > du) ? 1 : 2;
		pack[10]++;
	}
}

void	calculate_average(int img_low[SIZE_Y][SIZE_X], int img_height[SIZE_Y * 2 + 2][SIZE_X * 2 + 2],
			double pos_l[4], double pos_h[4])
{
	double	pack[12];
	double	du;

	pack[6] = 0;
	pack[7] = 0;
	du = ((pos_h[2] - pos_h[0]) * SIZE_X ) / 
		((pos_l[2] - pos_l[0]) * (SIZE_X * 2.0 + 2.0));
	pack[8] = (pos_l[0] - pos_h[0]) / (pos_h[2] - pos_h[0]) * (SIZE_X * 2 + 2);
	pack[9] = (pos_l[1] - pos_h[1]) / (pos_h[3] - pos_h[1]) * (SIZE_Y * 2 + 2);
	pack[11] = 0;
	while (pack[11] < SIZE_Y)
	{
		pack[3] = pack[7];
		pack[4] = (1 - pack[7] > du) ? du : 1 - pack[7];
		pack[5] = (1 - pack[7] > du) ? 1 - du - pack[7] : 0;
		end_average_calc(du, pack, img_height, img_low);
		pack[7] += (1 - pack[7] > du) ? 2 * du - 1: -du;
		pack[7] += (1 - pack[7]) ? 1 : 2;
		pack[11]++;
	}
}


//	Quand on a le nouveau cadre on decide si on recalcule ou pas


/*
**	-le redimentionement d'une fenetre
**	-la gestion du recalcule de img_height
**	-la gestion des calcule de bande pour le scroling
*/
