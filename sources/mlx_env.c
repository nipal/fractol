/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 04:08:06 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/05 02:00:18 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fractol.h"
#include <stdio.h>

/*
** 	ici il faudrait stoquer les dimetion maximale de la map
** 	on a deja le max x et y il maque le max et le min en z
*/

//int		mouse_motion(int x, int y, t_env *e)
int			**init_tab(int size_x, int size_y)
{
	int	j;
	int	**tab;

	if (!(tab = (int**)malloc(sizeof(int*) * size_y)))
		return (NULL);
	j = 0;
	while (j < size_y)
	{
		if (!(tab[j] = (int*)malloc(sizeof(int) * size_x)))
			return (NULL);
		j++;
	}
	return (tab);
}

double			**init_tab_d(int size_x, int size_y)
{
	int	j;
	double	**tab;

	if (!(tab = (double**)malloc(sizeof(double*) * size_y)))
		return (NULL);
	j = 0;
	while (j < size_y)
	{
		if (!(tab[j] = (double*)malloc(sizeof(double) * size_x)))
			return (NULL);
		j++;
	}
	return (tab);
}


void		env_end(t_env *e)
{
	e->y_maxl = SIZE_Y;
	e->x_maxl = SIZE_X;
	e->y_maxh = 2 * SIZE_Y;
	e->x_maxh = 2 * SIZE_X;
	e->zoom = ZOOM;
	e->zoom_on = 0;
	e->zoom_y = 0;
	e->zoom_x = 0;
	e->zoom_finished = 1;
	e->base_add = 0;
	e->trans_add = 0;
	
	if (!(e->img_low = init_tab_d(e->x_maxl, e->y_maxl))
		|| !(e->img_height = init_tab_d(e->x_maxh + 2,  e->y_maxh + 2)))
		return ;
//	mlx_hook(e->win, KEY_PRESS, (1 << 24) - 1, &key_press , e);
//	mlx_hook(e->win, KEY_RELEASE, (1 << 24) - 1, &key_release, e);
//	mlx_hook(e->win, BUTTON_PRESS, (1 << 24) - 1, &mouse_press, e);
//	mlx_hook(e->win, BUTTON_RELEASE, (1 << 24) - 1, &mouse_release, e);
//	mlx_hook(e->win, MOTION_NOTIFY, (1 << 24) - 1, &mouse_motion, e);
/*
	init_pos_ecr(e);
	calcul_grid(e->img_height, e->pos_height, e->x_maxh + 2, e->y_maxh + 2);
	calculate_average(e->img_low, e->img_height, e->pos_low, e->pos_height);
//	calcul_grid(e->img_low, e->pos_low, e->x_maxl, e->y_maxl);
//	print_map(e->img_height, e->x_maxh, e->y_maxh);
	set_color_fractal(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
*/
	mlx_loop_hook(e->mlx, main_work, e);
	init_koch(e);
	mlx_loop(e->mlx);
	mlx_do_sync(e->mlx);
}

t_env	*get_env(t_env *e)
{
	static	t_env	*env = NULL;

	if (e)
		env = e;
	return (env);
}

int		get_iter(int valu)
{
	static	int	iter = 0;

	if (valu > 0)
		iter = valu;
	return (iter);
}

void	init_win_event(t_win *w, t_env *e)
{
	(void)e;
	mlx_hook(w->win, KEY_PRESS, (1 << 24) - 1, press_key , w);
	mlx_hook(w->win, KEY_RELEASE, (1 << 24) - 1, release_key, w);
	mlx_hook(w->win, BUTTON_PRESS, (1 << 24) - 1, press_button, w);
	mlx_hook(w->win, BUTTON_RELEASE, (1 << 24) - 1, release_button, w);
	mlx_hook(w->win, MOTION_NOTIFY, (1 << 24) - 1, motion_cursor, w);
}

void		env(void)
{
	t_env		e;

	get_env(&e);
	e.iter = get_iter(ITER);
	if (!(e.mlx = mlx_init()))
		return ;
	if (!(e.fractal = window_init(&e, SIZE_X, SIZE_Y, "fractal"))
		|| !(e.param = window_init(&e, 700, 700, "param")))
		return ;
	init_win_event(e.fractal, &e);
	init_win_event(e.param, &e);
	init_koch_param_border(&e, e.param);

//	e.win = mlx_new_window(e.mlx, SIZE_X, SIZE_Y, "Leu test");
//	e.img = mlx_new_image(e.mlx, SIZE_X, SIZE_Y);
//	e.data = (t_pix*)mlx_get_data_addr(e.img, &(e.depth), &(e.size_line), &(e.endian));
//	e.z_buffer = (double*)malloc(sizeof(double) * SIZE_X * SIZE_Y);
	env_end(&e);
	return ;
}
