/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:23:10 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/12 20:50:27 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// init -> on definie des valeur de base et on ne fait pas de malloc
// 		-> on malloc une structure

#include "mini_include.h"


/*
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
	int					size;
}						t_ocl_mem;

//	On aura besoin d'un structure par kernel
typedef	struct			s_ocl_ker
{
	cl_kernel			kernel;
	cl_command_queue	command_queue;
	t_ocl_mem			data[ARG_KER_MAX];
}						t_ocl_ker;
*/

/*
 *	on pourrai prendre en parametre le nom de la fonction et du fichier don on vien et d'indiquer l'indice
 *	qui a eu une erreur. Et donc voila
 * */
int	check_ocl_err(cl_int *ret, int nb_ret, const char *func_name, const char *file_name)
{
	int	i;

	i = 0;
	while (i < nb_ret)
	{
		if (ret[i])
		{
			printf("error file:%s	function:%s	ret[%d]:%d\n", file_name, func_name, i, ret[i]);
			return (ret[i]);
		}
		i++;
	}
	return (0);
}

int	init_ocl_core(t_ocl_core *core, const char *file_name)
{
	cl_uint	ret_num_devices;
	cl_uint	ret_num_platforms;
	cl_int ret[5];
	size_t source_size;
	char *source_str;

	if (!core)	
		return (1);
	if (!(source_str = read_file(file_name, &source_size)))
		return (2);

	ret[0] = clGetPlatformIDs(1, &(core->platform_id), &(ret_num_platforms));
	ret[1] = clGetDeviceIDs(core->platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &(core->device_id), &ret_num_devices);
	core->context = clCreateContext(NULL, 1, &(core->device_id), NULL, NULL, ret + 2);
	core->program = clCreateProgramWithSource(core->context, 1, (const char **)&source_str, (const size_t *)&source_size, ret + 3);
	ret[4] = clBuildProgram(core->program, 1, &(core->device_id), NULL, NULL, NULL);
	return (check_ocl_err(ret, 5, __func__, __FILE__));	
}

//	on va faire une fonction generique pour initialiser la base d'un kernel
int	init_kernel(t_ocl_core *core, t_ocl_ker *ker, const char *kernel_name)
{
	cl_int ret[2];

	if (!core || !ker)
		return (1);

	// Create Command Queue 
	ker->command_queue = clCreateCommandQueue(core->context, core->device_id, 0, ret + 0);
	// Create OpenCL Kernel 
	ker->kernel = clCreateKernel(core->program, kernel_name, ret + 1);
	return (check_ocl_err(ret, 2, __func__, __FILE__));
}

int	init_kernel_calcul_ifs(t_ocl_core *core, t_ocl_ker *ifs_kernel)
{
	//	il faut reserver la memoir donc connaitre la taille de truc que voila
	//		- on peu faire des test de memoir pour ce qu'on peu reserver au max

	(void)core;
	(void)ifs_kernel;	


	// et binder ce qu'il y a a faire	
	return (0);
}

/*
int	init_ocl_ker();
int	init_ocl_ker_mem();
int	init_ocl_ker_arg();
*/

//	pour l'instant je peu faire un truc un peu monolitique pour la partie kernel et tout
//	apres on vera pour faire un archi supercool toutca toutca

/*
 *	Il faut determiner des structure de variable pour facilement nitialiser les bail
 *	des fonction qui ne font qu'une seul tache
 * */
