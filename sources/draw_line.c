/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 02:43:21 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/22 15:57:27 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "c_maths.h"

void					paint_circle(t_matrix *mid, t_matrix *col, double r
		, t_win *w)
{
	t_matrix	*pt1;
	t_matrix	*pt2;
	t_matrix	*mat_line;
	t_matrix	*c2;
	double		h[3];

	c2 = NULL;
	if (!mid || !w || !(pt1 = matrix_init(1, 3))
		|| (!col && !(c2 = vect_new_vertfd(50, 100, 70)))
		|| !(pt2 = matrix_init(1, 3)))
		return ;
	col = (col) ? col : c2;
	h[2] = mid->m[0] - r + 1;
	while (++h[2] < mid->m[0] + r)
	{
		pt1->m[0] = h[2];
		pt2->m[0] = h[2];
		h[0] = height_circle(r, h[2] - mid->m[0]);
		pt1->m[1] = mid->m[1] + h[0];
		pt2->m[1] = mid->m[1] - h[0];
		mat_line = init_mat_line(pt1, pt2, col, col);
		draw_line2(w, mat_line);
		matrix_free(&mat_line);
	}
	(matrix_free(&pt1) && matrix_free(&pt2)) ? matrix_free(&c2) : 0;
}

void					vectpx_to_img2(t_win *win, t_matrix *pos_color)
{
	int		x;
	int		y;

	x = (int)pos_color->m[0];
	y = (int)pos_color->m[1];
	if (!win || !pos_color || x < 0 || x >= win->size_x || y < 0
			|| y >= win->size_y)
		return ;
	win->data[y * win->size_x + x].nb = ((int)(pos_color->m[3])) << 16
		| ((int)(pos_color->m[4])) << 8 | (int)pos_color->m[5];
}

int						draw_line2(t_win *win, t_matrix *mat_line)
{
	int			i;
	int			size;
	t_matrix	*diff;
	t_matrix	*org;
	t_matrix	*print;

//			if (ft_strcmp(win->name, "fractal") == 0)
//			{
//				i = *((int*)(-2));
//			}
//			return (1);
	//	printf("win:%s\n", win->name);
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
		vectpx_to_img2(win, print);
		matrix_free(&org);
		org = print;
	}
	matrix_free(&org);
	matrix_free(&diff);
	return (1);
}

void					draw_line3(t_matline *ml, t_win *w)
{
	static	t_matrix	*mat_line = NULL;
	t_matrix			*diff;
	double				norme;

	diff = NULL;
	if (!ml || (!mat_line && !(mat_line = matrix_init(1, 14)))
		|| !ml->pt1 || !ml->pt2 || !ml->c1 || !ml->c2
		|| ((!(diff = matrix_sub(ml->pt2, ml->pt1)))))
		return ;
	diff->m[Z] = 0;
	norme = MAX(ABS(diff->m[0]), ABS(diff->m[1]));
	mat_line->m[NORME] = norme;
	matrix_scalar_product(diff, 1 / norme);
	ft_memmove(mat_line->m, ml->pt1->m, sizeof(double) * 3);
	ft_memmove(mat_line->m + 3, ml->c1->m, sizeof(double) * 3);
	ft_memmove(mat_line->m + 6, diff->m, sizeof(double) * 3);
	matrix_free(&diff);
	matrix_scalar_product(diff = matrix_sub(ml->c2, ml->c1), 1 / norme);
	ft_memmove(mat_line->m + 9, diff->m, sizeof(double) * 3);
	matrix_free(&diff);
	draw_line2(w, mat_line);
}

t_matrix				*init_mat_line(t_matrix *pt1, t_matrix *pt2,
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
