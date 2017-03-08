/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_manipule_basic.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 23:01:44 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/04 23:04:41 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_polygone	*get_last(t_polygone *node)
{
	if (node)
		while (node->next)
			node = node->next;
	return (node);
}

int			insert_portion(t_polygone **target, t_polygone *src)
{
	t_polygone	*tmp;

	if (!target || !src)
	{
		return (0);
	}
	if (*target)
	{
		if ((tmp = get_last(src)))
			tmp->next = (*target)->next;
		(*target)->next = src;
	}
	else
	{
		*target = src;
	}
	return (1);
}

void		push_back(t_polygone **root, t_polygone *node)
{
	t_polygone	*tmp;

	if (!root)
		return ;
	else if (*root)
	{
		if ((tmp = get_last(*root)))
			tmp->next = node;
		node->next = NULL;
	}
	else
		*root = node;
}

void		increm_polygone(int x, int y, t_env *e)
{
	add_point(&(e->actif), x, y, 0);
	if (!(e->beg_actif))
		e->beg_actif = e->actif;
}

void		add_point(t_polygone **node, int x, int y, int lvl)
{
	t_polygone	*last;
	double		pos[3];
	double		col[3];

	if (!node)
		return ;
	pos[0] = x;
	pos[1] = y;
	pos[2] = 0;
	col[0] = 250;
	col[1] = 250;
	col[2] = 250;
	if (!(last = creat_node(lvl, pos, col)))
		return ;
	if (*node)
		(*node)->next = last;
	*node = last;
	(*node)->next = NULL;
}
