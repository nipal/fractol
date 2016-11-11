/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone_transfrom.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 18:35:03 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/07 23:36:39 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	->	decrire la transformation, (base, proportion)
**	->	apliquer la transformation
**			(entre un node et son next)
*/

double		dist_to_end(t_polygone *seg)
{
	t_polygone	*last;
	double		dist;

	dist = -1;
	if (seg && (last = get_last(seg)))
	{
		dist = matrix_dot_product(seg->pos, seg->pos);
		dist += matrix_dot_product(last->pos, last->pos);
		dist = sqrt(dist);
	}
	return (dist);
}

/*
**	on recupere un segment et on en deduit un placement generique
**	a base de puetit changement de repere des famille
*/

void	init_dtab(double *tab, double valu, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		tab[i] = valu;
		i++;
	}
}

t_polygone	*adate_to_unite(t_matrix *ux, t_matrix *uy, t_matrix *org, t_polygone *src)
{
	t_polygone	*node;
	t_matrix	*pos;

//	(void)dist;
	if (!(node = (t_polygone*)malloc(sizeof(t_polygone)))
		|| !(node->pos = matrix_init(1, 3))
		|| !(node->col = matrix_copy(src->col))
		|| !(pos = matrix_sub(src->pos, org)))	
		return (NULL);
	node->lvl = src->lvl;
	pos = matrix_sub(src->pos, org);
	node->pos->m[0] = matrix_dot_product(ux, pos) + org->m[0];
	node->pos->m[1] = matrix_dot_product(uy, pos) + org->m[1];
	matrix_free(&pos);
	return (node);
}


/*
**	on defini la "matrice" de transformation d'un segment
*/
t_polygone	*transform(t_polygone *seg_beg)
{
	double		dist;
	t_polygone	*seg_end;
	t_polygone	*unite_beg;
	t_polygone	*node_u;
	t_polygone	*node_s;
	double		pos[3];
	double		col[3];
	t_matrix	*unite_x;
	t_matrix	*unite_y;
	t_env		*e;

	e = get_env(NULL);
	init_dtab(pos, 0, 3);	
	init_dtab(col, 255, 3);
	seg_end = get_last(seg_beg);
	if (!seg_beg || !(unite_x = matrix_sub(seg_end->pos, seg_beg->pos))
		|| !(unite_y = matrix_init(1, 3))
		|| !(dist = matrix_dot_product(unite_x, unite_x)))
		return (NULL);
	dist = sqrt(dist);
//	unite_x->m[0];
//	unite_x->m[1];
	unite_y->m[0] = unite_x->m[1];
	unite_y->m[1] = -unite_x->m[0];
	node_s = seg_beg;
	unite_beg = NULL;
	while (node_s->next && (node_s->next)->next)
	{
		if (!(node_u = adate_to_unite(unite_x, unite_y, seg_beg->pos, node_s->next)))
			return (NULL);
		node_u->pos->m[0] /= dist * dist;
		node_u->pos->m[1] /= dist * dist;	
		node_u->next = NULL;
		push_back(&unite_beg, node_u);
		node_s = node_s->next;
	}
	e->min_val_trans = get_min_dist(unite_beg);
	matrix_free(&unite_x);
	matrix_free(&unite_y);
//	print_polygone(get_env(NULL), unite_beg);
	return (unite_beg);
}

t_matrix	*position_transpose(t_matrix *org, t_matrix *ux, t_matrix *uy, t_matrix *dir)
{
	t_matrix	*pos;

	if (!(pos = matrix_copy(org)))
		return (NULL);
	pos->m[0] += ux->m[0] * dir->m[0] + uy->m[0] * dir->m[1];
	pos->m[1] += ux->m[1] * dir->m[0] + uy->m[1] * dir->m[1];
	return (pos);
}

//	on cree le polygone a oinserre a partir d'un segment en cosiderant selement les deux premier
t_polygone	*creat_insert(t_polygone *seg, t_polygone *transform)
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
	uy->m[0] = ux->m[1];
	uy->m[1] = -ux->m[0];
	beg_new = NULL;
	while (transform)
	{
		if (!(node_pos = position_transpose(seg->pos, ux, uy, transform->pos))
			|| !(node = creat_node_fv(seg->lvl + 1, node_pos, matrix_copy(seg->col))))
			return (NULL);
		push_back(&beg_new, node);
		transform = transform->next;
	}
	matrix_free(&ux);
	matrix_free(&uy);
	return (beg_new);
}

/*
**	on va inser dans le polygone une nouvelle portion entre chaque point
*/

void		iterate_transformation(t_polygone *polyg, t_polygone *transpose)
{
	t_polygone	*next;
	t_polygone	*to_insert;

	if (!polyg || !transpose)
		return ;
	while (polyg->next)
	{
		next = polyg->next;
		if (!(to_insert = creat_insert(polyg, transpose))
			|| !(insert_portion(&polyg, to_insert)))
			return ;
		polyg = next;
	}
}

/*
**	-on recupere la transformation
**	-on defini la transformation generique
**	-on l'aplique a tous les elements
**	-on affiche
*/
