/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_maths.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/15 14:35:08 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 19:15:02 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C_MATHS_H
# define C_MATHS_H
# include "libft.h"
# include <math.h>
# include <stdio.h>
# define TRIGO_FACT	3
# define TRIGO_ACCURACY (TRIGO_FACT * 360)

# define MIN(A, B) ((A) < (B) ? (A) : (B))
# define MAX(A, B) ((A) < (B) ? (B) : (A))

typedef struct	s_matrix
{
	double		*m;
	int			x;
	int			y;
}				t_matrix;

typedef struct	s_roots
{
	double		x1;
	double		x2;
	double		x3;
	double		x4;
	int			size;
	int			is_real;
}				t_roots;

typedef struct	s_coefs
{
	double		a;
	double		b;
	double		c;
	double		d;
	double		e;
}				t_coefs;

t_matrix		*vect_new_vertfd(double a, double b, double c);
t_matrix		*vect_new_vertfi(int a, int b, int c);
t_matrix		*vect_new_vert(double *tab, int size);
t_matrix		*vect_new_horz(double *tab, int size);
t_matrix		*vect_new_verti(int *tab, int size);
t_matrix		*vect_new_horzi(int *tab, int size);

void			matrix_display(t_matrix *a);
t_matrix		*matrix_init(int x, int y);
t_matrix		*vect_new_horzi(int *tab, int size);
t_matrix		*vect_new_verti(int *tab, int size);
t_matrix		*vect_new_horz(double *tab, int size);
t_matrix		*vect_new_vert(double *tab, int size);
t_matrix		*vect_new_vertfd(double a, double b, double c);

t_matrix		*matrix_add(t_matrix *a, t_matrix *b);
t_matrix		*matrix_add_in(t_matrix *a, t_matrix *b, t_matrix *c);
t_matrix		*matrix_sub(t_matrix *a, t_matrix *b);
int				matrix_sub_in(t_matrix *a, t_matrix *b, t_matrix *c);
t_matrix		*matrix_product(t_matrix *a, t_matrix *b);
void			matrix_product_in(t_matrix *a, t_matrix *b, t_matrix *c);
void			vector_product_in(t_matrix *a, t_matrix *b, t_matrix *result);

t_matrix		*matrix_scalar_product(t_matrix *a, double d);
t_matrix		*matrix_scalar_product_new(t_matrix *a, double d);
double			matrix_det(t_matrix *a);
t_matrix		*matrix_transpose(t_matrix *a, t_matrix *b);
double			matrix_norme(t_matrix *a);
t_matrix		*vector_product(t_matrix *a, t_matrix *b);
t_matrix		*vector_product_s(t_matrix *a, t_matrix *b, int x, int y);
void			vector_product_in(t_matrix *a, t_matrix *b, t_matrix *result);
double			matrix_dot_product(t_matrix *a, t_matrix *b);

t_matrix		*matrix_copy(t_matrix *src);
int				free_matrix(t_matrix *mat);
int				matrix_free(t_matrix **mat);

double			ft_cos(double deg);
double			ft_sin(double deg);

t_roots			eq_solve_2nd(t_coefs coefs);
t_roots			eq_solve_3rd(t_coefs coefs);
t_roots			eq_solve_4th(t_coefs coefs);

t_matrix		*matrix_buffer(t_matrix *mat);
void			matrix_put_in(double a, double b, double c, double d);
t_matrix		*matrix_put_in_new(double a, double b, double c, double d);

t_matrix		*set_rotate(double thetx, double thety, double thetz);
t_matrix		*set_translate(double dx, double dy, double dz);
t_matrix		*set_scale(double sx, double sy, double sz);

#endif
