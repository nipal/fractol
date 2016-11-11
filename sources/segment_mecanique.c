/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_mecanique.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 20:02:23 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/11 20:42:47 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_mecanique.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 04:37:12 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/10 20:02:01 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"fractol.h"

/*
**	BUTTON [1]
**		quand on clique (si on est dans un cadre b/t ) on peu: 
**			-fixer un node entre deux (si l'option espace st activer)
**				(rajouter un node en mode branch)
**			-rajouter a la fin
**	
**	BUTTON [2]
**		quand on clique on peu (si on est dans une fenetre):
**			-changer le mode ajout_fin/ajout_mid(si epace)
**	
**	pour ajouter entre deux il faut savoie quel segment est le plus pret
**
**	quand on se deplace hors du cadre on peu
**
**	LE NODE MOUSE ==> lvl = void		set_2d_landmark_incpy(double x, double y, t_matrix *dx, t_matrix *dy)
*/

void		set_2d_landmark_incpy(t_matrix *diff, t_matrix *dx, t_matrix *dy, double *dist)
{
	if (!diff || !dx || !dy || !dist)
		return ;
	*dist = sqrt(matrix_dot_product(diff, diff));
	matrix_scalar_product(diff, 1.0 / *dist);
	dx->m[0] = diff->m[0];
	dx->m[1] = diff->m[1];
	dy->m[0] = dx->m[1];
	dy->m[1] = -dx->m[0];
}

double		min_fabs(double	a, double b)
{
	a = (a < 0) ? -a : a;
	b = (a < 0) ? -b : b;
	return ((a < b) ? a : b);
}

double		max_fabs(double	a, double b)
{
	a = (a < 0) ? -a : a;
	b = (a < 0) ? -b : b;
	return ((a > b) ? a : b);
}

/*
**	on envoi
**	len_seg	=> data[6]
*/

double		set_dist_sepc(double *data, t_matrix *dx, t_matrix *dy, t_polygone *node)
{
	t_matrix	*pos;
	t_matrix	*inter;
	double		dist;
	double		distx_2;

	if (!data || !dx || !dy || !node || !node->next
			|| !(pos = vect_new_vertfd(data[2], data[3], 0))
			|| !(inter = matrix_sub(pos, node->pos)))
		return (2147483647);
	data[0] = matrix_dot_product(dx, inter);
	data[1] = matrix_dot_product(dy, inter);
	if (!matrix_free(&inter) || !(inter = matrix_sub(pos, node->next->pos)))
		return (2147483647);
	dx->m[0] *= -1;
	dx->m[1] *= -1;
	distx_2 = matrix_dot_product(dx, inter);	
	if (fabs(data[0]) > data[6] || fabs(distx_2) > data[6])
	{
		data[0] = min_fabs(data[0], distx_2);
		dist = max_fabs(data[0], data[1]);
	}
	else
		dist = fabs(data[1]);
	matrix_free(&pos);
	matrix_free(&inter);
	return (dist);
}

/*
**	on va regarder pourquoi ca ne marche pas
**	
*/

t_polygone	*get_cluster_seg(t_polygone *node, double x, double y)
{
	t_matrix	*dx;
	t_matrix	*dy;
	t_polygone	*closer;
	double		data[7];
	t_matrix	*diff;
	
//	dprintf(1, "******************************************\n");
	data[5] = MAX_DIST_ADD;
	data[2] = x;
	data[3] = y;
	closer = NULL;
	if (!node || !(dx = matrix_init(1, 3))
			|| !(dy = matrix_init(1, 3))
			|| !(diff = matrix_init(1, 3)))
		return (NULL);
	while (node->next)
	{
		matrix_sub_in(node->pos, node->next->pos, diff); 
		set_2d_landmark_incpy(diff, dx, dy, data + 6);
		data[4] = set_dist_sepc(data, dx, dy, node);
//		dprintf(1, "data[4]:%f	data[5]%f\n", data[4], data[5]);
		closer = (data[4] < data[5] || data[5] < 0) ? node: closer;
		data[5] = (data[4] < data[5] || data[5] < 0) ? data[4]: data[5];
		node = node->next;
	}
	data[6] = (42) ? matrix_free(&dx) + matrix_free(&dy) + matrix_free(&diff) : -42;
	return (closer);
}

/*
** //	On pourrait faire une fonction qui defini une base em malloc || copy
*/

void	set_in_grey(t_polygone *node, double value)
{
	value = (value < 0) ? 0 : value;
	value = (value > 255) ? 255 : value;
	while (node)
	{
		node->col->m[0] = value;
		node->col->m[1] = value;
		node->col->m[2] = value;
		node = node->next;
	}
}

void	draw_prewiew(t_win *w)
{
	t_polygone	*close_node;
	t_polygone	*cpy;

	close_node = NULL;
	if (mouse_in_border(&(w->e->border_b), w->mouse))
		close_node = get_cluster_seg(w->e->base_model, w->mouse->m[0], w->mouse->m[1]);
	else if (mouse_in_border(&(w->e->border_t), w->mouse))
		close_node = get_cluster_seg(w->e->trans_model, w->mouse->m[0], w->mouse->m[1]);
	if (!close_node)
		return ;
	if (!(cpy = copy_node(close_node, 0))
		|| !(cpy->next = copy_node(w->e->actif, 0))
		|| !(cpy->next->next = copy_node(close_node->next, 0)))
		return ;
	set_in_grey(cpy, 150);
	draw_simple_polygone(w, cpy);
	polygone_destroy(&cpy);
}

void	insert_adding_node(t_win *w)
{
	t_polygone	*close_node;

	close_node = NULL;
	if (mouse_in_border(&(w->e->border_b), w->mouse))
		close_node = get_cluster_seg(w->e->base_model, w->mouse->m[0], w->mouse->m[1]);
	else if (mouse_in_border(&(w->e->border_t), w->mouse))
		close_node = get_cluster_seg(w->e->trans_model, w->mouse->m[0], w->mouse->m[1]);
	if (!close_node)
		return ;
	insert_one_node(&close_node, copy_node(w->e->actif, 0));
//	actu_base(w->e, w->e->base_model);
//	actu_base(w->e, w->e->trans_model);
//	main_work();
}
/*
**	La on va insere le point quand on clique
*/
