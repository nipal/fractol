/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nperrin <nperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 10:54:24 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/13 22:39:59 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define NB_KER 10

# define STACK_SIZE 100
# define SERVEUR 0
# define CLIENT  1
# define MAX_NODE 20	// c'est deja enorme on aurra des gros problem de perfe a partir de 9

# include "c_maths.h"
# include "key.h"
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# define MAX_CLIENT 100

# define NB_NAME_FRAC 31
# define NB_NAME_ALT 10
# define NB_LETTER_NAME 100

# define SIZE_X 800
# define SIZE_Y 800

# define SIZE_PARAM_X 900
# define SIZE_PARAM_Y 600

# define SIZE_KOCH_X 1200
# define SIZE_KOCH_Y 1200

# define SIZE_Y2 2*SIZE_Y
# define SIZE_X2 2*SIZE_X
# define ITER 100
# define ZOOM 0.95


# define BETA e->beta

# define KEY_PRESS                2
# define KEY_RELEASE              3
# define BUTTON_PRESS             4
# define BUTTON_RELEASE           5
# define MOTION_NOTIFY            6

# define NORME 12
# define Z 2

# define MAX_DIST_ADD 50



# define MOUSE_IN mouse_in_border

# define X 0
# define Y 1


typedef	struct s_polygone	t_polygone;
typedef	struct s_env	t_env;

///////////// ocl_render /////////////

#include <OpenCL/opencl.h>	

# define BIG_OCL_BUF_SIZE 37500000 // pour retomber sur 300 mo
# define MAX_ITER 16 // vraiment... c'est trop pour un buffer mais bon... OK
# define ARG_KER_MAX 10
# define IFS_CALCUL_PT 0	// il faut vraiment queje me mette au enum, mais j'ai tellement la fleme
# define DRAW_LINE 1		// no comment 

//	on aura besoinr que d'une seule structure comme celle la pour tout le programe
typedef	struct		s_ocl_core
{
	cl_platform_id	platform_id;
	cl_device_id	device_id;
	cl_program		program;
	cl_context		context;	// c'est une variable qu'on initialise qu'une fois mais qu'on a souvent besoin
}					t_ocl_core;

typedef	struct			s_ocl_mem
{
	cl_mem				gpu_buff;
	void				*cpu_buff;
	size_t				size;
	short				io_acces;
}						t_ocl_mem;

//	On aura besoin d'un structure par kernel
typedef	struct			s_ocl_ker
{
	cl_context			context;
	cl_kernel			kernel;
	cl_command_queue	command_queue;
	t_ocl_mem			data[ARG_KER_MAX];
	int					nb_arg;
}						t_ocl_ker;

int	init_ocl_core(t_ocl_core *core, const char *file_name);
int	init_kernel(t_ocl_core *core, t_ocl_ker *ker, const char *kernel_name);
int	check_ocl_err(cl_int *ret, int nb_ret, const char *func_name, const char *file_name);

/*
 *	error_opencl.c	
 * */
int		print_ocl_error(int err_cl, int no_err, const char *file, const char *func);
void	init_ocl_error();

/*
 *	ocl_format_ifs_calcul.c
 * */
int	ocl_ifs_calcul_run(t_ocl_ker *ifs_cl, t_polygone *transform, t_polygone *base, int nb_iter, float col[6]);
int	ocl_init_ifs(t_env *e);

/*
 *	ifs_render.c
 * */

cl_int	ocl_create_mem(t_ocl_ker *ker, int id_arg, short io_acces, size_t size);
cl_int	ocl_init_mem(t_ocl_ker *ker, int id_arg, short io_acces, size_t size, cl_mem buff);
int	branch_arg_to_kernel(t_ocl_ker *ker, int nb_arg_buff);
int	check_ocl_err(cl_int *ret, int nb_ret, const char *func_name, const char *file_name);
int	init_ocl_core(t_ocl_core *core, const char *file_name);
int	init_kernel(t_ocl_core *core, t_ocl_ker *ker, const char *kernel_name);
///////// end_ocl //////////////////



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


