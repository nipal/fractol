/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_model.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 07:00:18 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/11 16:35:01 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <mlx.h>

/*
**	-pour les mouvement de souris on check la distance aux dintersection du model
**		-on a predefini un rayon
**	-si on est inferieur a 2X le rayon on affiche le disque
**		-si on clique en meme temps:	
**									==>	on deplace le point
**									==>	on recalcule le polygone transform
**									
*/

void	print_circle(int cx, int cy, double r)
{
	t_matrix	*pt1;
	t_matrix	*pt2;
	t_matrix	*col;
	double	x;

//	cx += SIZE_X / 2;
//	cy += SIZE_Y / 2;
	x = cx - r;
	if (!(pt1 = matrix_init(1, 3))
		|| !(pt2 = matrix_init(1, 3))
		|| !(col = matrix_init(1, 3)))
		return ;
	col->m[0] = 240;
	col->m[1] = 10;
	col->m[2] = 10;
	pt1->m[1] = cy;
	while (x < cx + r)
	{
		pt1->m[0] = x;
		pt2->m[0] = x + 1;
		pt1->m[1] = cy + sqrt(ABS((r * r - (x - cx) * (x - cx))));
		pt2->m[1] = cy + sqrt(ABS((r * r - (x - cx + 1) * (x - cx + 1))));
		trace_line(pt1->m, pt2->m, col->m, col->m);
		pt2->m[1] -= 2 * sqrt(ABS((r * r - (x - cx + 1) * (x - cx + 1))));
		pt1->m[1] -= 2 * sqrt(ABS((r * r - (x - cx) * (x - cx))));
		trace_line(pt1->m, pt2->m, col->m, col->m);
//dprintf(1, "%.2f	%.2f	%.2f\n%.2f	%.2f	%.2f\n", pt1->m[0], pt1->m[1], pt1->m[2], pt2->m[0], pt2->m[1], pt2->m[2]);
		pt1->m[1] = (pt2->m[1]);
		x++;
	}
}

void	print_circle_color(int cx, int cy, double r, t_matrix *col)
{
	t_matrix	*pt1;
	t_matrix	*pt2;
	double	x;

	x = cx - r;
	if (!col || !(pt1 = matrix_init(1, 3))
		|| !(pt2 = matrix_init(1, 3)))
		return ;
	pt1->m[1] = cy;
	while (x < cx + r - 1)
	{
		pt1->m[0] = x;
		pt2->m[0] = x + 1;
		pt2->m[1] = sqrt(ABS(x * x - r * r)) + cy;
		trace_line(pt1->m, pt2->m, col->m, col->m);
		pt2->m[1] = -(pt2->m[1] - cy) + cy;
		pt1->m[1] = -(pt1->m[1] - cy) + cy;
		trace_line(pt1->m, pt2->m, col->m, col->m);
		pt1->m[1] = -(pt2->m[1] - cy) + cy;
		x++;
	}
}

/*
**	il faut detecter quel intersection esy la plus proche
**	il faut aussi stoquer l'ancienne position de la souris pour faire du drag
*/

t_polygone	*get_closer_node(t_polygone *beg, t_matrix *mouse, double min_dist)
{
	t_matrix	*diff;
	t_polygone	*closer;
	double		dist;

	closer = NULL;
	if (!beg || !beg->next || !mouse || !(diff = matrix_copy(beg->pos)))
		return (NULL);
	beg = beg->next;
	while (beg->next)
	{
		matrix_sub_in(beg->pos, mouse, diff);
		diff->m[2] = 0;
		diff->m[0] += SIZE_X / 2;
		diff->m[1] += SIZE_Y / 2;
		dist = sqrt(matrix_dot_product(diff, diff));
		if (dist < min_dist)
		{
			min_dist = dist;
			closer = beg;
		}
		beg = beg->next;
	}
	return (closer);
}

void	print_mouse_close(t_env *e, t_polygone *poly)
{
	t_polygone	*node;
	double		r;

	r = e->r_select;
	if (e->mouse && poly && (node = get_closer_node(poly, e->mouse, r)))
	{
		print_circle((int)node->pos->m[0], (int)node->pos->m[1], r);
	}
}

void	translate_node(t_env *e, t_polygone *poly)
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
