/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 02:21:11 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/08 22:49:42 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define SIZE_X 1200
# define SIZE_Y 1200
# define ITER 200
# define ZOOM 0.95

# include "c_maths.h"
# include <errno.h>
# include <string.h>

# define BETA e->beta

# define KEY_PRESS                2
# define KEY_RELEASE              3
# define BUTTON_PRESS             4
# define BUTTON_RELEASE           5
# define MOTION_NOTIFY            6

# define NORME 12
# define Z 2

typedef	struct	s_polygone t_polygone;

struct			s_polygone
{
	int			lvl;
	t_matrix	*pos;
	t_matrix	*col;
	t_polygone	*next;
};

typedef	struct	s_average
{
	double		du;
	int			il;
	int			jl;
	int			ih;
	int			ih0;
	int			jh;
	double		coef[6];
}				t_average;

typedef	struct	s_mouse
{
	int			pos_x;
	int			pos_y;
	int			left_press;
	int			left_release;
	int			right_press;
	int			right_release;
}				t_mouse;

typedef	union	u_pix
{
	int			nb;
	char		comp[4];
}				t_pix;

/*
**	key_release 	(key_code == release) ?  (1, 2, 0) -> 0 : 1 -> 2
**	key_press		0 -> 1
**	
**	0 -> inactif
**	1 -> viens d'etre activer
**	2 -> n'est pas revenu
*/

typedef struct	s_key
{
	int			echap;
	int			add_iter;
}				t_key;

typedef	struct	s_cam
{
	t_matrix	**corner;
	t_matrix	**base;
	t_matrix	*pos;
	t_matrix	*dir;
	t_matrix	*rot;
}				t_cam;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	t_pix		*data;
	double		*z_buffer;
	int			size_line;
	int			depth;
	int			endian;
	double		**img_low;//[SIZE_Y][SIZE_X];
	double		**img_height;//[SIZE_Y * 2 + 2][SIZE_X * 2 + 2];
	int			x_maxl;
	int			y_maxl;
	int			x_maxh;
	int			y_maxh;
	int			iter;
	double		pos_height[4];
	double		pos_low[4];
	double		zoom;
	int			zoom_on;
	int			zoom_x;
	int			zoom_y;
	int			zoom_finished;

	t_polygone	*base;
	t_polygone	*transform;
	t_polygone	*beg_actif;
	t_polygone	*actif;
	int			draw_base;
	int			draw_transform;
	int			add_iter;
	t_polygone	*trans_controle;
//	t_polygone	*transform;
}				t_env;

void			print_map(double **img, int size_x, int size_y);
/*
** hook
*/
int				key_press(int keycode, t_env *e);
int				key_release(int keycode, t_env *e);
int				mouse_motion(int x, int y, t_env *e);
int 			mouse_press(int button, int x, int y, t_env *e);
int 			mouse_release(int button, int x, int y, t_env *e);
void			set_key(int key_code, t_env *e, const int on, const int off);
void			size_window_copy(double pos_low[4], double pos_height[4]);

/*
** mlx_env
*/
void			vectpx_to_img(t_env *e, t_matrix *pos_color);
void			env(void);
void			init_pos_ecr(t_env *e);


/*
**	exit.c
*/
void			free_map(t_matrix	****map, t_env *e);
int				free_int_map(t_env *e);
int				free_cam(t_env *e);
int				ft_exit(t_env *e);
int				main_work(void);

t_env			*get_env(t_env *e);
int				get_iter(int valu);

/*
**	calcul mandelbrot
*/

void			do_zoom_simple(t_env *e);
int				resize_window(double pos[4], double mult, double x, double y);
void			set_color_fractal(t_env *e);
void			calc_average(double pos[8], double max[4], t_env *e);
double			get_iter_average(double mult[2], double **val);
int				get_gray_color(double valu, double max_iter);
void			calcul_grid(double **img, double pos[4], double max_x, double max_y);
int				calcul_one_point(double ct[2], int iter);
void			calculate_average(double **img_low, double **img_height, double pos_l[4], double pos_h[4]);

/*
**	drawline
*/
void			trace_line(double *pt1, double *pt2, double *c1, double *c2);
int				draw_line(t_env *e, t_matrix *mat_line);
t_matrix		*init_mat_line(t_matrix *pt1, t_matrix *pt2,
				t_matrix *c1, t_matrix *c2);
void			trace_seg_line(t_env *e, t_polygone *node);

/*
**	koch
*/

void			print_polygone(t_env *e, t_polygone *poly);
t_polygone		*creat_node(int lvl, double *pos, double *color);
int				destroy_polgone(t_polygone **begin);
t_polygone		*get_last(t_polygone *node);
int				insert_portion(t_polygone **target, t_polygone *src);
void			push_back(t_polygone **root, t_polygone *node);
void			init_koch(t_env *e);
void			add_point(t_polygone **node, int x, int y, int lvl);
void			increm_polygone(int x, int y, t_env *e);
void			move_last(int x, int y, t_env *e);
t_polygone		*copy_node(t_polygone *node, int lvl);

void			end_transform(t_env *e);
void			end_base(t_env *e);
void			zero_double(double *tab1, double *tab2, int size);

/*
**	poygone_new
*/

t_polygone		*creat_node(int lvl, double *pos, double *color);
t_polygone		*creat_node_fv(int lvl, t_matrix *pos, t_matrix *color);
t_polygone		*copy_node(t_polygone *node, int lvl);

/*
**	polygone_destroy
*/
int				destroy_polgone(t_polygone **begin);

/*
**	polygone_transform
*/
void		iterate_transformation(t_polygone *polyg, t_polygone *transpose);

double			dist_to_end(t_polygone *seg);
void			init_dtab(double *tab, double valu, int size);
t_polygone		*adate_to_unite(t_matrix *ux, t_matrix *uy, t_matrix *org, t_polygone *src);
t_polygone		*transform(t_polygone *seg_beg);
t_matrix		*position_transpose(t_matrix *org, t_matrix *ux, t_matrix *uy, t_matrix *dir);
t_polygone		*creat_insert(t_polygone *seg, t_polygone *transforme);


void	init_trans_control(t_env *e);
void	describe_one_node(t_polygone *seg);
void	polygone_describe(t_polygone *node);
#endif
