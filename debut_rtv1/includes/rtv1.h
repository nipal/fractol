/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 02:08:51 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/19 21:24:57 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define KEY_PRESS                2
# define KEY_RELEASE              3
# define BUTTON_PRESS             4
# define BUTTON_RELEASE           5
# define MOTION_NOTIFY            6

# include "mlx.h"
# include "libft.h"
# include "c_maths.h"

# include <stdio.h>	
# include <stdlib.h>
# include <OpenCL/opencl.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>	
# include <stdlib.h>

# include <OpenCL/opencl.h>
# include <math.h>
# define MAX_SOURCE_SIZE (0xf0000)	

char* g_ocl_error[100];


/*
   ON va faire une structure keybord et mousse avec plein de truc cool
   (en mode interface a lib)
   */

//	# define SIZE_X 1024
//	# define SIZE_Y 768
# define SIZE_X 1024
# define SIZE_Y 768
# define NB_KERNEL 10

//	on pourrai avoir un kernel dinitialisation
# define TEST_IMAGE 0
# define INIT_FRAME 1
# define TEST_STRUCT 2
# define DRAW_LINE 3

/*
 **	dans t_ocl on a juste les variable de base pour lancer un kernel
 **	apres on aurras sois une structure par kernel sois un tableau sois un verra
 */



# define BUFF_FILE_SIZE 128

typedef	struct	s_buff_file	t_buff_file;
struct			s_buff_file
{
	int			size;
	char		buff[BUFF_FILE_SIZE];
		t_buff_file	*next;
};




/*
 **	Il y aurra un tableau d'index.
 **	Pour chaque classe, une liste d'id d'objet
 **	ca pourra etre chiant pour les lumier,  a moins qu'elles aient un plage d'id resever
 */
 
# define LIGHT 0
# define SPHERE 1
# define PLAN 2
# define CYLINDER 3
# define CONE 4

# define NB_OBJ 10
/*
**	C'est la structure qui caraterise un objet
*/	

typedef	struct			s_obj
{
	int					id;
	int					color;
	int					type;
	float				coef;
	float				position[4];
	float				angle[4];
	float				mat_rot[16];
}						t_obj;

/*
**	Il faudrait aussi faire la structure du buffer de rendue:
**	C'est lui qui serra calculer pour definir les lumiere
**		donc un a le lot d'info:
**			(distance (cam, obj), vecteur (cam, obj) [&&]  distance (obj, lum) , vecteur (obj, lum) [&&] couleur obj, couleur lum)
**		## pour l'instant la question c'est de savoir si il y a une importance a se placer dans un repere ou un autre...
**
**	Normalement tout les vecteur sont norme
**
** 	C'est le buffer pour calculer les lumiere
**   |
**   |
**   V
*/

/*	on a une structure a 4 * 16 octet maiiii	*/
typedef	struct			s_lbuffer
{
	float				dir_cam_obj[4];
	float				dir_obj_lum[4];
	float				dir_normal[4];
	float				dist_cam_obj;
	float				dist_obj_lum;
	int					obj_color;
	int					lum_color;
	int					id;
	int					form;
	float				pos_tmp[4];
	
}						t_lbuffer;


typedef	struct			s_init_ocl_param
{
	cl_platform_id		platform_id;
	cl_device_id		device_id;
}						t_init_ocl_param;

typedef	struct			s_param_buffer
{
	int					all_type[NB_OBJ];
	int					all_collor[NB_OBJ];
	float				all_coef[NB_OBJ];
	float				all_pos[NB_OBJ * 4];
	float				all_angle[NB_OBJ * 4];
	float				all_mat_rot[NB_OBJ * 16];
	int					current;

	cl_mem				ocl_type;
	cl_mem				ocl_collor;
	cl_mem				ocl_coef;
	cl_mem				ocl_pos;
	cl_mem				ocl_mat_rot;
	cl_mem				ocl_angle;   
	cl_mem				ocl_normal;
}						t_param_buffer;



typedef	struct			s_mem_ocl
{
	cl_mem				ocl_time;
	cl_mem				ocl_data;
	int					*img_data;
	float				cam[4 * 4];
	cl_mem				ocl_cam;
	cl_mem				ocl_ray_dir;
	float				*ray_dir;

	cl_mem				ocl_zbuffer_id;
	cl_mem				ocl_tab_obj;
	float				*tab_obj;


	t_obj				all_obj[NB_OBJ];
	t_obj				all_obj_out[NB_OBJ];	//	pour verifier si le pading est bon
	cl_mem				ocl_obj;
	cl_mem				ocl_obj_out;			//	pour verifier si le pading est bon

}						t_mem_ocl;

