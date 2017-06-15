/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_koch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 13:27:00 by fjanoty           #+#    #+#             */
/*   Updated: 2017/06/15 19:15:57 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	quand on reset l'un au l'aure on remet tout a zero
**	quand on clique dans un cadrde ET que base OU transform == null
*/
/*
**	si on a trouver un clique dans un cadre, on envoie le polygone assosier
**	mais ca c'est cool que pour quand on clique
**	le mieux ca serrait de reperer quand on entre et
**		on sort 				-> 	on suprime le dernier maillon
**		on rentre				->	on ajoute le maillon courrant
**		on bouge 				->	on modifi le maillon courrent
**
**		clique ET dans cadre	->	on copy le dernier maillon et on
**									le met en avant dernier
*/

t_polygone				*scale_segment(t_polygone *src, t_border *from
		, t_border *to, double *add)
{
	t_polygone	*begin_new;
	t_polygone	*new_node;
	double		scale_x;
	double		scale_y;
	double		add_s[2];

	begin_new = NULL;
	scale_x = 1.0 * (to->x1 - to->x0) / (1.0 * from->x1 - from->x0);
	scale_y = 1.0 * (to->y1 - to->y0) / (1.0 * from->y1 - from->y0);
	add_s[0] = add[0] + to->x0;
	add_s[1] = add[1] + to->y0;
	while (src)
	{
		if (!(new_node = copy_node(src, 0)))
			return (NULL);
		new_node->pos->m[0] =
			(new_node->pos->m[0] - from->x0) * scale_x + add_s[0];
		new_node->pos->m[1] =
			(new_node->pos->m[1] - from->y0) * scale_y + add_s[1];
		polygone_push_back(&begin_new, new_node);
		src = src->next;
	}
	return (begin_new);
}

double					height_circle(double r, double x)
{
	if (x <= r)
		return (sqrt(r * r - x * x));
	return (0);
}

static	inline	void	bcl_circle(t_dp p
		, t_matrix *col, const t_matrix *mid)
{
	t_matrix	*mat_line;
	t_d3		h;

	h.v0 = 0;
	h.v2 = mid->m[0] - p.r;
	while (h.v2 < mid->m[0] + p.r)
	{
		p.pt1->m[0] = h.v2;
		p.pt2->m[0] = h.v2 + 1;
		h.v0 = height_circle(p.r, h.v2 - mid->m[0]);
		h.v1 = height_circle(p.r, h.v2 - mid->m[0] + 1);
		p.pt1->m[1] = mid->m[1] + h.v0;
		p.pt2->m[1] = mid->m[1] + h.v1;
		mat_line = init_mat_line(p.pt1, p.pt2, col, col);
		draw_line2(p.w, mat_line);
		matrix_free(&mat_line);
		p.pt2->m[1] -= 2 * h.v1;
		p.pt1->m[1] -= 2 * h.v0;
		mat_line = init_mat_line(p.pt1, p.pt2, col, col);
		draw_line2(p.w, mat_line);
		matrix_free(&mat_line);
		h.v2++;
	}
}

void					print_circle2(t_matrix *mid, t_matrix *col, double r, t_win *w)
{
	t_dp		p;
	t_matrix	*c2;

	c2 = NULL;
	if (!mid || !w || !(p.pt1 = matrix_init(1, 3))
		|| (!col && !(c2 = vect_new_vertfd(180, 30, 30)))
		|| !(p.pt2 = matrix_init(1, 3)))
		return ;
	p.r = r;
	p.w = w;
	col = (col) ? col : c2;
	bcl_circle(p, col, mid);
	matrix_free(&c2);
	matrix_free(&(p.pt1));
	matrix_free(&(p.pt2));
}

int						move_the_node(t_env *e, t_polygone *seg)
{
	t_polygone *node;

	if (seg && (node = get_closer_node(seg, e->param->prev_mouse, e->r_select)))
	{
		node->pos->m[0] = e->param->mouse->m[0];
		node->pos->m[1] = e->param->mouse->m[1];
	}
	return (1);
}
