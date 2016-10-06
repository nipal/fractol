/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 02:21:11 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/06 07:49:26 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "c_maths.h"
# include <errno.h>
# include <string.h>

# define BETA e->beta

# define KEY_PRESS                2
# define KEY_RELEASE              3
# define BUTTON_PRESS             4
# define BUTTON_RELEASE           5
# define MOTION_NOTIFY            6

typedef	struct			s_average
{
	double	du;
	int		il;
	int		jl;
	int		ih;
	int		ih0;
	int		jh;
	double	coef[6];
}						t_average;

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

# define SIZE_X 1200
# define SIZE_Y 1200
# define ITER 50
# define ZOOM 0.95

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
	double				**img_low;//[SIZE_Y][SIZE_X];
	double				**img_height;//[SIZE_Y * 2 + 2][SIZE_X * 2 + 2];
	int					x_maxl;
	int					y_maxl;
	int					x_maxh;
	int					y_maxh;
	int					iter;
	double				pos_height[4];
	double				pos_low[4];
	double				zoom;
}						t_env;

void		print_map(double **img, int size_x, int size_y);
/*
** hook
*/
int						key_press(int keycode, t_env *e);
int						key_release(int keycode, t_env *e);
int						mouse_motion(int x, int y, t_env *e);
int 					mouse_press(int button, int x, int y, t_env *e);
int 					mouse_release(int button, int x, int y, t_env *e);
void					set_key(int key_code, t_env *e, const int on, const int off);

/*
** mlx_env
*/
void					vectpx_to_img(t_env *e, t_matrix *pos_color);
void					env(void);
void					init_pos_ecr(t_env *e);


/*
**	exit.c
*/
void					free_map(t_matrix	****map, t_env *e);
int						free_int_map(t_env *e);
int						free_cam(t_env *e);
int						ft_exit(t_env *e);
int						main_work(void);

t_env					*get_env(t_env *e);
int						get_iter(int valu);

/*
**	calcul mandelbrot
*/

void					resize_window(double pos[4], double mult, double x, double y);
void					set_color_fractal(t_env *e);
void					calc_average(double pos[8], double max[4], t_env *e);
double					get_iter_average(double mult[2], double **val);
int						get_gray_color(double valu, double max_iter);
void					calcul_grid(double **img, double pos[4], double max_x, double max_y);
int						calcul_one_point(double ct[2], int iter);
void					calculate_average(double **img_low, double **img_height, double pos_l[4], double pos_h[4]);
#endif
