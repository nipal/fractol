/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_printing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 01:28:49 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/18 08:52:53 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_printing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 00:36:43 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/17 01:28:43 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "c_maths.h"

//t_matrix		*tsl_to_rvb_new(double t, double s, double l);
/*
**	dist_fractal	=>	perimetre de la fractal
**	iter			=>	la neme couche de recurtion
**	prog_iter		=>	le neme maiilon du segment
**
**		TOUT LES COEF SONT ENTRE 0 ET 1 (inclus)
**
*/
t_matrix	*define_node_color(double dist_frac, double iter, double prog_iter)
{
	t_matrix	*color;

	if (dist_frac < 0 || iter < 0 || prog_iter < 0 || dist_frac > 1 || iter > 1
			|| prog_iter > 1)
	{
		ft_putstr("color param error\n");
		return (NULL);
	}
	return((color = tsl_to_rvb_new(360 * dist_frac, iter, prog_iter)));
}

void		actual_node_color(t_matrix *col, double dist_frac, double iter, double prog_iter)
{
	t_matrix	*color;

	if (dist_frac < 0 || iter < 0 || prog_iter < 0 || dist_frac > 1 || iter > 1
			|| prog_iter > 1)
	{
		ft_putstr("color param error\n");
		return ;
	}
	if (!(color = tsl_to_rvb_new(360 * dist_frac, iter, prog_iter)))
		return ;
	col->m[0] = color->m[0];
	col->m[1] = color->m[1];
	col->m[2] = color->m[2];
	matrix_free(&color);
}

/*
**	La il faut une fonction qui actualise les couleur pour les point
*/

double		get_polygone_len(t_polygone *seg)
{
	double	i;

	i = 0;
	while (seg)
	{
		seg = seg->next;
		i++;
	}
	return (i);
}

/*
void	print_seg(t_win *w, t_polygone *seg)
{
	t_matrix	*c1;
	t_matrix	*c2;
}
*/


/*
**	delta_dist = (1 / mult_length) ^ iter;
**	il faudra aussi initialiser la structure
*/

/*
void		init_coef_print()
{
	t_coef_print	*coef;

	coef->len_mult = get_polygone_len(coef->mult);
	coef->diff = matrix_init(1, 3);
}
*/


/*
**	il faut une structure qui change et une fix
*/

int			init_coef_draw(t_coef_draw *cd, t_polygone *seg, double iter, double len_mult)
{
	if (!cd || !seg)
		return (0);
	cd->iter = iter;
	cd->len_seg = get_polygone_len(seg);
	cd->du_dist = pow(1.0 / len_mult, iter) / cd->len_seg;
	cd->to_insert = NULL;
	return (1);
}

int			init_coef_const(t_coef_const *cc, t_polygone *mult, double max_iter, t_win *w)
{
	if (!w |! cc || !mult || !(cc->diff = matrix_init(1, 3)))
		return (0);
	cc->dist = 0;
	cc->max_iter = max_iter;
	cc->mult = mult;
	cc->w = w;
	cc->len_mult = get_polygone_len(mult);
	cc->min_val_trans = get_min_dist(mult);
	return (1);
}

int			destroy_coef_const(t_coef_const *cc)
{
	if (cc)
		matrix_free(&(cc->diff));
	return (1);
}

void		draw2_koch_general(t_polygone *seg, t_coef_const *cc, double dist, double iter)
{
	t_coef_draw	cd;
	double		i;
	double		dist_2;
	t_polygone	*cpy;

	i = 0;
	if (seg && (init_coef_draw(&cd, seg, iter, cc->len_mult)))
	{
		if (cd.iter < cc->max_iter)
		{
			while (seg->next)
			{
				if (!(cpy = copy_node(seg, seg->lvl))
					|| !(cpy->next = copy_node(seg->next, seg->lvl)))
				{
					cpy->next->next = NULL;
					matrix_sub_in(cpy->pos, cpy->next->pos, cc->diff);
					dist_2 = matrix_dot_product(cc->diff, cc->diff);
					if (dist_2 * cc->min_val_trans < 16)
						print_polygone2(cc, &cd, dist + i * cd.du_dist , cpy);
					else if (!(cd.to_insert = creat_insert(cpy, cc->mult))
						|| !(insert_portion(&(cpy), cd.to_insert)))
						ft_putstr("error on calcul\n");
					draw2_koch_general(cpy, cc, dist + cd.du_dist * i, iter + 1);
					polygone_destroy(&(cpy));
					seg = seg->next;
				}
				i++;
			}
		}
		else
			print_polygone2(cc, &cd, dist + i * cd.du_dist , seg);
	}
	else if (seg)
		print_polygone2(cc, &cd, dist + i * cd.du_dist , seg);
}


/*
**	ici on va faire une fonction qui s'occupe de la boucle d'impression generale
**	c'est entre autre elle qui va gerer le calcule en plusiseur fois
*/

void		print_loop(t_env *e)
{
	t_coef_const	cc;
	
	init_coef_const(&cc, e->transform, e->iter_koch, e->param);
	draw2_koch_general(e->base, &cc, 0, 0);
	matrix_free(&(cc.diff));
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

//	void		actual_node_color(t_matrix *col, double dist_frac, double iter, double prog_iter)
//	On va tranquillement definir dist, iter et prog_iter et puis on actualise les 
//	Fonction vraiment tailler a la rache pour lutilisation particuliere
void		print_polygone2(t_coef_const *cc, t_coef_draw *cd, double dist, t_polygone *seg)
{
	double	prog_iter;

	prog_iter = 0;
	if (!seg || ! cc || !cd)
	{
		ft_putstr("preitn_polugone:	NO SEG HAHAHA\n");
		return ;
	}
	if (seg)
		actual_node_color(seg->col, dist + prog_iter * cd->du_dist, cd->iter, prog_iter);
	while (seg->next)
	{
		actual_node_color(seg->next->col, dist + prog_iter * cd->du_dist, cd->iter, prog_iter);
		trace_seg_line2(cc->w, seg);
		seg = seg->next;
		prog_iter++;
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
