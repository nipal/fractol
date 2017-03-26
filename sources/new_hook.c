/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 10:37:32 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/25 19:49:06 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mouse_inside(int x, int y, t_win *w)
{
	if (!w || x < 0 || x >= w->size_x || y < 0 || y >= w->size_y)
		return (0);
	return (1);
}

int		press_key(int key_code, t_win *w)
{
	(key_code == 53) ? ft_exit(w->e) : 0;
	(key_code == 36) ? ++(w->e->max_iter) : 0;
	(key_code == 51 && w->e->max_iter > 0) ? --(w->e->max_iter) : 0;
	(key_code == 49) ? w->e->add_point = 1 : 0;
	if (key_code == 15 && ft_strcmp(w->name, "param") == 0)
	{
		if (mouse_in_border(&(w->e->border_b), w->mouse))
			reset_base(w->e);
		else if (mouse_in_border(&(w->e->border_t), w->mouse))
			reset_transform(w->e);
	}
	(key_code == 36 || key_code == 51) ? print_fractal(w->e) : (void)w;
	return (1);
}

int		release_key(int key_code, t_win *w)
{
	(key_code == 49) ? w->e->add_point = 0 : 0;
	return (1);
}

int		motion_cursor(int x, int y, t_win *w)
{
	int		on;

	w->mx = x;
	w->my = y;
	if (!ft_strcmp(w->name, "param"))
		actu_polygone_io(w->e, w);
	actu_mouse_pos(w, x, y);
	if (w->e->base_add != 0 && w->button1 && mouse_in_border(&(w->e->border_b)
				, w->mouse))
		on = move_the_node(w->e, w->e->base_model)
			+ actu_base(w->e, w->e->base_model);
	if (w->e->trans_add != 0 && w->button1 && mouse_in_border(&(w->e->border_t)
				, w->mouse))
		on = move_the_node(w->e, w->e->trans_model)
			+ actu_transform(w->e, w->e->trans_model);
	if (w->e->id_scrol >= 0 && w->e->max_iter >= -1)
		actu_base(w->e, w->e->base_model);
	if (!ft_strcmp("fractal", w->name) && w->e->move_set)
	{
		w->e->tr_base[0] += w->mouse->m[0] - w->prev_mouse->m[0];
		w->e->tr_base[1] += w->mouse->m[1] - w->prev_mouse->m[1];
		actu_base(w->e, w->e->base_model);
	}
	main_work(w->e);
	return (on + 1);
}
