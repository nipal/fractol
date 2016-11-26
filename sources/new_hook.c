/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 10:37:32 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/21 01:36:18 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mouse_inside(int x, int y, t_win *w)
{
	if (!w || x < 0 || x >= w->size_x || y < 0 || y >= w->size_y)
		return (0);
	return (1);
}

int	press_key(int key_code, t_win *w)
{
	dprintf(1, "max_iter:%d\n", w->e->max_iter);
	(key_code == 53) ? ft_exit(w->e) : 0;
	dprintf(1, "key_press ~~>	code:   %d\n", key_code);
	(key_code == 36) ? ++(w->e->max_iter) : 0;
	(key_code == 51 && w->e->max_iter > 0) ? --(w->e->max_iter): 0;
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

int	release_key(int key_code, t_win *w)
{
//	(key_code == 36) ? --(w->e->iter_koch) : (void)w;
	

	(key_code == 49) ? w->e->add_point = 0 : 0;
	dprintf(1, "(%s)	release_key:	%d\n", w->name, key_code);
	return (1);
}

int motion_cursor(int x, int y, t_win *w)
{
	char	*position;
	int		on;
//	static	long	ttt = 0;

	position = (mouse_inside(x, y, w)) ? "in " : "out";
	(void)position;
	w->mx = x;
	w->my = y;
	if (!ft_strcmp(w->name, "param"))
		actu_polygone_io(w->e, w);
	actu_mouse_pos(w, x, y);
	if (w->button1 && mouse_in_border(&(w->e->border_b), w->mouse) && w->e->base_add)
		on = move_the_node(w->e, w->e->base_model) + actu_base(w->e, w->e->base_model);
	if (w->button1 && mouse_in_border(&(w->e->border_t), w->mouse) && w->e->trans_add)
		on = move_the_node(w->e, w->e->trans_model) + actu_transform(w->e, w->e->trans_model);
	if (w->e->id_scrol >= 0 && w->e->max_iter <= 7)
		actu_base(w->e, w->e->base_model);
	if (!ft_strcmp("fractal", w->name) && w->e->move_set)
	{
		w->e->tr_base[0] += w->mouse->m[0] - w->prev_mouse->m[0];
		w->e->tr_base[1] += w->mouse->m[1] - w->prev_mouse->m[1];
		actu_base(w->e, w->e->base_model);
	}
	main_work();
	return (on + 1);
}

int press_button(int button, int x, int y, t_win *w)
{
	int			toto;

	w->button1 = 1;
	if (button == 1 && !ft_strcmp(w->name, "param"))
	{
		w->e->id_scrol = select_button(w, w->e->sliders);
		dprintf(1, "id_scrol:%d\n", w->e->id_scrol);
		complet_polygone(w);
		if (w->e->add_point && w->e->base_add && w->e->trans_add)
			insert_adding_node(w);
	}
	if (button == 2 && !ft_strcmp(w->name, "param"))
	{
		if (mouse_in_border(&(w->e->border_b), w->mouse) && (w->e->base_add++) == 0)
				toto = polygone_forget_last(&(w->e->base_model))
					+ actu_base(w->e, w->e->base_model);
		if (mouse_in_border(&(w->e->border_t), w->mouse) && (w->e->trans_add++) == 0)
				toto = polygone_forget_last(&(w->e->trans_model))
					+ actu_transform(w->e, w->e->trans_model);
		if (w->e->trans_add && w->e->base_add)
			remove_one_node(w->e);
	}
	if (!ft_strcmp(w->name, "fractal"))
	{
		if (button == 4 || button == 6)
			zoom_border(&(w->e->base_cadre), x, y, 0.8);
		else if (button == 5 || button == 7)
			zoom_border(&(w->e->base_cadre), x, y, 1.25);
		else if (button == 1)
			w->e->move_set = 1;
		actu_base(w->e, w->e->base_model);
	}
	char	*position;
	position = (mouse_inside(x, y, w)) ? "in " : "out";
	dprintf(1, "press	(%s ==> %s)		x:%d	y:%d	button:%d\n", w->name, position, x, y, button);
	return (x + y > 0);
}

int release_button(int button, int x, int y, t_win *w)
{
	char	*position;

	w->button1 = 0;
	position = (mouse_inside(x, y, w)) ? "in " : "out";
	dprintf(1, "release	(%s ==> %s)		x:%d	y:%d	button:%d\n", w->name, position, x, y, button);
	if (button == 1 && !ft_strcmp("param", w->name))
	{
		if (w->e->id_scrol >= 0)
			actu_base(w->e, w->e->base_model);
		w->e->id_scrol = -1;
	}
	if (button == 1 && !ft_strcmp(w->name, "fractal"))
		w->e->move_set = 0;
	return (1);
}

/*
int mouse_other(int x, int y, t_env *e)
{
}
*/

void	actu_mouse_pos(t_win *w, int x, int y)
{
	w->prev_mouse->m[0] = w->mouse->m[0];
	w->prev_mouse->m[1] = w->mouse->m[1];
	w->mouse->m[0] = x;
	w->mouse->m[1] = y;
}
