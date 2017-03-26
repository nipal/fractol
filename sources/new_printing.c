/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_printing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 00:36:43 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/22 14:59:41 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "c_maths.h"
#include <mlx.h>

void					actu_win_rest(t_win *w)
{
	mlx_put_image_to_window(w->e->mlx, w->win, w->img, 0, 0);
	mlx_do_sync(w->e->mlx);
	ft_bzero(w->data, sizeof(t_pix) * w->size_x * w->size_y);
}

void					actu_win(t_win *w)
{
	mlx_put_image_to_window(w->e->mlx, w->win, w->img, 0, 0);
	mlx_do_sync(w->e->mlx);
}

double					get_polygone_len(t_polygone *seg)
{
	double	i;

	i = 0;
	while (seg)
	{
		seg = seg->next;
		i++;
	}
	return (i);
}

static	inline	void	init_pt(t_matrix *pta, t_matrix *ptb, double *data
		, int no)
{
	pta->x = 1 + (no * 0);
	ptb->x = 1;
	pta->y = 3;
	ptb->y = 3;
	pta->m = data;
	ptb->m = data + 3;
}

void					draw_simple_polygone(t_win *w, t_polygone *node)
{
	static	double			data[6];
	static	t_matrix		pta;
	static	t_matrix		ptb;
	static	int				init = 1;
	t_matrix				*mt;

	mt = NULL;
	init = 1;
	if (init)
		init_pt(&pta, &ptb, data, (init = 0));
	if (!node)
		return ;
	while (node->next)
	{
		if (!get_pos_to_draw(w, node, &pta, &ptb)
			|| !(mt = init_mat_line(&pta, &ptb, node->col, node->next->col)))
		{
			node = node->next;
			matrix_free(&mt);
			continue ;
		}
		draw_line2(w, mt);
		matrix_free(&mt);
		node = node->next;
	}
}
