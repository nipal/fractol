/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_printing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 00:36:43 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/16 19:22:58 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "c_maths.h"

t_matrix	*define_node_color(double dist_frac, double u_iter)
{

}

void		vectpx_to_img2(t_win *win, t_matrix *pos_color)
{
	int		x;
	int		y;

	x = (int)pos_color->m[0];
	y = (int)pos_color->m[1];
	x += SIZE_Y / 2;
	y += SIZE_X / 2;
	if (x < 0 || x >= win->size_x || y < 0 || y >= win->size_y)
		return ;
	win->data[y * win->size_x + x].nb = ((int)pos_color->m[3]) << 16
		| ((int)pos_color->m[4]) << 8 | (int)pos_color->m[5];
}

int			draw_line2(t_win *win, t_matrix *mat_line)
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
	while (++i < size)
	{
		if (!(print = matrix_add(org, diff)))
			return (0);
		vectpx_to_img2(win, print);
		matrix_free(&org);
		org = print;
	}
	matrix_free(&diff);
	matrix_free(&org);
	return (1);
}

void		trace_line2(double *pt1, double *pt2, double *c1, double *c2)
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

void		trace_seg_line2(t_win *w, t_polygone *node)
{
	static	double	increm = 0;
	double			max = 500;
	t_matrix		*mat_line;
	t_matrix		*color1;
	t_matrix		*color2;
	t_env			*e;

	double			t1;
	double			t2;
	double			s1;
	double			s2;
	double			l1;
	double			l2;
	double			lvl1;
	double			lvl2;
	double			focus;
	double			iter;
	double			centre;


	e = get_env(NULL);
	iter = e->iter_koch;
	focus = 0.1;
	centre = 0.6;
	increm += 0.1;

	if (node && node->next)
	{
		lvl1 = node->lvl;
		lvl2 = node->next->lvl;
		max = MAX(iter, 2);
		max = MAX(max, lvl1);
		max = MAX(max, lvl2);
		t1 = 360 * (((1 - centre)) + focus * ((lvl1) / (max)));
		t2 = 360 * (((1 - centre)) + focus * ((lvl2) / max));


		s1 = ((lvl1 + 1) / (max + 1));
		s2 = ((lvl2 + 1) / (max + 1));

		l1 = 0.9 - 0.8 * ((lvl1 + 1) / (max + 1));;
		l2 = 0.9 - 0.8 * ((lvl2 + 1) / (max + 1));;
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
		draw_line2(w, mat_line);
		matrix_free(&color1);
		matrix_free(&color2);
		matrix_free(&mat_line);
	}
}

void		print_polygone2(t_win *win, t_polygone *seg)
{
	if (!seg)
	{
//		ft_putstr("preitn_polugone:	NO SEG HAHAHA\n");
		return ;
	}
	while (seg->next)
	{
		trace_seg_line2(win, seg);
		seg = seg->next;
	}
}

void	translate_node2(t_env *e, t_polygone *poly)
{
	t_polygone *node;

	if ((node = get_closer_node(poly, e->prev_mouse, e->r_select)))
	{
		node->pos->m[0] += e->mouse->m[0] - e->prev_mouse->m[0];
		node->pos->m[1] += e->mouse->m[1] - e->prev_mouse->m[1];
		polygone_destroy(&(e->transform));
		e->transform = transform(poly);
	}
}

void	draw_vertice(t_win *w, t_polygone *seg)
{
	double		pc[6];
	t_matrix	*pos_color;

	pc[0] = seg->pos->m[0];
	pc[1] = seg->pos->m[1];
	pc[3] = 250;
	pc[4] = 250;
	pc[5] = 250;
	if (!seg || !w || !(pos_color = vect_new_vert(pc, 6)))
		return ;
	vectpx_to_img2(w, pos_color);
	matrix_free(&pos_color);
}

void	draw_verticies(t_win *w, t_polygone *seg)
{
	while (seg)
	{
		draw_vertice(w, seg);
		seg = seg->next;
	}
}

void	draw_vertice1(t_env *e, t_polygone *seg)
{
	double		pc[6];
	t_matrix	*pos_color;

	pc[0] = seg->pos->m[0];
	pc[1] = seg->pos->m[1];
	pc[3] = 250;
	pc[4] = 250;
	pc[5] = 250;
	if (!seg || !e || !(pos_color = vect_new_vert(pc, 6)))
		return ;
	vectpx_to_img(e, pos_color);
	matrix_free(&pos_color);
}

void	draw_verticies1(t_env *e, t_polygone *seg)
{
	while (seg)
	{
		draw_vertice1(e, seg);
		seg = seg->next;
	}

}