typedef	struct			s_ocl
{
	cl_platform_id		platform_id;		// on peut init a null
	cl_device_id		device_id;			// on peut init a null
	cl_program			program;
	cl_context			context;
	cl_command_queue	command_queue[NB_KERNEL];
	cl_kernel			kernel[NB_KERNEL];
}						t_ocl;

/*
 **	t_kernel sert a avoir une tache en particulier
 */

typedef	struct			s_kernel
{
	cl_command_queue	command_queue;
	cl_kernel			kernel;
}						t_kernel;

typedef	union			u_pix
{
	int					nb;
	char				comp[4];
}						t_pix;

typedef	struct			s_env	t_env;

typedef	struct			s_win
{
	void				*img;
	void				*win;
	int					size_line;
	int					depth;
	int					endian;
	t_pix				*data;
	t_env				*e;
	char				*name;
	int					size_x;
	int					size_y;

	float				cam_ang_incr;
	float				cam_angle[4];
	float				cam_pos[4];
	float				mouse_pos[4];
	float				mouse_prev_pos[4];
	int					mode_cursor;
	int					cursor_on;

	t_param_buffer		param;
}						t_win;

typedef	struct			s_cam
{
	float				landmark[16];
}						t_cam;


struct					s_env
{
	void				*mlx;
	t_win				*win_rt;
	t_ocl				*ocl;
	t_mem_ocl			*mem_ocl;
};


/*
 **	init_rtv1
 */
int						run_rtv1();
int						main_bcl(t_env *e);


/*
 **	init_win
 */
t_win					*window_init(t_env *e, int size_x, int size_y, char *name);
int						ft_free(void **ptr);
int						window_destroy(t_win **w);
void					init_win_event(t_win *w);

/*
 **	init_opencl
 */
int						init_opencl(t_env *e, int size_x, int size_y);

t_ocl					*init_kernel(int size_x, int size_y, const char *name_file);
t_mem_ocl				*init_mem_ocl(t_win *w, t_ocl *ocl);
int						main_while_ocl(t_mem_ocl *mem, t_ocl *ocl, t_win *w);
void					actual_ocl_data(t_mem_ocl *mem);
int						destroy_ocl(t_ocl **ocl);
int						destroy_mem_ocl(t_mem_ocl **mem);

/*
 **	event
 */

int						press_key(int key_code, t_win *w);
int						release_key(int key_code, t_win *w);
int						motion_cursor(int x, int y, t_win *w);
int						press_cursor(int button, int x, int y, t_win *w);
int						release_cursor(int button, int x, int y, t_win *w);

/*
 **	exit
 */
int						ft_exit(t_env *e);

/*
 **	hook
 */
int						main_while_ocl(t_mem_ocl *mem, t_ocl *ocl, t_win *w);
t_mem_ocl				*init_mem_ocl(t_win *w, t_ocl *ocl);

/*
 **	math_vector
 */
void					mat_vector_prod(float *mat, float *vect);
void					set_vect_val(float *vect, float a, float b, float c);
void					set_identity_in(float *dest);
void					set_rot_mat4(float *mat, float angle, int id1, int id2);
void					set_rot_mat4_all(float *mat, float x, float y, float z);
void					mult_mat4_in(float *mat1, float *mat2, float *mat_in);
void					set_landmark(float *landmark, float *ang, float *pos);
void					print_mat4(float *mat);
void					print_vect4(float *vect);
float					vect_dot4(float *vecta, float *vectb);
void					set_rot_mat4(float *mat, float angle, int id1, int id2);

/*
 **	manage_objet
 */
int						add_light(t_param_buffer *param, float *pos, int color);
int						add_sphere(t_param_buffer *param, float *pos, int color, float radius);
int						add_plan(t_param_buffer *param, float *pos, int color, float *dir);
int						add_cylindre(t_param_buffer *param, float *pos, int color, float *dir);
int						add_cone(t_param_buffer *param, float *pos, int color, float *dir);

/*
 **	read_oclfile
 */
int						open_file(const char *name);
t_buff_file				*get_next(int fd);
t_buff_file				*stack_buff_file(int fd, int *total_size, int *nb_buff);
int						destroy_buff_file_stack(t_buff_file **beg);
int						copy_stack_in_str(t_buff_file *beg, int nb_buff, int size, char *str);
char					*read_file(const char *name, size_t *str_size);

/*
 **	error_opencl
 */
void					init_ocl_error();
int						print_ocl_error(int err_cl, int nb, char *name);
#endif
