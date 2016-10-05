/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 02:21:11 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/05 04:14:29 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "c_maths.h"
# include <errno.h>
# include <string.h>

# define R 0
# define G 1
# define B 2

# define X 0
# define Y 1
# define Z 2

# define BEG_X 0
# define END_X 1
# define DELTA_Y 2
# define BEG_Y 3
# define MAX_Y 4
# define MIN_Y 5

# define X 0
# define Y1 1
# define Y2 2

# define BEG_Z 0
# define DELTA_Z 1

# define X1 0
# define Y1 1
# define Z1 2
# define DX 3
# define DY 4
# define DZ 5
# define R1 6
# define G1 7
# define B1 8
# define DR 9
# define DG 10
# define DB 11
# define NORME 12

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
	int					decal_down;
	int					decal_up;
	int					decal_right;
	int					decal_left;
	int					zoom;
	int					zoom_back;
	int					cte1_increase;
	int					cte1_decrease;
	int					isometric;
	int					parallel;
	int					conic;
	int					scale_increase;
	int					scale_decrease;
	int					r;
	int					g;
	int					b;
	int					rot_x1;
	int					rot_y1;
	int					rot_z1;
	int					rot_x2;
	int					rot_y2;
	int					rot_z2;
	int					rot_cam_x1;
	int					rot_cam_x2;
	int					rot_cam_y1;
	int					rot_cam_y2;
	int					rot_cam_z1;
	int					rot_cam_z2;
	int					speed_up;
	int					speed_down;
	int					speed_stop;
	int					fi1;
	int					fi_1;
	int					fi2;
	int					fi_2;
	int					view;
	int					draw;
	int					switch_anime;
	int					z_up;
	int					z_down;
}						t_key;

# define TOP_LEFT 0
# define BOTOM_LEFT 1
# define BOTOM_RIGHT 2
# define TOP_RIGHT 3

# define LEFT 0
# define BOTOM 1
# define RIGHT 2
# define TOP 3

typedef	struct			s_cam
{
	t_matrix			**corner;
	t_matrix			**base;
	t_matrix			*pos;
	t_matrix			*dir;
	t_matrix			*rot;
}						t_cam;

# define SIZE_Y 1900
# define SIZE_X 1200
# define PRINT_DIAG 0

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	void				*img;
	t_pix				*data;
	double				*z_buffer;
	int					size_line;
	int					ecr_x;
	int					ecr_y;
	int					depth;
	int					endian;
	int					**map;
	double				**map_d;
	t_matrix			***color_map;
	t_matrix			***vect_map;
	int					proj;
	double				scale;
	double				cte1;
	int					decalx;
	int					decaly;
	int					zoom;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
	t_key				key;
	int					size_map_x;
	int					size_map_y;
	double				z_min;
	double				z_max;
	double				rot_x;
	double				rot_y;
	double				rot_z;
	double				speed;
	t_cam				*cam;
	double				dr1;
	double				dr2;
	int					view;
	int					view_sw;
	int					draw;
	int					draw_sw;
	double				k;
	double				phi1;
	double				phi2;
	double				beta;
	double				increm;
	int					nb_frame;
	double				advence;
	double				mult_z;
	
	int					img_low[SIZE_Y][SIZE_X];
	int					img_height[SIZE_Y * 2 + 2][SIZE_X * 2 + 2];
	int					x_maxl;
	int					y_maxl;
	int					x_maxh;
	int					y_maxh;
	int					iter;
}						t_env;

typedef struct			s_point
{
	int					x;
	int					y;
	int					z;
	unsigned int		color;
}						t_point;

/*
** hook
*/
void					init_t_key(t_key *key);
int						key_press(int keycode, t_env *e);
int						key_release(int keycode, t_env *e);

void					init_t_key_2(t_key *key);
void					init_t_key(t_key *key);
void					key_press_end(int keycode, t_env *e);
int						key_press(int keycode, t_env *e);

void					key_release_end(int keycode, t_env *e);
int						key_release(int keycode, t_env *e);
int						increm_dir_cam(t_env *e);
void					increm_pos_cam(t_env *e);
void					manage_cam_rot(t_env *e);

int						loop_hook(t_env *e);

/*
** mlx_env
*/
t_matrix				*finishe_color(t_env *e, double *pak);
t_matrix				*get_max_zdim(int **map, int size_x, int size_y);
void					px_to_img(t_env *e, int x, int y, int color);
void					vectpx_to_img(t_env *e, t_matrix *pos_color);
void					print_state(t_env *e);

void					env(int **map, int size_x, int size_y);
/*
** coord
*/

/*
**	cam
*/
t_cam					*init_cam(double fov_y, double fov_x, t_env *e);
void					describe_cam(t_cam *cam);
/*
** print_map
*/
void					define_color(t_matrix *point, t_matrix *color);
void					get_point(t_matrix ***map, t_matrix **point,
						int i, int j);
void					print_map(t_env *e, t_cam *cam, t_matrix ***map);

/*
** draw
*/
void					draw_point(t_env *e);
/*
** parse
*/
int						**parse(int fd);
char					*maps_name(char *str);

/*
**	draw_line_triangle.c
*/
int						draw_line(t_env *e, t_matrix *mat_line);
t_matrix				*init_mat_line(t_matrix *pt1, t_matrix *pt2,
						t_matrix *c1, t_matrix *c2);
t_matrix				*init_mat_line2(t_matrix *pt_color, t_matrix *pt3,
						t_matrix *c3);
int						draw_triangle(t_env *e, t_matrix *mat_line,
						t_matrix *pt3, t_matrix *c3);

/*
**	draw_link_face.c
*/
void					draw_link_map2(t_env *e, t_matrix ***map,
						t_matrix *c1, t_matrix *c2);
void					draw_link_map(t_env *e, t_matrix ***map);
void					draw_face_map(t_env *e, t_matrix ***map,
						t_matrix *mat_l);

/*
**	map_adapt_to_cam.c
*/
void					conique_adapte(t_matrix *vect);
int						is_out(t_matrix *vect, t_env *e);
int						ato(t_matrix *vect1, t_matrix *vect2, t_env *e);
t_matrix				*base_change_scalar(t_cam *cam, t_matrix *vect);
void					base_change(t_env *e, t_cam *c, t_matrix ***map,
						t_matrix *rot_cam);

/*
**	its_parse_time.c
*/
t_list					*read_line_number(int fd);
void					ft_replace(char *str, char *to_find, char replace);
void					ft_replace(char *str, char *to_find, char replace);
int						*get_number_from_str(char **char_nb, int *size);
int						free_char_split(char **tab);
t_list					*read_line_number(int fd);

t_matrix				***get_map(t_env *e);
int						**get_the_map(int fd, int *x_max, int *y_max);

void					free_map(t_matrix	****map, t_env *e);
int						free_int_map(t_env *e);
int						free_cam(t_env *e);
int						ft_exit(t_env **e);

void					draw_point_old(t_env *e);
void					main_work(t_env *e);
double					**cast_tab(int **tab, int x, int y);

int	loop_mouse_clic(int button, int x, int y, t_env *e);
int	loop_mouse_move(int x, int y, t_env *e);
t_env	*get_env(t_env *e);


void	resize_window(double pos[4], double mult, double x, double y);
void	set_color_fractal(t_env *e);
void	calc_average(double pos[8], double max[4], t_env *e);
int		get_iter_average(double mult[2], int val[SIZE_Y * 2 + 2][SIZE_X * 2 + 2]);
int		get_gray_color(int valu, int max_iter);
void	calcul_hgrid(t_env *e, double pos[4]);
int		calcul_one_point(double ct[2], int iter);
#endif
