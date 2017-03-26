/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone_manip_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 03:40:26 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/05 03:41:43 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_polygone	*get_cluster_seg(t_polygone *node, double x, double y)
{
	t_matrix	*dx;
	t_matrix	*dy;
	t_polygone	*closer;
	double		data[7];
	t_matrix	*diff;

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
		closer = (data[4] < data[5] || data[5] < 0) ? node : closer;
		data[5] = (data[4] < data[5] || data[5] < 0) ? data[4] : data[5];
		node = node->next;
	}
	data[6] = (matrix_free(&dx) + matrix_free(&dy) + matrix_free(&diff)) * 0;
	return (closer);
}

void		insert_adding_node(t_win *w)
{
	t_polygone	*close_node;

	close_node = NULL;
	if (MOUSE_IN(&(w->e->border_b), w->mouse))
		close_node = get_cluster_seg(w->e->base_model
						, w->mouse->m[0], w->mouse->m[1]);
	else if (MOUSE_IN(&(w->e->border_t), w->mouse))
		close_node = get_cluster_seg(w->e->trans_model
						, w->mouse->m[0], w->mouse->m[1]);
	if (!close_node)
		return ;
	insert_one_node(&close_node, copy_node(w->e->actif, 0));
	actu_base(w->e, w->e->base_model);
	actu_transform(w->e, w->e->trans_model);
	print_fractal(w->e);
}

int			insert_one_node(t_polygone **target, t_polygone *src)
{
	if (!target || !src)
		return (0);
	if (*target)
	{
		src->next = (*target)->next;
		(*target)->next = src;
	}
	else
		*target = src;
	return (1);
}

int			remove_one_node(t_env *e)
{
	t_polygone	*to_rm;
	t_polygone	*beg;
	t_polygone	*node;
	t_polygone	*tmp;

	to_rm = NULL;
	beg = NULL;
	if (MOUSE_IN(&(e->border_b), e->param->mouse) && (beg = e->base_model))
		to_rm = get_closer_node(e->base_model, e->param->mouse, e->r_select);
	if (MOUSE_IN(&(e->border_t), e->param->mouse) && (beg = e->trans_model))
		to_rm = get_closer_node(e->trans_model, e->param->mouse, e->r_select);
	if (!to_rm || !beg || to_rm == beg || to_rm->next == NULL)
		return (0);
	node = beg;
	while (node->next && node->next != to_rm)
		node = node->next;
	if (!node->next)
		return (0);
	tmp = node->next;
	node->next = tmp->next;
	polygone_destroy_one(&tmp);
	(beg == e->base_model) ? actu_base(e, e->base_model) :
		actu_transform(e, e->trans_model);
	print_fractal(e);
	return (1);
}