typedef	struct	s_win
{
	int			button1;
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
	int			mx;
	int			my;
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

typedef	struct	s_koch_const
{
	t_polygone	*trans;
	t_win		*w;
	double		max_iter;
	double		len_seg;
	double		len_seg_beg;
	double		min_print;
}				t_koch_const;

typedef	struct	s_koch_changing
{
	t_polygone	*seg;
	double		iter;
	double		dist;
	double		prev_du;
}				t_koch_changing;



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

/*
**	on va faire une slider horizontal
*/

	typedef	struct	s_slider
{
	double		v1;
	double		v2;
	t_matrix	*color;
	t_border	*border;
}				t_slider;

typedef	struct	s_range_tsl
{
	double		tmin;
	double		tmax;
	double		smin;
	double		smax;
	double		lmin;
	double		lmax;
}				t_range_tsl;

typedef	struct	timeval	t_timeval;

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
	double		*img_low;
	double		**img_height;
	int			x_maxl;
	int			y_maxl;
	int			x_maxh;
	int			y_maxh;
	int			iter;
	int			max_iter;
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
	t_polygone	*trans_model2; // la mem chose que trans_model mais modifier par l'animation
	t_polygone	*base;	// coordonner reel
	t_polygone	*transform; // coordonner reel
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
	t_border	border_p;	// pour la border de preview
	int			base_add;
	int			trans_add;
	int			nb_sliders;
	int			id_scrol;
	t_slider	**sliders;
	t_range_tsl	range_color;
	int			add_point;
	double		tr_base[3];
	t_border	base_cadre;
	int			move_set;
	int			idf;
	double		ctx;
	double		cty;
	fd_set		read_fd;	// pour le reseau
	int			sock;		// pour le reseau aussi
	int			status;		// pour savoir si on est client ou serveur
	int			port;		// bah c'est explicite non ?
	////////////////
	int			id_anime_clicked;
	t_border	*border_abox;
	t_border	*border_speed;
	///////////
	t_timeval	time;
	double		periode;
	//////// openCl ////////////
	t_ocl_core	ocl;
	t_ocl_ker	ker[NB_KER];
};

typedef	struct	s_mandel_pt
{
	double		min;
	double		max;
	double		v0;
	double		v1;
	double		v2;
	double		v3;
}				t_mandel_pt;

typedef	struct	s_mandel_color
{
	int			i;
	int			j;
	int			y_maxl;
	int			x_maxl;
	int			iter;
}				t_mandel_color;

typedef	struct	s_pt2d
{
	double		x;
	double		y;
}				t_pt2d;

typedef	struct	s_pt2i
{
	int			x;
	int			y;
}				t_pt2i;

typedef	struct	s_calc_gr
{
	int			i;
	int			j;
	int			id;
	int			iter;
}				t_calc_gr;

typedef	struct	s_cop_julia
{
	double		*beg_x;
	double		*beg_y;
	double		ctx;
	double		cty;
}				t_cop_julia;

typedef	struct	s_d3
{
	double	v0;
	double	v1;
	double	v2;
}				t_d3;

typedef	struct	s_dp
{
	t_matrix	*pt1;
	t_matrix	*pt2;
	double		r;
	t_win		*w;
}				t_dp;

typedef	struct	s_lim
{
	int			v;
	int			h;
}				t_lim;

typedef	struct	s_network
{
	int			port;
	int			sock;
	fd_set		read_fd;
}				t_network;


//	les pramaetre d'animation d'un client a afficher
typedef	struct	s_anime_data
{
	t_polygone	*trans;
	t_polygone	*base;
	int			nb_iter;
	double		col[6];

}				t_anime_data;

// les parametre d'une animation
typedef	struct	s_anime
{
	t_slider	*speed;
	t_slider	*offset;
	int			abox_selected;
	t_polygone	*ovaloide;		//	un truc a initialiser bien
//	

}				t_anime;



typedef struct	s_client_data
{
	unsigned char	in_use;
	int				socket;
	struct in_addr	addr;
	t_anime_data	*p_a_data;
}				t_client_data;

extern int time_prg;
extern int periode;
extern t_anime lst_anime[MAX_NODE];

/*
** hook
*/

int				key_press(int keycode, t_env *e);
int				key_release(int keycode, t_env *e);
int				mouse_motion(int x, int y, t_env *e);
int				mouse_press(int button, int x, int y, t_env *e);
int				mouse_release(int button, int x, int y, t_env *e);
void			size_window_copy(double pos_low[4], double pos_height[4]);

/*
**	new_hook
*/

