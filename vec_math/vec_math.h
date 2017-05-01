/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 03:04:00 by fjanoty           #+#    #+#             */
/*   Updated: 2017/05/01 08:15:32 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_MATH_H
# define VEC_MATH_H

#include <math.h>
#include <stdio.h>
#include <string.h>

# define DIM 3
//typedef float	t_vec;

typedef	union	u_axes
{
	float		comp[DIM][DIM];
	float		all[DIM * DIM];
}				t_axes;

typedef	struct	s_basis
{
	float	pos[3];
	float*	axes[DIM];
	float	ux[DIM];
	float	uy[DIM];
	float	uz[DIM];
}				t_basis;

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

void	basis_init(t_basis *b);
void	basis_set(t_basis *b, float ux[DIM], float uy[DIM], float uz[DIM]);
void	basis_normalise(t_basis *b);
void	basis_orthonormalise(t_basis *b);
void	basis_vec_w2b(t_basis *b, float src[DIM], float dst[DIM]); // vec: World -> Basis
void	basis_vec_b2w(t_basis *b, float src[DIM], float dst[DIM]); // vec: Basis -> World

/////////// pobablement d'autre fichier -->

typedef	struct	s_drawline
{
	t_basis		*from;
	t_basis		*to
	float		pos[DIM];
	float		col[DIM];
	float		diff_col[DIM];
	float		diff_pos[DIM]
}				t_drawline;

typedef	struct	s_cam
{
	t_basis		*b;
	t_win		*w;
}				t_cam;

t_drawline	*drawline_init_change(t_basis *from, t_basis *to);
t_drawline	*drawline_init_pos(t_drawline *dr, float p1[DIM], float p2[DIM]);
t_drawline	*drawline_init_col(t_drawline *dr, float c1[DIM], float c2[DIM]);
void		draw_line(t_cam *c, t_drawline *dr);
void		cam_init(t_cam *c, float pos[DIM], float ang[DIM]);



#endif

/*
**	Alors il reste a faire:
**			- les fonction de dessin
**			- les fonction/gestion de hook souris
**				ca serrait un peu comme si on re faisait un systeme de fenetre youpi
**	
*/
