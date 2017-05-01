/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 03:04:00 by fjanoty           #+#    #+#             */
/*   Updated: 2017/05/01 03:36:00 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_MATH_H
# define VEC_MATH_H

#include <math.h>
#include <stdio.h>
#include <string.h>

# define DIM 3
//typedef float	t_vec;

void	vec_add(float src_a[DIM], float src_b[DIM], float dst[DIM]);
void	vec_sub(float src_a[DIM], float src_b[DIM], float dst[DIM]);
void	vec_cross(float src_a[DIM], float src_b[DIM], float dst[DIM]);
void	vec_scalar_prod(float src[DIM], float factor, float dst[DIM]);
void	vec_set(float vec[DIM], float a, float b, float c);
float	vec_dot(float src_a[DIM], float src_b[DIM]);
void	vec_normalise(float src[DIM], float dst[DIM]);
float	vec_get_norme(float vec[DIM]);

void	mat_set_id(float mat[DIM][DIM]);
void	mat_set_one_rot(float mat[DIM][DIM], int id1, int id2, float ang);
void	mat_set_all_rot(float mat[DIM][DIM], float ang[DIM]);
void	mat_mult_mat(float src_l[DIM][DIM], float src_r[DIM][DIM], float dst[DIM][DIM]);
void	mat_mult_vec(float mat[DIM][DIM], float vec_src[DIM], float vec_dst[DIM]);


#endif
