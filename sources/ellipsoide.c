/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoide.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 23:41:50 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/29 00:36:50 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		draw_ellipsoide(t_win *w, t_polygone *pt);

//	void		ellipsoid_modify_centre(t_polygone *pt, t_polygone *old_pos);
//	void		ellipsoid_modify_ux(t_polygone *pt, t_polygone *old_pos);
//	void		ellipsoid_modify_uy(t_polygone *pt, t_polygone *old_pos);

t_matrix		*ellipsoide_param(t_polygone *pt, double param);
void			draw_ellipsoide(t_win *w, t_polygone *pt);
double			my_modf1(double res);

double	my_modf1(double res)
{
	res = res - (int)res + 1;
	res = res - (int)res;
	return (res);
}

t_matrix		*ellipsoide_param(t_polygone *pt, double param)
{
	double		x, y;
	double		r1;	// ux
	double		r2; // uy
	t_matrix	*result;
	t_matrix	*tmp;
	t_matrix	*ux;
	t_matrix	*uy;

	if (!pt || !(pt->next) || !(pt->next->next)
		|| !(result = matrix_init(1, 3))
		|| !(tmp = matrix_init(1, 3))
		|| !(ux = matrix_sub(pt->pos, pt->next->pos))
		|| !(uy = matrix_sub(pt->next->next->pos, pt->next->pos)))
		return (NULL);
	param = my_modf1(param);
	r1 = sqrt(matrix_dot_product(ux, ux));
	r2 = sqrt(matrix_dot_product(uy, uy));

	x = acos((param * 2 * M_PI)); 
	y = (r2 / r1) * sqrt(r1 * r1 - x * x); 
	y *= (param >= 0.5) ? -1 : 1;

	//	cacule du point restant
	matrix_scalar_product_in(ux, x, result);
	matrix_scalar_product_in(uy, y, tmp);
	matrix_add_in(result, tmp, result);
	matrix_add_in(pt->next->pos, result, result);

	matrix_free(&tmp);
	matrix_free(&ux);
	matrix_free(&uy);
	return (result);
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
