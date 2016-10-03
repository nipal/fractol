/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 04:08:06 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/04 01:52:36 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fdf.h"
#include <stdio.h>

/*
** 	ici il faudrait stoquer les dimetion maximale de la map
** 	on a deja le max x et y il maque le max et le min en z
*/

t_matrix	*set_color(t_env *e, double value)
{
	t_matrix	*color;
	double		pak[4];

	pak[3] = value;
	pak[2] = e->z_max - e->z_min;
	color = NULL;
	pak[0] = 0;
	if (pak[3] < 0)
	{
		if (e->z_max > 0)
			pak[0] = 255 * pak[3] / e->z_min;
		else if (pak[2] > 0)
			pak[0] = 255 * pak[3] / pak[2];
		else
			pak[0] = 255;
		pak[1] = 255 - pak[0];
		if (!(color = vect_new_vertfd(0, pak[1], pak[0])))
			return (NULL);
	}
	else
		color = finishe_color(e, pak);
	return (color);
}

int			map_color_init(t_env *e)
{
	t_matrix	***color;
	int			i;
	int			j;

	if (!(color = (t_matrix***)malloc(sizeof(t_matrix**) * e->size_map_y)))
		return (0);
	j = 0;
	while (j < e->size_map_y)
	{
		if (!(color[j] = (t_matrix**)malloc(sizeof(t_matrix*) * e->size_map_x)))
			return (0);
		i = 0;
		while (i < e->size_map_x)
		{
			if (!(color[j][i] = set_color(e, e->map[j][i])))
				return (0);
			i++;
		}
		j++;
	}
	e->color_map = color;
	return (1);
}

#define KeyPress                2
#define KeyRelease              3
#define ButtonPress             4
#define ButtonRelease           5
#define MotionNotify            6

//int		mouse_motion(int x, int y, t_env *e)
int			mega_event()
{
	return (1);
}

/*
 * Evènement de type "KeyPress":
 *
 * int funct(int keycode, void *param);
 * Evènement de type "KeyRelease":
 *
 * int funct(int keycode, void *param);
 * Evènement de type "ButtonPress" (souris):
 *
 * int funct(int button, int x, int y, void *param);
 * Evènement de type "MotionNotify" (mouvement de la souris):
 *
 * int funct(int x, int y, void *param);
 * Tous les autres évènements:
 *
 * int funct(void *param);
 *
 * */

int	key_press(int key_code, t_env *e)
{
	(void)e;
	dprintf(1, "key_press-->	code:   %d\n", key_code);
	return (1);
}

int	key_release(int key_code, t_env *e)
{
	(void)e;
	dprintf(1, "key_release-->	code:   %d\n", key_code);
	return (1);
}

int mouse_motion(int x, int y, t_env *e)
{
	(void)e;
	dprintf(1, "mouse motion-->				x:%d	y:%d\n", x, y);
	return (1);
}

int mouse_press(int button, int x, int y, t_env *e)
{
	(void)e;
	dprintf(1, "mousse press-->		button:%d	x:%d	y:%d\n", button, x, y);
	return (1);
}

int mouse_release(int button, int x, int y, t_env *e)
{
	(void)e;
	dprintf(1, "mousse release-->	button:%d	x:%d	y:%d\n", button, x, y);
	return (1);
}

int mouse_other(int x, int y, t_env *e)
{
	(void)e;
	dprintf(1, "other-->		x:%d	y:%d\n", x, y);
	return (1);
}

//int		mouse_motion(int x, int y, t_env *e)
void		env_end(t_env *e)
{
	t_cam		*cam;

	e->dr1 = 0;
	e->dr2 = 0;
	e->ecr_x = SIZE_Y;
	e->ecr_y = SIZE_X;
	
	e->speed = 0;
	if (!(cam = init_cam(60.0 / 360.0 * M_PI, 60.0 / 360.0 * M_PI, e)))
		return ;
	e->cam = cam;
	init_t_key(&(e->key));
	mlx_hook(e->win, 2, (1 << 24) - 1, &key_press , e);
	mlx_hook(e->win, 3, (1 << 24) - 1, &key_release, e);
	mlx_hook(e->win, 4, (1 << 24) - 1, &mouse_press, e);//	fait aussi la mollet
	mlx_hook(e->win, 5, (1 << 24) - 1, &mouse_release, e);
	mlx_hook(e->win, 6, (1 << 24) - 1, &mouse_motion, e);
//	mlx_mouse_hook (e->win, loop_mouse_move, e);
	mlx_loop_hook(e->mlx, loop_hook, e);
	mlx_loop(e->mlx);
}
// masks: KeyPress, KeyRelease, ButtonPress, ButtonRelease, PointerMotion, Button1Motion
// , Button2Motion, Button3Motion, Button4Motion, Button5Motion, and ButtonMotion
void		env_mid(t_env *e)
{
	e->k = 1;
	e->phi1 = M_PI * 2;
	e->phi2 = M_PI * 2;
	e->beta = M_PI / 2 - 0.0001;
	e->nb_frame = 60;
	e->increm = (M_PI / (4 * e->nb_frame));
	e->view = 0;
	e->draw = 0;
	e->rot_x = (20.0 / 360.0) * 2 * M_PI;
	e->rot_y = (120.0 / 360.0) * 2 * M_PI;
	e->rot_z = (0.0 / 360.0) * 2 * M_PI;
}

void		env(int **map, int size_x, int size_y)
{
	t_env		e;
	t_matrix	*z_dim;

	if (!(z_dim = get_max_zdim(map, size_x, size_y)))
		return ;
	e.mult_z = 1;
	e.size_map_x = size_x;
	e.size_map_y = size_y;
	e.z_min = z_dim->m[0];
	e.z_max = z_dim->m[1];
	env_mid(&e);
	e.map = map;
	if (!(e.map_d = cast_tab(map, size_x, size_y)))
		return ;
	if (!(map_color_init(&e)))
		return ;
	if (!(e.mlx = mlx_init()))
		return ;
	e.win = mlx_new_window(e.mlx, SIZE_Y, SIZE_X, "Leu test");
	e.img = mlx_new_image(e.mlx, SIZE_Y, SIZE_X);
	e.data = mlx_get_data_addr(e.img, &(e.depth), &(e.size_line), &(e.endian));
	e.z_buffer = (double*)malloc(sizeof(double) * SIZE_X * SIZE_Y);
	env_end(&e);
	matrix_free(&z_dim);
}
