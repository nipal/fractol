/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 18:52:27 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/04 01:40:44 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fdf.h"

/*
**	ft_putchar('[');
** 	ft_putnbr(keycode);
**	ft_putstr("] ");
*/

void	key_release_end(int keycode, t_env *e)
{
	(keycode == 36) ? e->key.switch_anime = 0 : (void)keycode;
	(keycode == 53) ? e->key.echap = 0 : (void)keycode;
	(keycode == 125) ? e->key.decal_down = 0 : (void)keycode;
	(keycode == 126) ? e->key.decal_up = 0 : (void)keycode;
	(keycode == 124) ? e->key.decal_right = 0 : (void)keycode;
	(keycode == 125) ? e->key.decal_down = 0 : (void)keycode;
	(keycode == 126) ? e->key.decal_up = 0 : (void)keycode;
	(keycode == 124) ? e->key.decal_right = 0 : (void)keycode;
	(keycode == 123) ? e->key.decal_left = 0 : (void)keycode;
	(keycode == 69) ? e->key.zoom = 0 : (void)keycode;
	(keycode == 78) ? e->key.zoom_back = 0 : (void)keycode;
	(keycode == 24) ? e->key.scale_increase = 0 : (void)keycode;
	(keycode == 27) ? e->key.scale_decrease = 0 : (void)keycode;
	(keycode == 2) ? e->key.cte1_increase = 0 : (void)keycode;
	(keycode == 0) ? e->key.cte1_decrease = 0 : (void)keycode;
	(keycode == 34) ? e->key.isometric = 0 : (void)keycode;
	(keycode == 35) ? e->key.parallel = 0 : (void)keycode;
	(keycode == 8) ? e->key.conic = 0 : (void)keycode;
	(keycode == 15) ? e->key.r = 0 : (void)keycode;
	(keycode == 5) ? e->key.g = 0 : (void)keycode;
	(keycode == 11) ? e->key.b = 0 : (void)keycode;
}

int		key_release_old(int keycode, t_env *e)
{
	(keycode == 18) ? e->key.z_up = 0 : (void)keycode;
	(keycode == 19) ? e->key.z_down = 0 : (void)keycode;
	(keycode == 45) ? e->key.view = 0 : (void)keycode;
	(keycode == 46) ? e->key.draw = 0 : (void)keycode;
	(keycode == 6) ? e->key.fi1 = 0 : (void)keycode;
	(keycode == 7) ? e->key.fi_1 = 0 : (void)keycode;
	(keycode == 8) ? e->key.fi2 = 0 : (void)keycode;
	(keycode == 9) ? e->key.fi_2 = 0 : (void)keycode;
	(keycode == 27) ? e->key.speed_down = 0 : (void)keycode;
	(keycode == 24) ? e->key.speed_up = 0 : (void)keycode;
	(keycode == 29) ? e->key.speed_stop = 0 : (void)keycode;
	(keycode == 13) ? e->key.rot_x1 = 0 : (void)keycode;
	(keycode == 12) ? e->key.rot_y1 = 0 : (void)keycode;
	(keycode == 0) ? e->key.rot_z1 = 0 : (void)keycode;
	(keycode == 1) ? e->key.rot_x2 = 0 : (void)keycode;
	(keycode == 14) ? e->key.rot_y2 = 0 : (void)keycode;
	(keycode == 2) ? e->key.rot_z2 = 0 : (void)keycode;
	(keycode == 32) ? e->key.rot_cam_x1 = 0 : (void)keycode;
	(keycode == 34) ? e->key.rot_cam_y1 = 0 : (void)keycode;
	(keycode == 38) ? e->key.rot_cam_z1 = 0 : (void)keycode;
	(keycode == 31) ? e->key.rot_cam_x2 = 0 : (void)keycode;
	(keycode == 40) ? e->key.rot_cam_y2 = 0 : (void)keycode;
	(keycode == 37) ? e->key.rot_cam_z2 = 0 : (void)keycode;
	key_release_end(keycode, e);
	return (1);
}
