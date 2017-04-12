/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_include.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:28:46 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/12 20:58:18 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINI_INCLUDE
# define MINI_INCLUDE

/////////////// read_file /////////////

#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

# define BUFF_FILE_SIZE 128

typedef	struct	s_buff_file	t_buff_file;

struct			s_buff_file
{
	int			size;
	char		buff[BUFF_FILE_SIZE];
		t_buff_file	*next;
};

char	*read_file(const char *name, size_t *str_size);

///////////// ocl_render /////////////
//
#include <OpenCL/opencl.h>	

# define ARG_KER_MAX 10

//	on aura besoinr que d'une seule structure comme celle la pour tout le programe
typedef	struct		s_ocl_core
{
	cl_platform_id	platform_id;
	cl_device_id	device_id;
	cl_program		program;
	cl_context		context;	// c'est une variable qu'on initialise qu'une fois mais qu'on a souvent besoin
}					t_ocl_core;

/*
 *	c'est une structure qui englobe un peut toutes la gesiton de la memoir qui transite entre le gpu et le cpu
 *	dans le but de pouvoir faire passer dans une boucle qui automatise un peu les baille quand on aurra arreter 
 *	de coder avec le cul
 * */

typedef	struct			s_ocl_mem
{
	cl_mem				gpu_buff;
	void				*cpu_buff;
	size_t				size_total;
	size_t				size_used;
	short				io_acces;
}						t_ocl_mem;

//	On aura besoin d'un structure par kernel
typedef	struct			s_ocl_ker
{
	cl_kernel			kernel;
	cl_command_queue	command_queue;
	t_ocl_mem			data[ARG_KER_MAX];
}						t_ocl_ker;

int	init_ocl_core(t_ocl_core *core, const char *file_name);
int	init_kernel(t_ocl_core *core, t_ocl_ker *ker, const char *kernel_name);


//	un truc deja existant dans fractol.h
# define MAX_NODE 20	// c'est deja enorme on aurra des gros problem de perfe a partir de 9

#endif
