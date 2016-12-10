/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_insert_polygone.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 00:20:14 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/09 09:59:11 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static	inline	t_matrix	*position_transpose(t_matrix *org, t_matrix *ux
		, t_matrix *uy, t_matrix *dir)
{
	t_matrix	*pos;

	if (!(pos = matrix_copy(org)))
		return (NULL);
	pos->m[0] += ux->m[0] * dir->m[0] + uy->m[0] * dir->m[1];
	pos->m[1] += ux->m[1] * dir->m[0] + uy->m[1] * dir->m[1];
	return (pos);
}

static	inline	void		push_back_opti(t_polygone **beg, t_polygone *elem)
{
	static	t_polygone	*prev = NULL;

	if (!beg)
		return ;
	if (elem)
	{
		if (!*beg)
		{
			*beg = elem;
			prev = elem;
		}
		else
		{
			if (prev)
				prev->next = elem;
			prev = elem;
		}
	}
	else
	{
		if (prev)
			prev->next = NULL;
		prev = NULL;
	}
}

t_polygone					*creat_insert(t_polygone *seg
						, t_polygone *transform)
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
			|| !(node = creat_node_fv(seg->lvl + 1, node_pos
				, matrix_copy(seg->col))))
			return (NULL);
//garbage_node(node, ADD);
	//	push_addr(14, "", node);
		push_back_opti(&beg_new, node);
		transform = transform->next;
	}
//		matrix_free(&node_pos);
	push_back_opti(&beg_new, NULL);
	(matrix_free(&ux)) ? matrix_free(&uy) : matrix_free(&uy);
	return (beg_new);
}
