/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rectangle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 04:54:32 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/27 23:10:14 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	paint_rectangle(t_win *w, t_matrix *col, t_border *rec)
{
	int			i;
	int			len_h;
	double		mem_a[3];
	double		mem_b[3];
	t_matrix	*mt;
	t_matrix	pta;
	t_matrix	ptb;

	mt = NULL;
	pta.m = mem_a;
	ptb.m = mem_b;
	mem_a[0] = rec->x0;
	mem_a[1] = rec->y0;
	mem_b[0] = rec->x1;
	mem_b[1] = rec->y0;
	pta.x = 1;
	pta.y = 3;
	ptb.y = 3;
	ptb.x = 1;
	len_h = rec->y1 - rec->y0;
	i = 0;
	while (i < len_h)
	{
		mem_a[1]++;
		mem_b[1]++;
		if (!(mt = init_mat_line(&pta, &ptb, col, col)))
			return ;
		draw_line2(w, mt);
		matrix_free(&mt);
		i++;
	}
}

void	draw_rectangle(t_win *w, t_matrix *col, t_border *rec)
{
	double		mem_a[3];
	double		mem_b[3];
	t_matrix	*mt;
	t_matrix	pta;
	t_matrix	ptb;

	mt = NULL;
	pta.m = mem_a;
	ptb.m = mem_b;

	//	ligne du haut
	mem_a[0] = rec->x0;
	mem_a[1] = rec->y0;
	mem_b[0] = rec->x1;
	mem_b[1] = rec->y0;
	if (!(mt = init_mat_line(&pta, &ptb, col, col)))
		return ;
	draw_line2(w, mt);
	matrix_free(&mt);

	// ligne du bas
	mem_a[1] = rec->y1;
	mem_b[1] = rec->y1;
	if (!(mt = init_mat_line(&pta, &ptb, col, col)))
		return ;
	draw_line2(w, mt);
	matrix_free(&mt);

	//ligne de gauche
	mem_a[0] = rec->x0;
	mem_a[1] = rec->y0;
	mem_b[0] = rec->x0;
	mem_b[1] = rec->y1;
	if (!(mt = init_mat_line(&pta, &ptb, col, col)))
		return ;
	draw_line2(w, mt);
	matrix_free(&mt);

	//	ligne de droite (fillon president)
	mem_a[0] = rec->x1;
	mem_b[0] = rec->x1;
	if (!(mt = init_mat_line(&pta, &ptb, col, col)))
		return ;
	draw_line2(w, mt);
	matrix_free(&mt);
}
