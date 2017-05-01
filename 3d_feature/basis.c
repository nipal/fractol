/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 03:13:22 by fjanoty           #+#    #+#             */
/*   Updated: 2017/05/01 05:05:18 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_math.h"

void	basis_init(t_basis *b)
{
	axes[0] = &(b->ux);
	axes[1] = &(b->uy);
	axes[2] = &(b->uz);
}

void	basis_reset(t_basis *b)
{
	vec_set(b->pos, 0, 0, 0);
	vec_set(b->ux, 1, 0, 0);
	vec_set(b->uy, 0, 1, 0);
	vec_set(b->uz, 0, 0, 1);
	basis_init(b);
}

void	basis_set(t_basis *b, float ux[DIM], float uy[DIM], float uz[DIM])
{
	b->ux = ux;
	b->uy = uy;
	b->uz = uz;
}

void	basis_normalise(t_basis *b)
{
	vec_normalise(b->ux);
	vec_normalise(b->uy);
	vec_normalise(b->uz);
}

/*
**	basis_orthonormalise
**	
**	normalent a la sortie on a une base ortho normer pafait
**		par contre il faut que (ux dot_prod uy) != 0 
**		si non on ne fait rien
*/

void	basis_orthonormalise(t_basis *b)
{
	vec_cross(b->ux, b->uy, b->uz);
	vec_normalise(b->uz);
	vec_cross(b->uz, b->ux, b->uy);
	vec_normalise(b->uy);
	vec_normalise(b->ux);
}

// vec: World -> Basis
void	basis_vec_w2b(t_basis *b, float src[DIM], float dst[DIM])
{
	float	diff[DIM];
	float	tmp[DIM];
	int		i;

	vec_sub(src, b->pos, diff);
	i = 0;
	while (i < DIM)
	{
		tmp[i] = vec_dot(b->axes[i], diff);
		i++;
	}
	memmove(dst, tmp, sizeof(tmp));
}

// vec: Basis -> World
void	basis_vec_b2w(t_basis *b, float src[DIM], float dst[DIM])
{
	float	tmp[DIM];
	float	result[DIM];
	int		i;

	memmove(result, b->pos, sizeof(result));
	i = 0;
	while (i < DIM)
	{
		vec_scalar_prod(b->axes[i], src[i], tmp);
		vec_add(result, tmp2, result);
		i++;
	}
	memmove(dst, result, sizeof(result));
}
