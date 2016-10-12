/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 18:29:52 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/09 05:44:47 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			polygone_destroy(t_polygone **begin)
{
	t_polygone	*node;
	t_polygone	*tmp;

	if (!begin || *begin)
		return (0);
	node = *begin;
	while (node)
	{
		tmp = node->next;
		matrix_free(&(node->pos));
		matrix_free(&(node->col));
		free(node);
		node = tmp;
	}
	*begin = NULL;
	return (1);
}
