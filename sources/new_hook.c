/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 10:37:32 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/05 06:50:02 by fjanoty          ###   ########.fr       */
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
/*
	ft_putstr("haha\n");
	dprintf(1, "(%s)	press_key:		%d\n", w->name, key_code);
*/

	(key_code == 53) ? ft_exit(w->e) : (void)w;
	dprintf(1, "key_press ~~>	code:   %d\n", key_code);
	(key_code == 36) ? ++(w->e->iter_koch) : (void)w;
	(key_code == 51 && w->e->iter_koch > 0) ? --(w->e->iter_koch): (void)w;
	if (key_code == 15 && ft_strcmp(w->name, "param") == 0)
	{
		if (mouse_in_border(&(w->e->border_b), w->mouse))
		{
			reset_base(w->e);
		}
		else if (mouse_in_border(&(w->e->border_t), w->mouse))
		{
			reset_transform(w->e);
		}
	}
	return (1);
}

int	release_key(int key_code, t_win *w)
{
	dprintf(1, "(%s)	release_key:	%d\n", w->name, key_code);
	return (1);
}

int motion_cursor(int x, int y, t_win *w)
{
	char	*position;

	position = (mouse_inside(x, y, w)) ? "in " : "out";
	(void)position;
//	dprintf(1, "(%s ==> %s)		x:%d	y:%d\n", w->name, position, x, y);
	w->prev_mouse->m[0] = w->mouse->m[0];
	w->prev_mouse->m[1] = w->mouse->m[1];
	w->mouse->m[0] = x;
	w->mouse->m[1] = y;
	if (!ft_strcmp(w->name, "param"))
		actu_polygone_io(w->e, w);
//	check_border_io(w->e, w, &(w->e->border_b));
//	check_border_io(w->e, w, &(w->e->border_t));
	//	ici on apele le petit chec des famille
	return (1);
}

int press_button(int button, int x, int y, t_win *w)
{
	char	*position;

	position = (mouse_inside(x, y, w)) ? "in " : "out";
	if (button == 1)
		complet_polygone(w);
	if (button == 2 && !ft_strcmp(w->name, "param"))
	{
		if (mouse_in_border(&(w->e->border_b), w->mouse))
		{
			if ((w->e->base_add++) == 0)
				polygone_forget_last(&(w->e->base_model));
		}
		if (mouse_in_border(&(w->e->border_t), w->mouse))
		{
			if ((w->e->trans_add++) == 0)
				polygone_forget_last(&(w->e->trans_model));
		}
//		dprintf(1, "base:%d	trans:%d\n", w->e->base_add, w->e->trans_add);
	}
			
	dprintf(1, "press	(%s ==> %s)		x:%d	y:%d	button:%d\n", w->name, position, x, y, button);
	return (1);
}

int release_button(int button, int x, int y, t_win *w)
{
	char	*position;

	position = (mouse_inside(x, y, w)) ? "in " : "out";
	dprintf(1, "release	(%s ==> %s)		x:%d	y:%d	button:%d\n", w->name, position, x, y, button);
	return (1);
}

/*
int mouse_other(int x, int y, t_env *e)
{
}
*/
