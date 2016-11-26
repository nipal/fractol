/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_printing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 00:36:43 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/26 17:57:25 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "c_maths.h"
#include <mlx.h>

void	actu_win_rest(t_win *w)
{
//	describe_window(w);
	mlx_put_image_to_window(w->e->mlx, w->win, w->img, 0, 0);
	mlx_do_sync(w->e->mlx);
	ft_bzero(w->data, sizeof(t_pix) * w->size_x * w->size_y);
}

void	actu_win(t_win *w)
{
	mlx_put_image_to_window(w->e->mlx, w->win, w->img, 0, 0);
	mlx_do_sync(w->e->mlx);
}

void	draw_line3(t_matline *ml, t_win *w)
{
	t_matrix	*mat_line;
	t_matrix	*diff;
	double		norme;

	mat_line = NULL;
	diff = NULL;
	if (!ml || !(mat_line = matrix_init(14, 1))
		|| !ml->pt1 || !ml->pt2 || !ml->c1 || !ml->c2
		|| ((!(diff = matrix_sub(ml->pt2, ml->pt1)) && matrix_free(&mat_line))))
		return ;
	diff->m[Z] = 0;
	norme = MAX(ABS(diff->m[0]), ABS(diff->m[1]));
	mat_line->m[NORME] = norme;
	matrix_scalar_product(diff, 1 / norme);
	ft_memmove(mat_line->m, ml->pt1->m, sizeof(double) * 3);
	ft_memmove(mat_line->m + 3, ml->c1->m, sizeof(double) * 3);
	ft_memmove(mat_line->m + 6, diff->m, sizeof(double) * 3);
	matrix_free(&diff);
	matrix_scalar_product(diff = matrix_sub(ml->c2, ml->c1), 1 / norme);
	ft_memmove(mat_line->m + 9, diff->m, sizeof(double) * 3);
	matrix_free(&diff);
	draw_line2(w, mat_line);
}
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

	if (dist_frac < 0 || iter < 0 || prog_iter < 0 || dist_frac > 1 || iter > 1)
	// || prog_iter > 1)
	{
		ft_putstr("color param error\n");
		char *let = NULL;
		ft_putstr(let + 3);
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
	cc->len_mult = get_polygone_len(mult);
	cc->min_val_trans = get_min_dist(mult);
	cc->mult = mult;
	cc->w = w;
	if (!(cc->diff = matrix_init(1, 3)))
		return (0);
	cc->mouse = w->mouse;
	cc->prev_mouse = w->prev_mouse;
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
	if (!seg || !cc->mult)
		return ;
	if (seg && (init_coef_draw(&cd, seg, iter, cc->len_mult)))
	{
		if (cd.iter < cc->max_iter)
		{
			while (seg->next)
			{
				dprintf(1, "turn:%d\n", (int)i);
			//	printf("%p\n", seg);
				if (!(cpy = copy_node(seg, seg->lvl))
					|| !(cpy->next = copy_node(seg->next, seg->lvl)))
				{
					cpy->next->next = NULL;
					matrix_sub_in(cpy->pos, cpy->next->pos, cc->diff);
					dist_2 = matrix_dot_product(cc->diff, cc->diff);
					if (dist_2 * cc->min_val_trans < 16)
					{
						dprintf(1, "too small\n");
						print_polygone2(cc, &cd, dist + i * cd.du_dist , cpy);
					}
					else if (!(cd.to_insert = creat_insert(cpy, cc->mult))
						|| !(insert_portion(&(cpy), cd.to_insert)))
						ft_putstr("error on calcul\n");
					draw2_koch_general(cpy, cc, dist + cd.du_dist * i, iter + 1);
					polygone_destroy(&(cpy));
				}
				seg = seg->next;
				i++;
			}
		}
		else
		{
			dprintf(1, "max of operation\n");
			print_polygone2(cc, &cd, dist , seg);
		}
	}
	else if (seg)
	{
		dprintf(1, "other fail\n");
		print_polygone2(cc, &cd, dist, seg);
	}
}


/*
**	ici on va faire une fonction qui s'occupe de la boucle d'impression generale
**	c'est entre autre elle qui va gerer le calcule en plusiseur fois
**	normalement c'est [lus fait pour etre recursif donc voila
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
//	x -= win->size_x / 2;
//	y -= win->size_y / 2;
	if (!win || !pos_color || x < 0 || x >= win->size_x || y < 0 || y >= win->size_y)
		return ;
//	dprintf(1, "%p\n", win->data);
//	dprintf(1, "%d\n", (int)win->data[0].nb);
	win->data[y * win->size_x + x].nb = ((int)(pos_color->m[3])) << 16
		| ((int)(pos_color->m[4])) << 8 | (int)pos_color->m[5];
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

/*
**	
*/

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
		if (!(color1 = tsl_to_rvb_new(t1, s1, l1))
			|| !(color2 = tsl_to_rvb_new(t2, s2, l2)))
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

static	inline	void	init_pt(t_matrix *pta, t_matrix *ptb, double *data, int no)
{
	pta->x = 1 + (no * 0);
	ptb->x = 1;
	pta->y = 3;
	ptb->y = 3;
	pta->m = data;
	ptb->m = data + 3;
}


int		matrix_describ(t_matrix *mat, int line, char *name)
{
	int		i;
	int		j;
	int		max_j;
	int		max_i;
	int		id;
	
	if (!mat)
		return (printf("ta matrice est trop nuuuuul\n"));
	if (!name)
		return (printf("ton nom est a chier\n"));
	max_i = (line) ? mat->y: mat->x;
	max_j = (line) ? mat->x: mat->y;
	printf("%s	%s:\n", name, ((line) ? "line" : "column"));
	j = 0;
	while (j < max_j)
	{
		i = 0;
		while (i < max_i)
		{
			id = ((line)? j : i) + mat->x * ((line) ? i : j);
			printf("[%d]:%f	", ((line)? j : i), mat->m[id]);
			i++;
		}
		printf("\n");
		j++;
	}
	printf("---\n");
	return (1);
}

void	draw_simple_polygone(t_win *w, t_polygone *node)
{
	static	double			data[6];
	static	t_matrix		pta;
	static	t_matrix		ptb;
	static	int				init = 1;
	t_matrix				*mat_line;

	mat_line = NULL;
	init = 1;
	if (init)
		init_pt(&pta, &ptb, data, (init = 0));
//	printf("yolo\n");
	if (!node)
		return;
	while (node->next)
	{
//		printf("enter\n");
		if (!get_pos_to_draw(w, node, &pta, &ptb)
			|| !(mat_line = init_mat_line(&pta, &ptb, node->col, node->next->col)))
		{
			node = node->next;
			matrix_free(&mat_line);
			continue ;
		}
//		matrix_describ(&pta, 1, "pta");
//		matrix_describ(&ptb, 1, "ptb");
		draw_line2(w, mat_line);
		matrix_free(&mat_line);
		node = node->next;
	}
}
