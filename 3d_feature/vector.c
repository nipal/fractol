/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 03:13:38 by fjanoty           #+#    #+#             */
/*   Updated: 2017/05/01 03:23:06 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_math.h"

void	vec_add(float src_a[DIM], float src_b[DIM], float dst[DIM])
{
	int		i;
	
	i = 0;
	while (i < DIM)
	{
		dst[i] = src_a[i] + src_b[i];
		i++;
	}
}

void	vec_sub(float src_a[DIM], float src_b[DIM], float dst[DIM])
{
	int		i;
	
	i = 0;
	while (i < DIM)
	{
		dst[i] = src_a[i] - src_b[i];
		i++;
	}
}

void	vec_add(float src_a[DIM], float src_b[DIM], float dst[DIM])
{
	int		i;
	float	res[DIM];
	
	i = 0;
	while (i < DIM)
	{
		res[i] = src_a[i] src_b[i];
		i++;
	}
	memove(dst, res, sizeof(res));
}
