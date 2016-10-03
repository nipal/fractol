/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 03:45:15 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 23:47:02 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "fdf.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int			draw_line(t_env *e, t_matrix *mat_line)
{
	int			i;
	int			size;
	t_matrix	*diff;
	t_matrix	*org;
	t_matrix	*print;

	if (!(mat_line)
		|| !(diff = matrix_init(6, 1))
		|| !(org = matrix_init(6, 1)))
		return (0);
	i = -1;
	ft_memmove(org->m, mat_line->m, sizeof(double) * 6);
	ft_memmove(diff->m, mat_line->m + 6, sizeof(double) * 6);
	size = (int)(mat_line->m[NORME] + 0.5);
	while (++i < size)
	{
		if (!(print = matrix_add(org, diff)))
			return (0);
		vectpx_to_img(e, print);
		matrix_free(&org);
		org = print;
	}
	matrix_free(&diff);
	matrix_free(&org);
	return (1);
}

t_matrix	*init_mat_line(t_matrix *pt1, t_matrix *pt2,
			t_matrix *c1, t_matrix *c2)
{
	t_matrix	*mat_line;
	t_matrix	*diff;
	double		norme;

	mat_line = NULL;
	diff = NULL;
	if (!(mat_line = matrix_init(14, 1))
		|| !pt1 || !pt2 || !c1 || !c2
		|| ((!(diff = matrix_sub(pt2, pt1)) && matrix_free(&mat_line))))
		return (NULL);
	diff->m[Z] = 0;
	norme = MAX(ABS(diff->m[0]), ABS(diff->m[1]));
	mat_line->m[NORME] = norme;
	matrix_scalar_product(diff, 1 / norme);
	ft_memmove(mat_line->m, pt1->m, sizeof(double) * 3);
	ft_memmove(mat_line->m + 3, c1->m, sizeof(double) * 3);
	ft_memmove(mat_line->m + 6, diff->m, sizeof(double) * 3);
	matrix_free(&diff);
	matrix_scalar_product(diff = matrix_sub(c2, c1), 1 / norme);
	ft_memmove(mat_line->m + 9, diff->m, sizeof(double) * 3);
	matrix_free(&diff);
	return (mat_line);
}

t_matrix	*init_mat_line2(t_matrix *pt_color, t_matrix *pt3, t_matrix *c3)
{
	t_matrix	*pt_inter;
	t_matrix	*cl_inter;
	t_matrix	*mat_l;
	t_matrix	*diff;

	if (!(pt_color) || !(pt3) || !(c3) || !(mat_l = matrix_init(14, 1))
		|| !pt_color || !pt3 || !c3 || !(pt_inter = matrix_init(1, 3))
		|| !(cl_inter = matrix_init(1, 3)))
		return (NULL);
	ft_memmove(pt_inter->m, pt_color->m, sizeof(double) * 3);
	if (!(diff = matrix_sub(pt_inter, pt3)) && matrix_free(&mat_l))
		return (NULL);
	mat_l->m[NORME] = MAX(ABS(diff->m[0]), ABS(diff->m[1]));
	diff = matrix_scalar_product(diff, 1 / mat_l->m[NORME]);
	ft_memmove(mat_l->m, pt3->m, sizeof(double) * 3);
	ft_memmove(mat_l->m + 3, c3->m, sizeof(double) * 3);
	ft_memmove(mat_l->m + 6, diff->m, sizeof(double) * 3);
	matrix_free(&diff);
	ft_memmove(cl_inter->m, pt_color->m + 3, sizeof(double) * 3);
	matrix_scalar_product(diff = matrix_sub(cl_inter, c3), 1 / mat_l->m[NORME]);
	ft_memmove(mat_l->m + 9, diff->m, sizeof(double) * 3);
	if (matrix_free(&diff) && matrix_free(&cl_inter) && matrix_free(&pt_inter))
		;
	return (mat_l);
}

int			draw_triangle(t_env *e, t_matrix *mat_line,
		t_matrix *pt3, t_matrix *c3)
{
	int			i;
	t_matrix	*diff;
	t_matrix	*org;
	t_matrix	*print;
	t_matrix	*mat_line2;

	print = NULL;
	if ((!(mat_line))
		|| (!(diff = matrix_init(6, 1)))
		|| (!(org = matrix_init(6, 1)) && matrix_free(&diff)))
		return (0);
	ft_memmove(org->m, mat_line->m, sizeof(double) * 6);
	ft_memmove(diff->m, mat_line->m + 6, sizeof(double) * 6);
	i = -1;
	while (++i < (int)(mat_line->m[NORME] + 0.5))
	{
		print = matrix_add(org, diff);
		if ((mat_line2 = init_mat_line2(print, pt3, c3))
			&& draw_line(e, mat_line2) > -1 && matrix_free(&mat_line2)
			&& matrix_free(&org) && (org = print))
			;
	}
	matrix_free(&diff);
	matrix_free(&print);
	return (1);
}
