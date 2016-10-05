/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 02:21:11 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/05 20:25:01 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "c_maths.h"
# include <errno.h>
# include <string.h>

# define BETA e->beta

typedef	struct			s_mouse
{
	int					pos_x;
	int					pos_y;
	int					left_press;
	int					left_release;
	int					right_press;
	int					right_release;
}						t_mouse;

typedef	union			u_pix
{
	int					nb;
	char				comp[4];
}						t_pix;

typedef struct			s_key
{
	int					echap;
}						t_key;

typedef	struct			s_cam
{
	t_matrix			**corner;
	t_matrix			**base;
	t_matrix			*pos;
	t_matrix			*dir;
	t_matrix			*rot;
}						t_cam;

# define SIZE_X 480
# define SIZE_Y 320

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	void				*img;
	t_pix				*data;
	double				*z_buffer;
	int					size_line;
	int					depth;
	int					endian;
	int**				img_low;//[SIZE_Y][SIZE_X];
	int**				img_height;//[SIZE_Y * 2 + 2][SIZE_X * 2 + 2];
	int					x_maxl;
	int					y_maxl;
	int					x_maxh;
	int					y_maxh;
	int					iter;
}						t_env;

/*
** hook
*/
int						key_press(int keycode, t_env *e);
int						key_release(int keycode, t_env *e);

int						loop_hook(t_env *e);

/*
** mlx_env
*/
void					vectpx_to_img(t_env *e, t_matrix *pos_color);
void					env(void);


/*
**	exit.c
*/
void					free_map(t_matrix	****map, t_env *e);
int						free_int_map(t_env *e);
int						free_cam(t_env *e);
int						ft_exit(t_env *e);

int						main_work(void);

int						loop_mouse_clic(int button, int x, int y, t_env *e);
int						loop_mouse_move(int x, int y, t_env *e);
t_env					*get_env(t_env *e);

/*
**	calcul mandelbrot
*/

void					resize_window(double pos[4], double mult, double x, double y);
void					set_color_fractal(t_env *e);
void					calc_average(double pos[8], double max[4], t_env *e);
int						get_iter_average(double mult[2], int **val);
int						get_gray_color(int valu, int max_iter);
void					calcul_hgrid(t_env *e, double pos[4]);
int						calcul_one_point(double ct[2], int iter);
#endif
