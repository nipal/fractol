/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 22:04:45 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/10 08:58:06 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	On definie un segement horizontal en bas de la fenetre
**	On lui aplique la transformation et on l'affiche a l'initialisation
**	du triangle
*/

void	init_trans_control(t_env *e)
{
	double		pos[3];
	double		col[3];
	t_polygone	*node;

	e->trans_model = NULL;
	pos[1] = SIZE_Y * 0.35;
	pos[0] = SIZE_X * 0.20;
	pos[2] = 0;
	col[0] = 250;
	col[1] = 250;
	col[2] = 250;
	if (!(node = creat_node(0, pos, col)))
		return ;
	push_back(&(e->trans_model), node);
	pos[0] = SIZE_X * 0.45;
	if (!(node = creat_node(0, pos, col)))
		return ;
	push_back(&(e->trans_model), node);
	iterate_transformation(e->trans_model, e->transform);
}

void	polygone_describe(t_polygone *node)
{
	while (node)
	{
		describe_one_node(node);
		node = node->next;
	}
}
