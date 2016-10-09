/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone_maj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 02:02:08 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/09 05:50:41 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	-iteration maximale ->	affichable ?	<==	depend du zoom
**		((plus petit cote) * (plus petit coef) ^ iter ) > 1
**	-zoom				->	calcul inteligent des zone afichable
**	-progression recursive a la vole
**	-modification des parametre en directe
*/

double	get_min_dist(t_polygone *node)
{
	double		min;
	double		dist;
	t_matrix	*diff;

	if (node && (diff = matrix_copy(node->pos)))
	{
		matrix_sub_in(node->next->pos, node->pos, diff);
		min = sqrt(matrix_dot_product(diff, diff));
		while (node->next)
		{
			matrix_sub_in(node->next->pos, node->pos, diff);
			dist = sqrt(matrix_dot_product(diff, diff));
			if (dist < min)
				min = dist;
			node = node->next;
		}
		return (dist);
	}
	return (0);
}

int	nb_iter_koch(t_polygone *base, t_polygone *mult)
{
	int		i;
	double	min_base;
	double	min_mult;
	double	result;

	min_base = get_min_dist(base);
	min_mult = get_min_dist(mult);
	i = 0;
	result = min_base;
	while (result >= 1)
	{
		result *= min_mult;
		i++;
	}
	return (i);
}

void	calcul_and_print(t_polygone *seg, t_polygone *mult, int iter, t_env *e)
{
	t_polygone	*cpy;
	t_polygone	*to_insert;

	if (seg && mult)
	{
		if (iter > 1)
		{
			while (seg->next)
			{
				cpy = NULL;
				cpy = copy_node(seg, seg->lvl);
				cpy->next = copy_node(seg->next, seg->lvl);
				if (!(to_insert = creat_insert(cpy, mult))
					|| !(insert_portion(&cpy, to_insert)))
					ft_putstr("error on calcul\n");
				calcul_and_print(cpy, mult, iter - 1, e);
				polygone_destroy(&cpy);
				seg = seg->next;
			}
		}
		else
		{
			print_polygone(e, seg);
		}
	}
}
