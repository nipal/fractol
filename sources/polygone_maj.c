/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone_maj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 02:02:08 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/18 18:21:27 by fjanoty          ###   ########.fr       */
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

	if (node && node->next && (diff = matrix_copy(node->pos)))
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
	return (1);
}

int	nb_iter_koch(t_polygone *base, t_polygone *mult)
{
	int		i;
	double	min_base;
	double	min_mult;
	double	result;
	double	prev;

	if (!base || !mult)
		return (0);
	min_base = get_min_dist(base);
	min_mult = get_min_dist(mult);
	i = 0;
	result = min_base;
	prev = result;
	while (result >= 1 && result <= prev)
	{
		result *= min_mult;
		i++;
	}
	return (i);
}


int		polygone_push_back(t_polygone **begin, t_polygone *node)
{
	t_polygone	*elem;

	if (!begin)
	{
		return (0);
	}
	elem = *begin;
	if (!elem)
		*begin = node;
	else
	{
		while (elem->next)
			elem = elem->next;
		elem->next = node;
	}
	return (1);
}

int		polygone_push_befor_last(t_polygone **begin, t_polygone *node)
{
	t_polygone	*elem;

	if (!begin)
	{
		return (0);
	}
	elem = *begin;
	if (!elem)
		*begin = node;
	else
	{
		if (!elem->next)
		{
			node->next = elem;
			*begin = node;
			return (0);
		}
		while (elem->next->next)
			elem = elem->next;
		node->next = elem->next;
		elem->next = node;
	}
	return (1);
}

int		polygone_forget_last(t_polygone **begin)
{
	t_polygone	*elem;

	if (!begin)
		return (0);
	elem = *begin;
	if (!elem || !elem->next)
	{
		if (elem && !elem->next)
			*begin = NULL;
		return (0);
	}
	while (elem->next->next)
		elem = elem->next;
	elem->next = NULL;
	return (1);
}
