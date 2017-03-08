/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 18:02:26 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/05 06:59:00 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define INCREM 0.05

int		mandel_press_key(int key_code, t_win *w)
{
	(key_code == KEY_ESC) ? ft_exit(w->e) : ft_putstr("");
	(key_code == 123) ? ft_putstr("GAUCHE\n")
		+ do_the_translation(w->e, -INCREM, 0) : ft_putstr("");
	(key_code == 124) ? ft_putstr("DROITE\n")
		+ do_the_translation(w->e, INCREM, 0) : ft_putstr("");
	(key_code == 125) ? ft_putstr("BAS\n")
		+ do_the_translation(w->e, 0, INCREM) : ft_putstr("");
	(key_code == 126) ? ft_putstr("HAUT\n")
		+ do_the_translation(w->e, 0, -INCREM) : ft_putstr("");
	if (key_code >= 123 && key_code <= 126)
	{
		do_the_zoom_simple(w->e, 0, 0, 1);
		actu_win_rest(w->e->fractal);
	}
	return (1);
}

int		mandel_release_key(int key_code, t_win *w)
{
	(void)key_code;
	(void)w;
	return (0);
}

int		mandel_motion_cursor(int x, int y, t_win *w)
{
	double	dx;
	double	dy;

	(void)(x + y);
	(void)w;
	dx = (w->e->pos_low[2] - w->e->pos_low[0]) / (double)SIZE_X;
	dy = (w->e->pos_low[3] - w->e->pos_low[1]) / (double)SIZE_Y;
	w->e->ctx = w->e->pos_low[0] + dx * (double)x;
	w->e->cty = w->e->pos_low[1] + dy * (double)y;
	do_the_zoom_simple(w->e, 0, 0, 1);
	actu_win_rest(w->e->fractal);
	return (0);
}

int		mandel_press_button(int button, int x, int y, t_win *w)
{
	double	zoom_factor;

	(void)(x + y + button);
	(void)w;
	zoom_factor = 0.8;
	w->e->zoom_on = 1;
	w->e->zoom_finished = 0;
	w->e->zoom_x = x;
	w->e->zoom_y = y;
	(button == 4 || button == 6) ?
		do_the_zoom_simple(w->e, x, y, zoom_factor) : 0;
	(button == 5 || button == 7) ?
		do_the_zoom_simple(w->e, x, y, 1 / zoom_factor) : 0;
	(button >= 4 && button <= 7) ? actu_win_rest(w->e->fractal) : 0;
	return (0);
}

int		mandel_release_button(int button, int x, int y, t_win *w)
{
	(void)(x + y + button);
	(void)w;
	return (0);
}
