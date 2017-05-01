/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 03:13:32 by fjanoty           #+#    #+#             */
/*   Updated: 2017/05/01 05:28:51 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_math.h"


void	mat_set_id(float mat[DIM][DIM])
{
	int	i;
	int	j;

	j = 0;
	while (j < DIM)
	{
		i = 0;
		while (i < DIM)
		{
			mat[j][i] = (i == j);
			i++;
		}
		j++;
	}
}

void	mat_set_one_rot(float mat[DIM][DIM], int id1, int id2, float ang)
{
	bzero(mat, sizeof(float) * DIM * DIM);
	mat[id1][id1] = cos(ang);
	mat[id2][id2] = cos(ang);
	mat[id1][id2] = -sin(ang);
	mat[id2][id1] = sin(ang);
}

void	mat_set_all_rot(float mat[DIM][DIM], float ang[DIM])
{
	float	rot_tmp[DIM][DIM];
	int	i;
	int	j;

	mat_set_id(mat);
	i = 0;
	while (i < DIM)
	{
		mat_set_one_rot(rot_tmp, (i + 1) % 3, (i + 2) % 3, ang[i]);
		mat_mult_mat(rot_tmp, mat, mat);
		i++;
	}
}

void	mat_mult_mat(float src_l[DIM][DIM], float src_r[DIM][DIM], float dst[DIM][DIM])
{
	int	i;
	int	j;

	j = 0;
	while (j < DIM)
	{
		i = 0;
		while (i < DIM)
		{
			i++;
		}
		j++;
	}
}

void	mat_mult_vec(float mat[DIM][DIM], float vec_src[DIM], float vec_dst[DIM])
{
	float	tmp[DIM];
	int	i;
	int	j;

	j = 0;
	while (j < DIM)
	{
		tmp[j] = 0;
		i = 0;
		while (i < DIM)
		{
			tmp[j] += vec_src[i] * mat[j][i];
			i++;
		}
		j++;
	}
	memmove(vec_dst, tmp, sizeof(tmp));
}
