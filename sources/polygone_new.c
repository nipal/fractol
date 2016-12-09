/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 18:26:18 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/09 03:30:01 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_polygone	*creat_node(int lvl, double *pos, double *color)
{
	int			i;
	t_polygone	*node;
char	dbg_c[3];
dbg_c[0] = '0' + (lvl / 10);
dbg_c[1] = '0' + (lvl % 10);

	if (!(node = (t_polygone*)malloc(sizeof(t_polygone))))
		return (NULL);
push_addr(8, dbg_c, node);
	if (!(node->pos = matrix_init(1, 3))
			|| !(node->col = matrix_init(1, 3)))
		return (NULL);
	node->lvl = lvl;
	node->next = NULL;
	i = 0;
	while (i < 3)
	{
		node->pos->m[i] = pos[i];
		node->col->m[i] = color[i];
		i++;
	}
	return (node);
}

t_polygone	*creat_node_fv(int lvl, t_matrix *pos, t_matrix *color)
{
	t_polygone	*node;

	if (!(node = (t_polygone*)malloc(sizeof(t_polygone))))
		return (NULL);
push_addr(9, "", node);
	if (!(node->pos = pos)
			|| !(node->col = color))
		return (NULL);
	node->lvl = lvl;
	node->next = NULL;
	return (node);
}

t_polygone	*copy_node(t_polygone *node, int lvl)
{
	t_polygone	*copy;

	if (!(copy = creat_node(lvl, node->pos->m, node->col->m)))
		return (NULL);
	copy->next = NULL;
	return (copy);
}