int				mouse_inside(int x, int y, t_win *w);
int				press_key(int key_code, t_win *w);
int				release_key(int key_code, t_win *w);
int				motion_cursor(int x, int y, t_win *w);
int				press_button(int button, int x, int y, t_win *w);
int				release_button(int button, int x, int y, t_win *w);
void			actu_mouse_pos(t_win *w, int x, int y);

/*
** mlx_env
*/

void			vectpx_to_img(t_env *e, t_matrix *pos_color);
void			env(t_env *e);
void			init_pos_ecr(t_env *e);
void			init_win_event(t_win *w, t_env *e);

/*
**	exit.c
*/

void			free_map(t_matrix	****map, t_env *e);
int				free_int_map(t_env *e);
int				free_cam(t_env *e);
int				ft_exit(t_env *e);
int				main_work(t_env *e);

/*
**	new_calcul_mandel
*/

/*
**	calcul mandelbrot
*/

void			do_zoom_simple(t_env *e);
int				resize_window(double pos[4], double mult, t_pt2d siz, t_env *e);
void			set_color_fractal(t_win *w);
void			calc_average(double pos[8], double max[4], t_env *e);
double			get_iter_average(double mult[2], double **val);
void			calcul_grid(double *img, double pos[4], t_pt2d max, t_env *e);
void			calculate_average(double **img_low, double **img_height
				, double pos_l[4], double pos_h[4]);

/*
**	drawline
*/

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
t_polygone		*scale_segment(t_polygone *src, t_border *from, t_border *to
				, double *add);
int				actu_base(t_env *e, t_polygone *src);
int				actu_transform(t_env *e, t_polygone *src);
void			print_circle2(t_matrix *mid, t_matrix *col, double r, t_win *w);
int				move_the_node(t_env *e, t_polygone *seg);
double			height_circle(double r, double x);

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

void			describe_window(t_win *w);
t_win			*window_init(t_env *e, int size_x, int size_y, char *name);
int				window_destroy(t_win **window);

void			end_transform(t_env *e);
void			end_base(t_env *e);

/*
**	poygone_new
*/

t_polygone		*creat_node(int lvl, double *pos, double *color);
t_polygone		*creat_node_fv(int lvl, t_matrix *pos, t_matrix *color);
t_polygone		*copy_node(t_polygone *node, int lvl);

/*
**	polygone_destroy
*/

int				polygone_destroy(t_polygone **begin);
int				polygone_destroy_one(t_polygone **node);

/*
**	polygone_transform
*/

void			iterate_transformation(t_polygone *polyg, t_polygone *transpos);
double			dist_to_end(t_polygone *seg);
t_polygone		*adate_to_unite(t_matrix *ux, t_matrix *uy, t_matrix *org
				, t_polygone *src);
t_polygone		*transform(t_polygone *seg_beg);
t_polygone		*creat_insert(t_polygone *seg, t_polygone *transforme);

void			init_trans_control(t_env *e);
void			calcul_and_print(t_polygone *seg, t_polygone *mult, int iter
				, t_env *e);

/*
**	polygone_maj
*/
int				nb_iter_koch(t_polygone *base, t_polygone *mult);
double			get_min_dist(t_polygone *node);
int				polygone_push_befor_last(t_polygone **begin, t_polygone *node);
int				polygone_push_back(t_polygone **begin, t_polygone *node);
int				polygone_forget_last(t_polygone **begin);

/*
**	modify_model
*/

t_polygone		*get_closer_node(t_polygone *beg, t_matrix *mouse
				, double min_dist);
void			translate_node(t_env *e, t_polygone *poly);

/*
**	color_transpose
*/

void			rgb_to_tsl_mod(t_matrix *rgb);
t_matrix		*rgb_to_tsl_new(double t, double s, double l);
t_matrix		*tsl_to_rvb_new(double t, double s, double l);
double			modulo(double a, double b);
void			tsl_to_rvb_in(double t, double s, double l, t_matrix *rvb);
int				tsl_to_rvb_int(double t, double s, double l);

/*
**	new_printing
*/

void			actu_win_rest(t_win *w);
void			actu_win(t_win *w);
t_matrix		*define_node_color(double dist_frac, double iter
				, double prog_iter);
