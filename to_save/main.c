/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 07:31:16 by fjanoty           #+#    #+#             */
/*   Updated: 2017/06/16 18:26:20 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "fractol.h"
#include "mlx.h"

t_win		*window_init(t_env *e, int size_x, int size_y, char *name)
{
	t_win	*w;

	if (!name)
		name = "new w";
	if (!e || !(size_x > 0 && size_y > 0)
			|| !(w = (t_win*)malloc(sizeof(t_win)))
			|| !(w->mouse = matrix_init(1, 3))
			|| !(w->prev_mouse = matrix_init(1, 3))
			|| !(w->win = mlx_new_window(e->mlx, size_x, size_y, name))
			|| !(w->img = mlx_new_image(e->mlx, size_x, size_y))
			|| !(w->data = (t_pix*)mlx_get_data_addr(w->img, &(w->depth)
					, &(w->size_line), &(w->endian)))
			|| !(w->name = ft_strdup(name))
			|| !(w->z_buff = (double*)malloc(sizeof(double) * size_x * size_y)))
		return (NULL);
	w->e = e;
	w->is_z_buff = 1;
	w->size_x = size_x;
	w->size_y = size_y;
	w->mx = 0;
	w->my = 0;
	return (w);
}



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




int		press_key(int key_code, t_win *w)
{
	(key_code == 53) ? ft_exit(w->e) : 0;
	return (1);
}

void		init_win_event(t_win *w, t_env *e)
{
	(void)e;

	mlx_hook(w->win, KEY_PRESS, (1 << 24) - 1, press_key, w);
}

int			main_work(t_env *e)
{
	e->max_iter = HARD_ITER;
	ocl_render_run(e);
	return (1);
}

void		env(t_env *e)
{
	t_border border_abox;

	if (!e || !(e->mlx = mlx_init()))
		return ;
	if (!(e->fractal = window_init(e, SIZE_KOCH_X, SIZE_KOCH_Y, "fractal")))
		return ;
	init_win_event(e->fractal, e);
	mlx_loop_hook(e->mlx, main_work, e);
	ocl_init_ifs(e);
	mlx_loop(e->mlx);
	mlx_do_sync(e->mlx);

	return ;
}

int		main(int ac, char **av)
{
	t_env				e;

	bzero(&e, sizeof(t_env));
	bzero(&(e.ocl), sizeof(t_ocl_core));
	bzero(&(e.ker), sizeof(t_ocl_ker) * NB_KER);
//	get_env(&e);
	env(&e);

	return (0);
}
