/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_func_inutile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 18:04:15 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/05 03:26:30 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static	inline	void		init_unite(t_matrix *ux, t_matrix *uy, double dx
					, double dy)
{
	uy->m[0] = ux->m[1];
	uy->m[1] = -ux->m[0];
	ux->m[0] *= dx;
	ux->m[1] *= dx;
	uy->m[0] *= dy;
	uy->m[1] *= dy;
}

t_polygone					*creat_insert_scale(t_polygone *seg
		, t_polygone *transform, double dx, double dy)
{
	t_polygone	*beg_new;
	t_polygone	*node;
	t_matrix	*node_pos;
	t_matrix	*ux;
	t_matrix	*uy;

	if (!seg || !seg->next
		|| (!(ux = matrix_sub(seg->next->pos, seg->pos)))
		|| (!(uy = matrix_copy(ux))))
		return (NULL);
	init_unite(ux, uy, dx, dy);
	beg_new = NULL;
	while (transform)
	{
		if (!(node_pos = position_transpose(seg->pos, ux, uy, transform->pos))
			|| !(node = creat_node_fv(seg->lvl + 1
					, node_pos, matrix_copy(seg->col))))
			return (NULL);
		push_back(&beg_new, node);
		transform = transform->next;
	}
	matrix_free(&ux);
	matrix_free(&uy);
	return (beg_new);
}



t_matrix	*rgb_to_tsl_new(double r, double g, double b);
void		rgb_to_tsl_mod(t_matrix *color);

double			diff_2(t_matrix *pt1, t_matrix *pt2)
{
	int		i;
	int		max;
	double	sum;

	if (!pt1 || !pt2 || pt1->x != pt2->x || pt1->y != pt2->y)
		return (0);
	max = pt1->x * pt1->y;
	i = 0;
	sum = 0;
	while (i < max)
	{
		sum += pt1->m[i] * pt2->m[i];
		i++;
	}
	return (sum);
}


t_matrix	*rgb_to_tsl_new(double r, double g, double b)
{
	double		max;
	double		min;
	double		croma;
	t_matrix	*tsl;

	r /= 255.0;
	g /= 255.0;
	b /= 255.0;
	if (!(tsl = matrix_init(1, 3)))
		return (NULL);
	max = MAX(r, g);
	max = MAX(max, b);
	min = MIN(r, g);
	min = MIN(min, b);
	croma = max - min;
	if ((!croma && !(tsl->m[0] = 0))
		|| (max == r && ((tsl->m[0] = 60 * modulo((((g - b) / croma) + 6.0),  6.0)) > -1))
		|| ((max == g) && ((tsl->m[0] = 60 * (((b - r) / croma) + 2.0) > -1)))
		|| ((tsl->m[0] = 60 * (((r - g) / croma) + 4.0)) > -1 ))
	tsl->m[2] = max;
	tsl->m[1] = (max == 0) ? 0 : croma / max;
	return (tsl);
}

void		rgb_to_tsl_mod(t_matrix *rgb)
{
	double		max;
	double		min;
	double		croma;
	t_matrix	*tsl;

	rgb->m[0] /= 255.0;
	rgb->m[1] /= 255.0;
	rgb->m[2] /= 255.0;
	if (!(tsl = matrix_init(1, 3)))
		return ;
	max = MAX(rgb->m[0], rgb->m[1]);
	max = MAX(max, rgb->m[2]);
	min = MIN(rgb->m[0], rgb->m[1]);
	min = MIN(min, rgb->m[2]);
	croma = max - min;
	if ((!croma && !(tsl->m[0] = 0))
		|| (max == rgb->m[0] && ((tsl->m[0] = 60 * (modulo((((rgb->m[1] - rgb->m[2]) / croma) + 6.0),  6.0))) > -1))
		|| ((max == rgb->m[1]) && ((tsl->m[0] = 60 * (((rgb->m[2] - rgb->m[0]) / croma) + 2.0) > -1)))
		|| ((tsl->m[0] = 60 * (((rgb->m[0] - rgb->m[1]) / croma) + 4.0)) > -1 ))
	tsl->m[2] = max;
	tsl->m[1] = (max == 0) ? 0 : croma / max;
	rgb->m[0] = tsl->m[0];
	rgb->m[1] = tsl->m[1];
	rgb->m[2] = tsl->m[2];
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
			i++;
		}
		printf("\n");
		j++;
	}
	printf("---\n");
	return (1);
}

