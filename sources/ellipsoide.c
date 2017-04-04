/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoide.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 23:41:50 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/04 21:02:26 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		draw_ellipsoide(t_win *w, t_polygone *pt);

//	void		ellipsoid_modify_centre(t_polygone *pt, t_polygone *old_pos);
//	void		ellipsoid_modify_ux(t_polygone *pt, t_polygone *old_pos);
//	void		ellipsoid_modify_uy(t_polygone *pt, t_polygone *old_pos);

t_matrix		*ellipsoide_param(t_anime *pt, double param);
void			draw_ellipsoide(t_win *w, t_polygone *pt);
double			my_modf1(double res);

double	my_modf1(double res)
{
	res = res - (int)res + 1;
	res = res - (int)res;
	return (res);
}

double			get_time_ellipse_anime(t_env *e, t_anime *a)
{
	double	time;

	time_prg = (e->time.tv_sec % 10) * 1000 + (e->time.tv_usec / 1000);
	lkjlj;

	time = (() / ((double)periode));
	return (time);
}

t_matrix		*ellipsoide_shape(t_polygone *pt, double t)
{
	t_matrix	*ux, *uy, *result;
	double		x, y, speed, offset;

//		speed = (a->speed->v1 - 0.5) * MAX_SPEED;
//		offset = a->offset->v1;
//		t = t * speed + offset;
	if (!pt
		|| !(result = matrix_init(1, 3))
		|| !(ux = matrix_sub(pt->pos, pt->next->pos))
		|| !(uy = matrix_sub(pt->next->next->pos, pt->next->pos)))
		return (NULL);
	t = t * 2 * M_PI;
	x = cos(t);
	y = sin(t);
	matrix_scalar_product_in(ux, x, ux);
	matrix_scalar_product_in(uy, y, uy);
	matrix_add_in(ux, uy, result);
	matrix_free(&ux);
	matrix_free(&uy);
	return (result);
}

void			draw_preview_one_anime(t_win *w, t_anime *anime, t_matrix *pos, double time)
{
	t_matrix	*mt, *prev, *pt, *col, *tmp;
	int			i, max;
	double		param, mult;

	if (!anime || !pos || !pos
		|| !(prev = matrix_init(1, 3))
		|| !(col = vect_new_vertfd(130, 130, 130)))
		return ;

	//	on dessine le parcourt de l'ellipse
//		mult = (anime->speed->v1 - 0.5) * MAX_SPEED;
	i = 0;
	max = 100;
	while (i < max)
	{
		param = (((double) i) * mult) / ((double) max);
		if (!(tmp = ellipsoide_shape(anime->ovaloide, param))
			|| !(pt = matrix_add(tmp, pos)))
			return ;
		if (i)
		{
			if (!(mt = init_mat_line(pt, prev, col, col)))
				return ;
			draw_line2(w, mt);
			matrix_free(&mt);
		}
		matrix_copy_in(pt, prev);
		matrix_free(&pt);
		matrix_free(&tmp);
		i++;
	}
	matrix_free(&col);
	matrix_free(&prev);

//	On imprime la position du point
	if (!(col = vect_new_vertfd(150, 90, 90))
		|| !(tmp = ellipsoide_shape(anime->ovaloide, time))
		|| !(pt = matrix_add(tmp, pos)))
		return ;
	print_circle2(pt, col, 7, w);
	matrix_free(&col);
	matrix_free(&tmp);
	matrix_free(&pt);
}

void		draw_ellipsoide(t_win *w, t_polygone *pt)
{
	double		x, y;
	double		r1;	// ux
	double		r2; // uy
	double		coef_xy;
	t_matrix	*pt_a1;
	t_matrix	*pt_b1;
	t_matrix	*pt_a2;
	t_matrix	*pt_b2;
	t_matrix	*tmp;
	t_matrix	*col;
	t_matrix	*ux;
	t_matrix	*uy;
	t_matrix	*mt;

	if (!pt || !(pt->next) || !(pt->next->next))
		return ;
	if (!(pt_a1 = matrix_init(1, 3))
		|| !(pt_b1 = matrix_init(1, 3))
		|| !(pt_a2 = matrix_init(1, 3))
		|| !(pt_b2 = matrix_init(1, 3))
		|| !(tmp = matrix_init(1, 3)))
		return ;
	if (!(ux = matrix_sub(pt->pos, pt->next->pos)))
		return ;
	if (!(uy = matrix_sub(pt->next->next->pos, pt->next->pos)))
		return ;
	if (!(col = tsl_to_rvb_new(0, 0, 1)))
		return ;
	mt = NULL;
	r1 = sqrt(matrix_dot_product(ux, ux));
	r2 = sqrt(matrix_dot_product(uy, uy));
	x = r1;
	coef_xy = r2 / r1;
	matrix_copy_in(ux, pt_b1);
	matrix_copy_in(ux, pt_b2);
	matrix_add_in(pt->next->pos, pt_b1, pt_b1);
	matrix_add_in(pt->next->pos, pt_b2, pt_b2);
	matrix_scalar_product(ux, 1 / r1);
	matrix_scalar_product(uy, 1 / r2);
	while (x >= -r1)
	{
		y = coef_xy * sqrt(r1 * r1 - x * x); 

		//	calcule du point du dessu
		matrix_scalar_product_in(ux, x, pt_a1);
		matrix_scalar_product_in(uy, y, tmp);
		matrix_add_in(pt_a1, tmp, pt_a1);
		matrix_add_in(pt->next->pos, pt_a1, pt_a1);

		//	calcule du point du dessou
		matrix_scalar_product_in(ux, x, pt_a2);
		matrix_scalar_product_in(uy, -y, tmp);
		matrix_add_in(pt_a2, tmp, pt_a2);
		matrix_add_in(pt->next->pos, pt_a2, pt_a2);

		if (!(mt = init_mat_line(pt_a1, pt_b1, col, col)))
			return ;
		draw_line2(w, mt);
		matrix_free(&mt);

		if (!(mt = init_mat_line(pt_a2, pt_b2, col, col)))
			return ;
		draw_line2(w, mt);
		matrix_free(&mt);

		//	on copy les point calculer pour partir de la pour dessiner la prochaine ligne
		matrix_copy_in(pt_a1, pt_b1);
		matrix_copy_in(pt_a2, pt_b2);
		x--;
	}
		if (!(mt = init_mat_line(pt_a2, pt_a1, col, col)))
			return ;
		draw_line2(w, mt);
		matrix_free(&mt);

	matrix_free(&pt_a1);
	matrix_free(&pt_b1);
	matrix_free(&pt_a2);
	matrix_free(&pt_b2);
	matrix_free(&tmp);
	matrix_free(&ux);
	matrix_free(&uy);
	matrix_free(&col);
}

/*Alors si on veu faire la meme chose mais juse pour l'evaluation de point*/
