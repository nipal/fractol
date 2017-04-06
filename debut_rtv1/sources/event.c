/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 16:14:03 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/19 09:06:55 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <mlx.h>

void	actu_mouse_cursor(t_win *w, int x, int y)
{
	ft_memcpy(w->mouse_prev_pos, w->mouse_pos, sizeof(w->mouse_pos));
//		if (((w->mode_cursor % 2) == 1) && w->cursor_on == 1)
//		{
//			w->cursor_on = 0;
//			mlx_cursor_hide(w->e->mlx, w);
//			mlx_cursor_move(w->e->mlx, w, w->size_x * 0.5, w->size_y * 0.5);
//			ft_memcpy(w->mouse_prev_pos, w->mouse_pos, sizeof(w->mouse_pos));
//		}
//		else if (((w->mode_cursor % 2) == 0) && w->cursor_on == 0)
//		{
//			w->cursor_on = 1;
//			mlx_cursor_show(w->e->mlx, w);
//			ft_memcpy(w->mouse_prev_pos, w->mouse_pos, sizeof(w->mouse_pos));
//			mlx_cursor_move(w->e, w, w->size_x * 0.5, w->size_y * 0.5);
//		}
//		if (!w->cursor_on)
//		{
//			w->mouse_pos[0] = x - SIZE_X * 0.5;
//			w->mouse_pos[1] = y - SIZE_Y * 0.5;
//		}
//		else
//		{
		w->mouse_pos[0] = x;
		w->mouse_pos[1] = y;
//		}
}


/*
**	123 gauche
**	124 droite
**	125 bas
**	126 haut

**	4	h
**	38	j
**	40	k
**	37	l
**
**
**	(G D) -> angle teta (longitude)  (horizntale)
**	(H B) -> angle phi  (colatitude) (verticale)
**
**	
*/


int press_key(int key_code, t_win *w)
{
	char *oui = malloc(sizeof(t_win));
	(key_code == 4) ? w->cam_angle[1] += w->cam_ang_incr : 0;
	(key_code == 37) ? w->cam_angle[1] -= w->cam_ang_incr : 0;
	(key_code == 38) ? w->cam_angle[0] += w->cam_ang_incr : 0;
	(key_code == 40) ? w->cam_angle[0] -= w->cam_ang_incr : 0;
	int toto = (key_code == 12) ? oui[19999] = 1 : 0;
	(void)toto;
	if (key_code == 53)
		ft_exit(w->e);
	if (key_code == 48)
	{
		w->cursor_on = !(w->cursor_on);
	}
	(void)w;
	printf("key:%d		ang[0]:%.2f	ang[1]:%.2f ang[2]:%.2f\n", key_code, w->cam_angle[0], w->cam_angle[1], w->cam_angle[2]);
	return (key_code + 1);
}

int		release_key(int key_code, t_win *w)
{
	printf("key:%d\n", key_code);
	(void)w;
	return (key_code + 1);
}

int		motion_cursor(int x, int y, t_win *w)
{	
	printf("cursor:{%d, %d}\n", x, y);
	actu_mouse_cursor(w, x, y);
	return (x + y);
}

int		press_cursor(int button, int x, int y, t_win *w)
{
	printf("button:%d\n", button);
	(void)w;
	return (button + x + y);
}

int		release_cursor(int button, int x, int y, t_win *w)
{
	printf("button:%d\n", button);
	(void)w;
	return (button + x + y);
}
