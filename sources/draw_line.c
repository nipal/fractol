/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 02:43:21 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/07 08:39:42 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "c_maths.h"

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

void		trace_line(double *pt1, double *pt2, double *c1, double *c2)
{
	static	t_env	*e = NULL;
	t_matrix		*(sum[4]);
	t_matrix		*mat_line;

	if (!(e))
	{
		if (!(e = get_env(NULL)))
			return ;
	}
	if (!(sum[0] = vect_new_vert(pt1, 3))
		|| !(sum[1] = vect_new_vert(pt2, 3))
		|| !(sum[2] = vect_new_vert(c1, 3))
		|| !(sum[3] = vect_new_vert(c2, 3)))
		return ;
	if (!(mat_line = init_mat_line(sum[0], sum[1], sum[2], sum[3])))
		return ;
	draw_line(e, mat_line);
	if (matrix_free(sum) && matrix_free(sum + 1) && matrix_free(sum + 2)
			&& matrix_free(sum + 3))
		return ;
}

void		trace_seg_line(t_env *e, t_polygone *node)
{	
	t_matrix		*mat_line;

	if (!(mat_line = init_mat_line(node->pos, node->next->pos
				, node->col, node->next->col)))
		return ;
	draw_line(e, mat_line);
	matrix_free(&mat_line);
}
