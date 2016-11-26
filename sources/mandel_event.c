/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 18:02:26 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/26 18:05:50 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		print_pos(double *pos)
{
	printf("pos[0]:%f\t", pos[0]);
	printf("pos[1]:%f\t", pos[1]);
	printf("pos[2]:%f\t", pos[2]);
	printf("pos[3]:%f\n", pos[3]);
}

void		describe_img_position(t_env *e)
{
	double	delta_x;
	delta_x = (e->pos_height[2] - e->pos_height[0]) / (e->zoom * (e->pos_low[2] - e->pos_low[0]));
	printf("pos low:\n");
	print_pos(e->pos_low);
	printf("pos height:\n");
	print_pos(e->pos_height);
	printf("delta:%f\n", delta_x);

	printf("\n\n");
}

void		do_the_zoom_simple(t_env *e, int x, int y, double mult)
{
	resize_window(e->pos_low, mult, x, y);
	calcul_grid(e->img_low, e->pos_low, SIZE_X, SIZE_Y);
	set_color_fractal(e->fractal);
}


int	mandel_press_key(int key_code, t_win *w)
{
	(void)key_code;
	(key_code == 53) ? ft_exit(w->e) : 0;
	//	pour depacement touche flecher
	return (0);
}

int	mandel_release_key(int key_code, t_win *w)
{
	(void)key_code;
	(void)w;
	//	pour deplacement
	return (0);
}

int mandel_motion_cursor(int x, int y, t_win *w)
{
	(void)(x + y);
	(void)w;
	double	dx;
	double	dy;
	
	dx = (w->e->pos_low[2] - w->e->pos_low[0]) / (double)SIZE_X;
	dy = (w->e->pos_low[3] - w->e->pos_low[1]) / (double)SIZE_Y;
	w->e->ctx = w->e->pos_low[0] + dx * (double)x;// un raport avec le zoom et x
	w->e->cty = w->e->pos_low[1] + dy * (double)y;//	la meme avec le zoom et y
//	w->e->ctx = 4 * (0.5 - ((double)x) / ((double)SIZE_X));// un raport avec le zoom et x
//	w->e->cty = 4 * (0.5 -  ((double)y) / ((double)SIZE_Y));//	la meme avec le zoom et y
	do_the_zoom_simple(w->e, 0, 0, 1);
	actu_win_rest(w->e->fractal);
	return (0);
}

int mandel_press_button(int button, int x, int y, t_win *w)
{
	(void)(x + y + button);
	(void)w;
	double	zoom_factor;

	zoom_factor = 0.8;
	printf("	PRESS:%d->{%d,	%d}\n", button, x, y);
//	if (button == 1)
//		resize_window(w->e->pos_low, 0.9, x, y);
//	else if (button == 2)
//		resize_window(w->e->pos_low, 1.1, x, y);
//	if (button == 1 || button == 2)
//	{
	//	calculate_average(w->e->img_low, w->e->img_height, w->e->pos_low, w->e->pos_height);
//	set_color_fractal(w->e->fractal);
//	mlx_put_image_to_window(w->e->mlx, w->e->fractal->win, w->e->fractal->img, 0, 0);
		w->e->zoom_on = 1;
		w->e->zoom_finished = 0;
		w->e->zoom_x = x;
		w->e->zoom_y = y;
		(button == 4 || button == 6) ? do_the_zoom_simple(w->e, x, y, zoom_factor) : 0;
		(button == 5 || button == 7) ? do_the_zoom_simple(w->e, x, y, 1 / zoom_factor) : 0;
	actu_win_rest(w->e->fractal);
//	}
	//	pour le zoom (la mollet c'est un press)
	return (0);
}

int mandel_release_button(int button, int x, int y, t_win *w)
{
	(void)(x + y + button);
	(void)w;
	//	pour pas grand chose
	return (0);
}

//void	actu_mouse_pos(t_win *w, int x, int y)

	//	resize_window(w->e->pos_low, 0.97, x, y);
