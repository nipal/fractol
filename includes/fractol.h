/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 02:21:11 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/24 03:04:29 by fjanoty          ###   ########.fr       */
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

typedef	struct	s_env	t_env;

typedef	struct	s_win
{
	void		*img;
	void		*win;
	int			size_line;
	int			depth;
	int			endian;
	t_pix		*data;
	t_env		*e;
	char		*name;
	double		*z_buff;
	int			is_z_buff;
	int			size_x;
	int			size_y;
	t_matrix	*mouse;
	t_matrix	*prev_mouse;
}				t_win;




typedef	struct	s_coef_draw
{
	int			iter;
	double		len_seg;
	double		du_dist;
	t_polygone	*to_insert;
}				t_coef_draw;

typedef	struct	s_coef_const
{
	int			max_iter;
	double		dist;
	double		len_mult;
	double		min_val_trans;
	t_polygone	*mult;
	t_win		*w;
	t_matrix	*diff;
	t_matrix	*mouse;
	t_matrix	*prev_mouse;
}				t_coef_const;

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
	int			enter;
}				t_key;

typedef	struct	s_cam
{
	t_matrix	**corner;
	t_matrix	**base;
	t_matrix	*pos;
	t_matrix	*dir;
	t_matrix	*rot;
}				t_cam;

typedef	struct	s_matline
{
	t_matrix	*pt1;
	t_matrix	*pt2;
	t_matrix	*c1;
	t_matrix	*c2;
}				t_matline;

typedef	struct	s_border
{
	int	x0;
	int	x1;
	int	y0;
	int	y1;
}				t_border;

struct			s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	t_pix		*data;
	double		*z_buffer;
	int			size_line;
	int			depth;
	int			endian;
	double		**img_low;
	double		**img_height;
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

	int			iter_koch;
	t_polygone	*base_model;
	t_polygone	*trans_model;
	t_polygone	*base;
	t_polygone	*transform;
	t_polygone	*beg_actif;
	t_polygone	*actif;
	int			draw_base;
	int			draw_transform;
	int			add_iter;
	t_matrix	*prev_mouse;
	t_matrix	*mouse;
	double		r_select;
	double		min_val_trans;

	int			left;
	int			right;

	t_win		*param;
	t_win		*fractal;
	t_border	border_b;
	t_border	border_t;
//	t_polygone	*transform;
};

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
**	new_hook
*/
int				mouse_inside(int x, int y, t_win *w);
int				press_key(int key_code, t_win *w);
int				release_key(int key_code, t_win *w);
int 			motion_cursor(int x, int y, t_win *w);
int 			press_button(int button, int x, int y, t_win *w);
int 			release_button(int button, int x, int y, t_win *w);

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
**	param_koch.c
*/
void			draw_the_2_border(t_env *e);
void			init_koch_param_border(t_env *e, t_win *win_param);
void			draw_border(t_win *w, t_border *border, t_matrix *color);
int				reset_base(t_env *e);
int				reset_transform(t_env *e);
void			draw_the_2_border(t_env *e);
int				mouse_in_border(t_border *border, t_matrix *mouse);
int				check_border_io(t_env *e, t_win *w, t_border *b);
void			actu_polygone_io(t_env *e, t_win *w);
void			complet_polygone(t_win *w);
void			redefine_base(t_polygone *new_base, t_border *from, t_win *to);

void			print_polygone(t_env *e, t_polygone *poly);
t_polygone		*creat_node(int lvl, double *pos, double *color);
t_polygone		*get_last(t_polygone *node);
int				insert_portion(t_polygone **target, t_polygone *src);
void			push_back(t_polygone **root, t_polygone *node);
void			init_koch(t_env *e);
void			add_point(t_polygone **node, int x, int y, int lvl);
void			increm_polygone(int x, int y, t_env *e);
void			move_last(int x, int y, t_env *e);
t_polygone		*copy_node(t_polygone *node, int lvl);
int				init_win_param(t_env *e, int size_x, int size_y, char *name);

/*
**	init_win
*/
void	describe_window(t_win *w);
t_win	*window_init(t_env *e, int size_x, int size_y, char *name);
int		window_destroy(t_env *e, t_win **window);

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
int			polygone_destroy(t_polygone **begin);

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


void			init_trans_control(t_env *e);
void			describe_one_node(t_polygone *seg);
void			polygone_describe(t_polygone *node);
int				reset_koch(t_env *e);
void			calcul_and_print(t_polygone *seg, t_polygone *mult, int iter, t_env *e);

/*
**	polygone_maj
*/
int				nb_iter_koch(t_polygone *base, t_polygone *mult);
double			get_min_dist(t_polygone *node);
void			polygone_push_befor_last(t_polygone **begin, t_polygone *node);
void			polygone_push_back(t_polygone **begin, t_polygone *node);
void			polygone_forget_last(t_polygone **begin);

/*
**	modify_model
*/
void			print_circle_color(int cx, int cy, double r, t_matrix *col);
void			print_circle(int cx, int cy, double r);
t_polygone		*get_closer_node(t_polygone *beg, t_matrix *mouse, double min_dist);
void			print_mouse_close(t_env *e, t_polygone *poly);
void			translate_node(t_env *e, t_polygone *poly);

/*
**	color_transpose
*/

void			rgb_to_tsl_mod(t_matrix *rgb);
t_matrix		*rgb_to_tsl_new(double t, double s, double l);
t_matrix		*tsl_to_rvb_new(double t, double s, double l);
double			modulo(double a, double b);

/*
**	new_printing
*/
void			actu_win_rest(t_win *w);
t_matrix		*define_node_color(double dist_frac, double iter, double prog_iter);
void			draw_verticies(t_win *w, t_polygone *seg);
void			draw_vertice(t_win *w, t_polygone *seg);
void			translate_node2(t_env *e, t_polygone *poly);
void			print_polygone2(t_coef_const *cc, t_coef_draw *cd, double dist, t_polygone *seg);
void			trace_seg_line2(t_win *w, t_polygone *node);
void			trace_line2(double *pt1, double *pt2, double *c1, double *c2);
int				draw_line2(t_win *win, t_matrix *mat_line);
void			draw_line3(t_matline *ml, t_win *w);
void			vectpx_to_img2(t_win *win, t_matrix *pos_color);
void			draw_simple_polygone(t_win *w, t_polygone *node);

void			draw_vertice1(t_env *e, t_polygone *seg);
void			draw_verticies1(t_env *e, t_polygone *seg);
#endif
