/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 22:04:45 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/09 06:52:33 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	On definie un segement horizontal en bas de la fenetre
**	On lui aplique la transformation et on l'affiche a l'initialisation du triangle
*/

void	init_trans_control(t_env *e)
{
	//	on cree le segment
	double	pos[3];
	double	col[3];
	t_polygone	*node;

	e->trans_controle = NULL;
	pos[1] = SIZE_Y * 0.35;
	pos[0] = SIZE_X * 0.20;
	pos[2] = 0;
	col[0] = 250;
	col[1] = 250;
	col[2] = 250;
	if (!(node = creat_node(0, pos, col)))
		return ;
	push_back(&(e->trans_controle), node);
	pos[0] = SIZE_X * 0.45;
	if (!(node = creat_node(0, pos, col)))
		return ;
	push_back(&(e->trans_controle), node);
	
//	ft_putstr("LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL\n");
	iterate_transformation(e->trans_controle, e->transform);
//	ft_putstr("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n");
}

void	describe_one_node(t_polygone *seg)
{
	dprintf(1, "{\n\tadrr:\t{%ld}\n\tpos:\t[%f,\t%f]\n\tcol:\t[%f,\t%f,\t%f]\n\tlvl:\t%d\n}\n"
			, (long)seg
			, seg->pos->m[0]
			, seg->pos->m[1]
			, seg->col->m[0]
			, seg->col->m[1]
			, seg->col->m[2]
			, seg->lvl);
}

void	polygone_describe(t_polygone *node)
{
	while (node)
	{
		describe_one_node(node);
		node = node->next;
	}
}
