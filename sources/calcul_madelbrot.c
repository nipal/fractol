/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_madelbrot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 02:31:41 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/06 09:15:16 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"


# define X 0
# define Y 1
int		calcul_one_point(double ct[2], int iter)
{
	int		i;
	double	tmp[2];
	double	pt[2];
	int		again;

	again = 1;
	i = 0;
	pt[0] = 0;
	pt[1] = 0;
//	dprintf(1, "iter:	%d\n", iter);
	while (i < iter && again)
	{
		tmp[0] = pt[0] * pt[0] - pt[1] * pt[1] + ct[0];
		tmp[1] = 2 * pt[0] * pt[1] + ct[1];
		if (tmp[0] * tmp[0] + tmp[1] * tmp[1] > 4)
			again = 0;
		pt[0] = tmp[0];
		pt[1] = tmp[1];
		i++;
	}
	return (i);
}

void	calcul_grid(double **img, double pos[4], double max_x, double max_y)
{
	int		i;
	int		j;
	double	add[2];
	double	curs[2];
	int		iter;

	iter = get_iter(0);
	add[0] = (pos[2] - pos[0]) / max_x;
	add[1] = (pos[3] - pos[1]) / max_y;
	curs[1] = pos[1];
	j = 0;
	while (j < max_y)
	{
		curs[0] = pos[0];
		i = 0;
		while (i < max_x)
		{
			img[j][i] = calcul_one_point(curs, iter);
			curs[0] += add[0];
			i++;
		}
		curs[1] += add[1];
		j++;
	}
}

double		*get_lst_color(int val)
{
	int				i;
	static	int		iter;
	static	double	*valu = NULL;

	if (valu == NULL)
	{
		valu = (double*)malloc(sizeof(double) * (val + 2));
		iter = val;
		i = 0;
		while (i < val + 2)
		{
			valu[i] = log(i);
			i++;
		}
	}
	return (valu);
}
int		get_gray_color(double valu, double max_iter)
{
	t_pix	pix;
	int		val;
//	static	double	*color = NULL;
//	color = get_lst_color(max_iter);

//	if (color == NULL)
//		color = get_lst_color(max_iter);
//	val = 250 *(1 -  (color[(int)valu + 1] / color[(int)max_iter + 1]));
	val = 250 *(1 -  (log(valu + 1) / log(max_iter + 1)));
	pix.comp[0] = val;
	pix.comp[1] = val;
	pix.comp[2] = val;
	return (pix.nb);;
}


void	set_color_fractal(t_env *e)
{
	int		i;
	int		j;

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

double		get_iter_average(double mult[2], double **val)
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
	return(((1 - coef_x - coef_y + coef_xy) * val[j][i]
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

double	averaging_height(double coef[6], double **img_h, int i, int j)
{
	double	result;
	int		k;

	result = 0;
	k = 0;
	while (k < 9)
	{
		result += coef[3 + (k / 3)] * coef[k % 3] * (double)(img_h[j + (k / 3)][i + (k % 3)]);
		k++;
	}
	return (result);
}

void	describe_moy(t_average *moy)
{
	dprintf(1,	"il:%d	jl:%d	ih0:%d	ih:%d	jh:%d	du:%.2f \nalpha_x:%.3f	beta_x:%.2f	gama_x:%.2f \nalpha_y:%.2f	beta_y:%.2f	gama_y:%.2f\n"
			, moy->il
			, moy->jl
			, moy->ih0
			, moy->ih
			, moy->jh

			, moy->du
			, moy->coef[0]
			, moy->coef[1]
			, moy->coef[2]
			, moy->coef[3]
			, moy->coef[4]
			, moy->coef[5]
			);
}

void	end_average_calc(double du, t_average *moy, double **img_height, double **img_low)
{
	double	result;
	int		k;
	int		i;
	int		j;

	moy->coef[0] = du;
	moy->il = 0;
	moy->ih = moy->ih0;//;(pos_l[0] - pos_h[0]) / (pos_h[2] - pos_h[0]) * (SIZE_X * 2 + 2);
	while (moy->il < SIZE_X)
	{
//		moy->coef[0] = 0;//moy->coef[0];
		moy->coef[1] = (moy->coef[0] + du < 1) ? du : 1 - moy->coef[0];
		moy->coef[2] = (moy->coef[0] + du < 1) ? 1 - du - moy->coef[0] : 0;
		result = 0;
		k = 0;
		while (k < 9)
		{
			i = (int)moy->ih + (k / 3);
			j = (int)moy->jh + (k % 3);
//			dprintf(1, "\rmoy->il:%d	k:%d	i:%d	j:%d", moy->il, k, i, j);
			result += moy->coef[3 + (k / 3)] * moy->coef[k % 3] * (img_height[j][i]);

			k++;
		}
		img_low[moy->jl][moy->il] = result;
/*
//dprintf()
char c;
dprintf(1, "$$\t-\t-\t$$$\nk:%d	img_height[%d][%d]:%d	result:%f\n", k, j, i, img_height[j][i], result);
dprintf(1, "img_low[%d][%d]:%d\n", moy->jl, moy->il, img_height[moy->jl][moy->il]);
dprintf(1, "moy->coef[2] > 0 [%d]	::: %f :::\n", (moy->coef[2] > 0), (moy->coef[2]));
describe_moy(moy);
read(0, &c, 1);
//*/
		moy->coef[0] = (moy->coef[2] > 0) ? du - moy->coef[2] :  du - moy->coef[1];
		moy->ih += (moy->coef[2] > 0) ? 2 : 1;
		moy->il++;
	}
}

void	calculate_average(double **img_low, double **img_height, double pos_l[4], double pos_h[4])
{
	double	du;
	t_average	moy;
	t_env		*e;

double	delta_xh, delta_xl;

	e = get_env(NULL);
	moy.il = 0;
	moy.jl = 0;
	delta_xh = (pos_h[2] - pos_h[0]);
	delta_xl = (pos_l[2] - pos_l[0]);
//	dprintf(1, "delta_xh:%f	delta_xl:%f\n", delta_xh, delta_xl);
//	du = (double)(((delta_xh)) / (double)((delta_xl) * 2));
	du = (double)(((delta_xh) * e->x_maxl) / (double)((delta_xl) * e->x_maxh));
	du /= 1;
	moy.ih0 = (pos_l[0] - pos_h[0]) / (pos_h[2] - pos_h[0]) * (SIZE_X * 2 + 2);
	moy.jh = (pos_l[1] - pos_h[1]) / (pos_h[3] - pos_h[1]) * (SIZE_Y * 2 + 2);
	moy.jl = 0;
	moy.du = du;
	moy.coef[3] = du;//moy.coef[3];
	while (moy.jl < SIZE_Y)
	{
	//	moy.coef[3] = moy.coef[3];
		moy.coef[4] = (1 - moy.coef[3] > du) ? du : 1 - moy.coef[3];
		moy.coef[5] = (1 - moy.coef[3] > du) ? 1 - du - moy.coef[3] : 0;
		end_average_calc(du, &moy, img_height, img_low);
		moy.coef[3] = (moy.coef[5] > 0) ? du - moy.coef[5] : du - moy.coef[4];
		moy.jh += (moy.coef[5]  > 0) ? 2 : 1;
		moy.jl++;
	}
//	describe_moy(&moy);
}


//	Quand on a le nouveau cadre on decide si on recalcule ou pas


/*
**	-le redimentionement d'une fenetre
**	-la gestion du recalcule de img_height
**	-la gestion des calcule de bande pour le scroling
*/
