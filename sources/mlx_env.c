/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 04:08:06 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/05 20:26:16 by fjanoty          ###   ########.fr       */
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

void	set_key(int key_code, t_env *e, const int on, const int off)
{
	(void)key_code;
	(void)e;
	(void)on;
	(void)off;
//	e->echap = (key_code == 53) ? on : off;
}

int	key_press(int key_code, t_env *e)
{
//	set_key(key_code, e, 1, 0);
	(key_code == 53) ? ft_exit(e) : (void)e;
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
	e->y_maxl = SIZE_Y;
	e->x_maxl = SIZE_X;
	e->y_maxh = 2 * SIZE_Y + 2;
	e->x_maxh = 2 * SIZE_X + 2;
	
	mlx_hook(e->win, 2, (1 << 24) - 1, &key_press , e);
	mlx_hook(e->win, 3, (1 << 24) - 1, &key_release, e);
	mlx_hook(e->win, 4, (1 << 24) - 1, &mouse_press, e);//	fait aussi la mollet
	mlx_hook(e->win, 5, (1 << 24) - 1, &mouse_release, e);
	mlx_hook(e->win, 6, (1 << 24) - 1, &mouse_motion, e);
	mlx_loop_hook(e->mlx, main_work, e);
	mlx_loop(e->mlx);
}

t_env	*get_env(t_env *e)
{
	static	t_env	*env = NULL;

	if (e)
		env = e;
	return (env);
}

void		env(void)
{
	t_env		e;

	get_env(&e);
	if (!(e.mlx = mlx_init()))
		return ;
	e.win = mlx_new_window(e.mlx, SIZE_X, SIZE_Y, "Leu test");
	e.img = mlx_new_image(e.mlx, SIZE_X, SIZE_Y);
	e.data = (t_pix*)mlx_get_data_addr(e.img, &(e.depth), &(e.size_line), &(e.endian));
	e.z_buffer = (double*)malloc(sizeof(double) * SIZE_X * SIZE_Y);
	env_end(&e);
	return ;
}
