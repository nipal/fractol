/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 18:29:52 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/09 10:05:05 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			polygone_destroy_one(t_polygone **node)
{
	if (!node || !*node)
		return (1);
	matrix_free(&((*node)->pos));
	matrix_free(&((*node)->col));
	free(*node);
	*node = NULL;
	return (1);
}

int			polygone_destroy(t_polygone **begin)
{
	t_polygone	*node;
	t_polygone	*tmp;
int	debug = 0;

	if (!begin || !(*begin))
		return (1);
	node = *begin;
	while (node)
	{
		tmp = node->next;
		polygone_destroy_one(&node);
		node = tmp;
	}
	node = NULL;
	*begin = NULL;
	return (1);
}
