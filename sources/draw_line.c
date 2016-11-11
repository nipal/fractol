/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 02:43:21 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/10 00:19:36 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "c_maths.h"

int			draw_line(t_env *e, t_matrix *mat_line)
{
	int			i;
	int			size;
	t_matrix	*diff;
	t_matrix	*org;
	t_matrix	*print;

	if (!(mat_line)
		|| !(diff = matrix_init(6, 1))
		|| !(org = matrix_init(6, 1)))
		return (0);
	i = -1;
	ft_memmove(org->m, mat_line->m, sizeof(double) * 6);
	ft_memmove(diff->m, mat_line->m + 6, sizeof(double) * 6);
	size = (int)(mat_line->m[NORME] + 0.5);
	while (++i <= size)
	{
		if (!(print = matrix_add(org, diff)))
			return (0);
		vectpx_to_img(e, print);
		matrix_free(&org);
		org = print;
	}
	matrix_free(&diff);
	matrix_free(&org);
	return (1);
}

t_matrix	*init_mat_line(t_matrix *pt1, t_matrix *pt2,
			t_matrix *c1, t_matrix *c2)
{
	t_matrix	*mat_line;
	t_matrix	*diff;
	double		norme;

	mat_line = NULL;
	diff = NULL;
	if (!(mat_line = matrix_init(14, 1))
		|| !pt1 || !pt2 || !c1 || !c2
		|| ((!(diff = matrix_sub(pt2, pt1)) && matrix_free(&mat_line))))
		return (NULL);
	diff->m[Z] = 0;
	norme = MAX(ABS(diff->m[0]), ABS(diff->m[1]));
	mat_line->m[NORME] = norme;
	matrix_scalar_product(diff, 1 / norme);
	ft_memmove(mat_line->m, pt1->m, sizeof(double) * 3);
	ft_memmove(mat_line->m + 3, c1->m, sizeof(double) * 3);
	ft_memmove(mat_line->m + 6, diff->m, sizeof(double) * 3);
	matrix_free(&diff);
	matrix_scalar_product(diff = matrix_sub(c2, c1), 1 / norme);
	ft_memmove(mat_line->m + 9, diff->m, sizeof(double) * 3);
	matrix_free(&diff);
	return (mat_line);
}

void		trace_line(double *pt1, double *pt2, double *c1, double *c2)
{
	static	t_env	*e = NULL;
	t_matrix		*(sum[4]);
	t_matrix		*mat_line;

	if (!(e))
	{
		if (!(e = get_env(NULL)))
			return ;
	}
	if (!(sum[0] = vect_new_vert(pt1, 3))
		|| !(sum[1] = vect_new_vert(pt2, 3))
		|| !(sum[2] = vect_new_vert(c1, 3))
		|| !(sum[3] = vect_new_vert(c2, 3)))
		return ;
	if (!(mat_line = init_mat_line(sum[0], sum[1], sum[2], sum[3])))
		return ;
	draw_line(e, mat_line);
	if (matrix_free(sum) && matrix_free(sum + 1) && matrix_free(sum + 2)
			&& matrix_free(sum + 3))
		return ;
}


//t_matrix	*tsl_to_rvb_new(double t, double s, double l)
//	la il faut tracer un truc rigolo en fonction de plein de chose, la profondeur deja ensuite la distance
void		trace_seg_line(t_env *e, t_polygone *node)
{
	static	double	increm = 0;
	double			max = 500;
	t_matrix		*mat_line;
	t_matrix		*color1;
	t_matrix		*color2;

	double			t1;
	double			t2;
	double			s1;
	double			s2;
	double			l1;
	double			l2;
	double			lvl1;
	double			lvl2;
	double			iter;
	double			focus;
	double			centre;


	focus = 0.2;
	centre = 0.9;
	increm += 0.1;
	if (node && node->next)
	{
		lvl1 = node->lvl;
		lvl2 = node->next->lvl;
		iter = e->iter_koch;
		max = MAX(iter, 3);
		max = MAX(max, lvl1);
		max = MAX(max, lvl2);
		t1 = 360 * (((1 - centre)) + focus * ((lvl1 + 1) / (max + 1)));
		t2 = 360 * (((1 - centre)) + focus * ((lvl2 + 1) / (max + 1)));


		s1 = 0.99 - 0.35 * ((lvl1 + 1.0) / (max + 1.0));
		s2 = 0.99 - 0.35 * ((lvl2 + 1.0) / (max + 1.0));

		l1 = 0.89 - 0.70 * ((lvl1 + 1.0) / (max + 1.0));
		l2 = 0.89 - 0.70 * ((lvl2 + 1.0) / (max + 1.0));
//		dprintf(1, "lvl:%d\n", node->lvl);
//		dprintf(1, "focus:%.2f	centre:%.2f	max:%.2f	lvl1:%.2f	lvl2:%.2f\n", focus, centre, max, lvl1, lvl2);
//dprintf(1, "t1:%.2f	t2:%.2f	s1:%.2f	s2:%.2f	l1:%.2f	l2:%.2f\n", t1, t2, s1, s2, l1, l2);
//		dprintf(1, "increm:%.2f	/ max%f.2	=	%f.2\n", increm, max, teinte1);
	//	dprintf(1, "t1:%f.2\tt2:%f.2\n", teinte1, teinte2);
		if (!(color1 = tsl_to_rvb_new(t1, s1, l1))
			|| !(color2 = tsl_to_rvb_new(t2, s2, l2)))

//		if (!(color1 = vect_new_vertfd(255, 255, 255))
//			|| !(color2 = vect_new_vertfd(255, 255, 255)))
			return ;
		if (!(mat_line = init_mat_line(node->pos, node->next->pos
					, color1, color2)))
			return ;
		draw_line(e, mat_line);
		matrix_free(&color1);
		matrix_free(&color2);
		matrix_free(&mat_line);
	}
}