void			draw_verticies(t_win *w, t_polygone *seg);
void			draw_vertice(t_win *w, t_polygone *seg);
void			translate_node2(t_env *e, t_polygone *poly);
int				draw_line2(t_win *win, t_matrix *mat_line);
void			draw_line3(t_matline *ml, t_win *w);
void			vectpx_to_img2(t_win *win, t_matrix *pos_color);
void			draw_simple_polygone(t_win *w, t_polygone *node);
int				init_coef_const(t_coef_const *cc, t_polygone *mult
				, double max_iter, t_win *w);
double			get_polygone_len(t_polygone *seg);

void			draw_vertice1(t_env *e, t_polygone *seg);
void			draw_verticies1(t_env *e, t_polygone *seg);

/*
**	segment_mecanique
*/

void			set_2d_landmark_incpy(t_matrix *diff, t_matrix *dx, t_matrix *dy
				, double *dist);
double			set_dist_sepc(double *data, t_matrix *dx, t_matrix *dy
				, t_polygone *node);
t_polygone		*get_cluster_seg(t_polygone *begin, double x, double y);
double			min_fabs(double	a, double b);
double			max_fabs(double	a, double b);
double			set_dist_sepc(double *data, t_matrix *dx, t_matrix *dy
				, t_polygone *node);
t_polygone		*get_cluster_seg(t_polygone *node, double x, double y);
void			set_in_grey(t_polygone *node, double value);
void			draw_prewiew(t_win *w);
void			insert_adding_node(t_win *w);
int				insert_one_node(t_polygone **target, t_polygone *src);
int				remove_one_node(t_env *e);

/*
**	printing_koch_final
*/

double			diff_2(t_matrix *pt1, t_matrix *pt2);
t_koch_changing	init_kc(t_polygone *seg, double iteration, double dist
				, double prev_du);
void			init_koch_const(t_koch_const *kco, t_polygone *transform
				, t_win *w, double *data);
void			print_koch_fractale(t_koch_const *kco, t_koch_changing kch
				, double i);
void			print_koch_fractale_anime(t_koch_const *kco, t_koch_changing kch
				, double anime);
void			print_fractal(t_env *e);

/*
**	sliding_button
*/

void			paint_circle(t_matrix *mid, t_matrix *col, double r, t_win *w);
t_slider		**init_tab_slider(int nb, t_border *inside, t_matrix *color
				, double margin);
int				slider_free(t_slider **slide);
void			draw_slider(t_win *w, t_slider *s, int witch);
void			draw_the_sliders(t_win *w, t_slider **sliders);
void			scroling_button(t_win *w, t_slider *slide, int pt);
int				select_button(t_win *w, t_slider **tabs);
t_matrix		*get_button_pos(t_slider *s, int nb);
double			get_rmax(t_slider *s);
t_slider		*init_slider(t_matrix *color, t_border *b);
int				init_the_sliders(t_win *w, t_border *the_other);

/*
**	zoom_koch.c
*/

int				get_pos_to_draw(t_win *w, t_polygone *node, t_matrix *pos_a
				, t_matrix *pos_b);
void			zoom_border(t_border *b, double x, double y, double scale);

/*
**	mandel_event
*/

int				mandel_press_key(int key_code, t_win *w);
int				mandel_release_key(int key_code, t_win *w);
int				mandel_motion_cursor(int x, int y, t_win *w);
int				mandel_press_button(int button, int x, int y, t_win *w);
int				mandel_release_button(int button, int x, int y, t_win *w);
int				do_the_translation(t_env *e, double ux, double uy);

int				do_the_zoom_simple(t_env *e, int x, int y, double mult);
int				do_the_translation(t_env *e, double ux, double uy);

/*
**	init_mandel
*/

int				init_mandel_event(t_win *w);
int				bcl_mandel(void);
double			**init_data_tab(int size_x, int size_y);
int				init_mandel(t_env *e, int id);

/*
** mini_parseur.c
*/

void			print_usage(char tab[NB_NAME_FRAC][NB_NAME_ALT][NB_LETTER_NAME]
				, char *name);
int				check_one_id(char tab[NB_NAME_FRAC][NB_NAME_ALT][NB_LETTER_NAME]
				, char *name, int *id);
int				check_id(char tab[NB_NAME_FRAC][NB_NAME_ALT][NB_LETTER_NAME]
				, int ac, char **av, int *id);
int				check_syntax(int *id);
int				parse_imput(int ac, char **av
				, char tab[NB_NAME_FRAC][NB_NAME_ALT][NB_LETTER_NAME]);