void	polygone_describe(t_polygone *node)
{
	while (node)
	{
		describe_one_node(node);
		node = node->next;
	}
}

void			print_koch_fractale_anime(t_koch_const *kco, t_koch_changing kch
		, double anime)
{
	t_polygone	*cpy;
	t_polygone	*to_insert;
	double		i;
	double		du;
	double		len;

	cpy = NULL;
	i = 0;
	len = ((kch.iter == 0) ? kco->len_seg_beg : kco->len_seg);
	du = kch.prev_du / len;
	if (kch.iter >= kco->max_iter)
		draw_all_little(kco, kch, kch.seg);
	while (kch.seg->next)
	{
		if (kch.iter >= kco->max_iter || (diff_2(kch.seg->pos
						, kch.seg->next->pos) < kco->min_print))
			draw_seg_koch(kco, kch, kch.seg, i);
		else if ((cpy = copy_node(kch.seg, kch.seg->lvl))
			&& (cpy->next = copy_node(kch.seg->next, kch.seg->next->lvl))
			&& ((to_insert = creat_insert_scale(cpy, kco->trans, 1, anime))
				&& (insert_portion(&(cpy), to_insert))))
			print_koch_fractale_anime(kco, init_kch(cpy, kch.iter + 1
						, kch.dist + (du * i / len), du), anime);
		else
			return;
		i += polygone_destroy(&(cpy)) > -1;
		kch.seg = kch.seg->next;
	}
}

/*
	if (A)
		-> A'
	else if (B)   ::init::
		-> return
	else if (C)
		-> C'

====>	if ((A && A') || (B && B') || (C && C'))
*/


/*
void					translate_node2(t_env *e, t_polygone *poly)
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

*/

/*
void					draw_vertice(t_win *w, t_polygone *seg)
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

void					draw_verticies(t_win *w, t_polygone *seg)
{
	while (seg)
	{
		draw_vertice(w, seg);
		seg = seg->next;
	}
}
*/

/*
void					draw_vertice1(t_env *e, t_polygone *seg)
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
void					draw_verticies1(t_env *e, t_polygone *seg)
{
	while (seg)
	{
		draw_vertice1(e, seg);
		seg = seg->next;
	}
}
*/

/*
*/
/*
int						init_coef_draw(t_coef_draw *cd, t_polygone *seg
		, double iter, double len_mult)
{
	if (!cd || !seg)
		return (0);
	cd->iter = iter;
	cd->len_seg = get_polygone_len(seg);
	cd->du_dist = pow(1.0 / len_mult, iter) / cd->len_seg;
	cd->to_insert = NULL;
	return (1);
}
*/
/*
int						init_coef_const(t_coef_const *cc, t_polygone *mult
		, double max_iter, t_win *w)
{
	if (!w || !cc || !mult || !(cc->diff = matrix_init(1, 3)))
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
int						destroy_coef_const(t_coef_const *cc)
{
	if (cc)
		matrix_free(&(cc->diff));
	return (1);
}

*/

/*
t_matrix				*define_node_color(double dist_frac, double iter
		, double prog_iter)
{
	t_matrix	*color;

	if (dist_frac < 0 || iter < 0 || prog_iter < 0 || dist_frac > 1 || iter > 1
			|| prog_iter > 1)
	{
		ft_putstr("color param error\n");
		return (NULL);
	}
	return ((color = tsl_to_rvb_new(360 * dist_frac, iter, prog_iter)));
}
*/

/*
void					actual_node_color(t_matrix *col, double dist_frac
		, double iter, double prog_iter)
{
	t_matrix	*color;
	
	printf("yoooooooooooooooooooooooooo@@@@@@@@@@@@@@@\n");
	if (dist_frac < 0 || iter < 0 || prog_iter < 0 || dist_frac > 1 || iter > 1)
		return ;
	if (!(color = tsl_to_rvb_new(360 * dist_frac, iter, prog_iter)))
		return ;
	col->m[0] = color->m[0];
	col->m[1] = color->m[1];
	col->m[2] = color->m[2];
	matrix_free(&color);
}
*/


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
