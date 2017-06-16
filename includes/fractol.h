/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 20:54:37 by fjanoty           #+#    #+#             */
/*   Updated: 2017/06/16 21:45:50 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define NB_KER 4

# define HARD_ITER 7
# define HARD_BASE_LEN 4
# define HARD_TRANS_LEN 2

# define MAX_NODE 16	// c'est deja enorme on aurra des gros problem de perfe a partir de 9

# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# define SIZE_KOCH_X 1200
# define SIZE_KOCH_Y 1200
# define KEY_PRESS                2
# define MOUSE_IN mouse_in_border

# define X 0
# define Y 1


typedef	struct s_env		t_env;
typedef	struct s_win		t_win;
typedef	unsigned	long	ulong;

///////////// ocl_render /////////////
#include <OpenCL/opencl.h>	

# define BIG_OCL_BUF_SIZE 37500000 // pour retomber sur 300 mo
# define MAX_ITER 20 // vraiment... c'est trop pour un buffer mais bon... OK
# define ARG_KER_MAX 6
# define IFS_CALCUL_PT 0	// il faut vraiment queje me mette au enum, mais j'ai tellement la fleme
# define DRAW_LINE 1		// no comment 

# define MAX_GPU_BUFF 1048576 * 100  // (2^20) * 500 ==> 500 Mo

enum	e_ocl_kernel
{
	e_ifs_calcul_pt,
	e_define_color,
	e_draw_line,
};

enum	e_ker_calcul_ifs_point
{
	e_cip_pt_ifs		= 0,
	e_cip_param,
	e_cip_iter,
};

enum	e_ker_define_color
{
	e_dc_col,
	e_dc_param
};

enum	e_ker_draw_line
{
	e_dl_img,
	e_dl_pt,
	e_dl_col,
	e_dl_param	
};

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

typedef	struct			s_ocl_ker
{
	cl_context			context;
	cl_kernel			kernel;
	cl_command_queue	command_queue;
	t_ocl_mem			data[ARG_KER_MAX];
	int					nb_arg;
}						t_ocl_ker;

typedef	struct	s_range
{
	float		beg;
	float		end;
	float		delta;
	float		none;
}				t_range;


typedef	struct	s_ifs_spec
{
	float	pt_base[MAX_NODE][2];
	float	pt_trans[MAX_NODE][2];
	int		beg_id[MAX_ITER];
	int		len_base;
	int		len_trans;
	int		max_iter;
	int		max_pt;
	int		ecr_x;
	int		ecr_y;
	int		nb_iter;
	t_range	hue;
	t_range	sat;
	t_range	val;
}				t_ifs_spec;

int	ocl_mem_creat_calcul_ifs(t_ocl_ker *ifs_ker);
int	ocl_mem_creat_define_color(t_ocl_ker *def_col, size_t size_colore, t_ocl_mem *spec);
int	ocl_mem_creat_draw_line(t_ocl_ker *ifs_ker, size_t img_size, t_ocl_mem *buff_pt, t_ocl_mem *buff_col, t_ocl_mem *ifs_spec);

int	check_ocl_err(cl_int *ret, int nb_ret, const char *func_name, const char *file_name);

int	init_ifs(t_env *e, t_win *w);

/*
 *	error_opencl.c	
 * */
int		print_ocl_error(int err_cl, int no_err, const char *file, const char *func);
void	init_ocl_error(void);

/*
 *	ocl_format_ifs_calcul.c
 * */
int		set_id_isf_ptbuff(int nb_base, int nb_trans, int nb_iter, int *indice_beg);
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

/*
 *	tout les osl run, il faudra un peu faire le menage la c'est tout sal
 * */
int	ocl_render_run(t_env *e);
int	ocl_ifs_calcul_run(t_ocl_ker *ifs_cl, int nb_iter, float col[6]);
int	ocl_run_draw_line(t_ocl_ker *dl, int *id_tab, int max_iter);
int	ocl_run_define_colore(t_env *e, t_ocl_ker *def_col, int *id_tab);

///////// end_ocl //////////////////

void			actu_win_rest(t_win *w);
void			actu_win(t_win *w);


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
}				t_win;

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
	int			max_iter;
	t_win		*fractal;
	//////// openCl ////////////
	t_ocl_core	ocl;
	t_ocl_ker	ker[NB_KER];
};
int				ft_exit(t_env *e);
/*
**	exit.c
*/
typedef	struct	s_ifs_ocl
{
	float	pt_trans[MAX_NODE][2];
	float	pt_base[MAX_NODE][2];
	int		trans_len;
	int		base_len;
	int		max_iter;
	float	col_val[6];	// les parametre de couleur
}				t_ifs_ocl;


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