void			print_binary(int nb);

/*
**	main.c
*/

void			init_fractol(int id);

/*
**	init_param_koch.c
*/
int				init_statment(t_env *e);
void			sliders_set_valu(t_slider *slide, double v1, double v2);
t_polygone		*init_segment(double valu[4][2], int nb, t_border *boder
				, double min);

/*
**	test:
**		c'est le fichier qui aurra les fonciton de teste avant integration
*/
void	feature_testing(t_env *e);

/*
**	paint_rectangle.c
*/
void	paint_rectangle(t_win *w, t_matrix *col, t_border *rec);
void	draw_rectangle(t_win *w, t_matrix *col, t_border *rec);

/*
**	user_interface.c
*/
void	print_anime_box(t_win *w, t_polygone *poly, t_anime *anime, t_border *b);
int		select_anime_box(t_win *w, t_border *b);
void	draw_param_ui(t_env *e);

/*
**	border.c
*/
t_border	*creat_border(int x0, int x1, int y0, int y1);
void		init_border(t_border *b, int x0, int x1, int y0, int y1);

/*
**	ellipsoide.c
*/
double			get_time_ellipse_anime(t_env *e, t_anime *a);
void		draw_preview_one_anime(t_win *w, t_anime *anime, t_matrix *pos, double time);
void			draw_ellipsoide(t_win *w, t_polygone *pt);
t_matrix		*ellipsoide_shape(t_polygone *pt, double t);
double			my_modf1(double res);

//	a metre ua bon endroi
void		draw_preview_anime(t_win *w);

/*
**	===================	NETWORK	======================
*/

typedef	struct	s_ifs_param
{
	t_polygone	*trans;
	t_polygone	*base;
	int			transform_len;
	int			base_len;
	int			max_iter;
	double	col_val[6];	// les parametre de couleur

}				t_ifs_param;

typedef	struct	s_data_nw
{
	double	pt_trans[MAX_NODE][2];
	double	pt_base[MAX_NODE][2];
	int		trans_len;
	int		base_len;
	int		max_iter;
	double	col_val[6];	// les parametre de couleur
}				t_data_nw;

typedef	struct	s_ifs_ocl
{
	float	pt_trans[MAX_NODE][2];
	float	pt_base[MAX_NODE][2];
	int		trans_len;
	int		base_len;
	int		max_iter;
	float	col_val[6];	// les parametre de couleur
}				t_ifs_ocl;




int	get_server_socket(int ss);

int				remove_client(size_t socket_id);
int				add_client(
					int					new_socket,
					struct in_addr		new_addr);
size_t			get_all_client_data(
					t_client_data **p_client_data);

void			close_sockets(int s);
int				create_server(int port);
void			add_new_client(int new_sock);
void			wait_for_event(int sock, fd_set *active_fd, int status);
t_env			*get_env(t_env *e);


int				get_client_socket(int ss);
int				create_client(char *addr, int port);

/*
**	polygone_adapte.c
*/

int			format_data_to_print(t_data_nw *data_src, t_ifs_param *data_dst);
t_data_nw	format_data_to_network(t_polygone *transform, t_polygone *base, int nb_iter, double col[6]);
void		print_client_ifs(t_win *w, t_ifs_param *param);

//	debug
void	polygone_describe(t_polygone *node);
void	matrix_describe(t_matrix *mat);
void 	print_data_ifs(t_ifs_param *data);


/*
**	animation.c
*/
# define MAX_SPEED 5
int				init_t_anime(t_anime *anime, t_border *b_anime, t_border *b_speed, t_border *b_offset);
void			init_lst_anime(t_env *e);
t_polygone		*init_ovaloid(t_border *b);
void			draw_preview_path(t_env *e);
t_polygone		*apply_ellipse_anime(t_polygone *org);
void			scrol_button_anime(t_win *w, t_anime *anime);


//////////////////// OPENCL PART ///////////////////////////////

/*
 * read_file.c
*/
char	*read_file(const char *name, size_t *str_size);

/*
 * 
 * */

# define BUFF_FILE_SIZE 128

typedef	struct	s_buff_file	t_buff_file;

struct			s_buff_file
{
	int			size;
	char		buff[BUFF_FILE_SIZE];
		t_buff_file	*next;
};

#endif
