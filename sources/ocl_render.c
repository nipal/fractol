/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:23:10 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/13 14:25:03 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// init -> on definie des valeur de base et on ne fait pas de malloc
// 		-> on malloc une structure

#include "fractol.h"
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
			print_ocl_error(ret[i], i, file_name, func_name);
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

int	branch_arg_to_kernel(t_ocl_ker *ker, int nb_arg_buff)
{
	int		i;
	cl_int	ret;

	i = 0;
	while (i < nb_arg_buff)
	{
		if ((ret = clSetKernelArg(ker->kernel, i, sizeof(cl_mem), (void *)&(ker->data[i].gpu_buff))))
			print_ocl_error(ret, i, __FILE__, __func__);
		i++;
	}
	return (0);
}


int	init_mem_calcul_ifs(t_ocl_core *core, t_ocl_ker *ifs_ker)
{
	cl_int	ret[5];

	//	arg0 pt_ifs: le buffer de point a caluculer un tru qui ne sort jamais d'opencl
	ifs_ker->data[0].gpu_buff = clCreateBuffer(core->context, CL_MEM_READ_WRITE, BIG_OCL_BUF_SIZE * sizeof(float) * 2, NULL, ret + 0);
	ifs_ker->data[0].cpu_buff = NULL; // on les met tous a NULL on verra plus tard
	ifs_ker->data[0].size = BIG_OCL_BUF_SIZE * sizeof(float) * 2;
	ifs_ker->data[0].io_acces = CL_MEM_READ_WRITE; 
	
	//	arg1 transform: les points de transformation pour tout ca quoi
	ifs_ker->data[1].gpu_buff = clCreateBuffer(core->context, CL_MEM_READ_ONLY, MAX_NODE * sizeof(float) * 2, NULL, ret + 1);
	ifs_ker->data[1].cpu_buff = NULL; // on les met tous a NULL on verra plus tard
	ifs_ker->data[1].size = MAX_NODE * sizeof(float) * 2;
	ifs_ker->data[1].io_acces = CL_MEM_READ_ONLY; 
	
	//	arg2 beg_dat_id: les indice de debut de chaque section (les transche d'iterration)
	ifs_ker->data[2].gpu_buff = clCreateBuffer(core->context, CL_MEM_READ_ONLY, MAX_ITER * sizeof(int), NULL, ret + 2);
	ifs_ker->data[2].cpu_buff = NULL; // on les met tous a NULL on verra plus tard
	ifs_ker->data[2].size = MAX_ITER * sizeof(int);
	ifs_ker->data[2].io_acces = CL_MEM_READ_ONLY; 

	// arg3 trans_len
	ifs_ker->data[3].gpu_buff = clCreateBuffer(core->context, CL_MEM_READ_ONLY, sizeof(int), NULL, ret + 3);
	ifs_ker->data[3].cpu_buff = NULL; // on les met tous a NULL on verra plus tard
	ifs_ker->data[3].size = sizeof(int);
	ifs_ker->data[3].io_acces = CL_MEM_READ_ONLY; 

	// arg4 num_iter
	ifs_ker->data[4].gpu_buff = clCreateBuffer(core->context, CL_MEM_READ_ONLY, sizeof(int), NULL, ret + 4);
	ifs_ker->data[4].cpu_buff = NULL; // on les met tous a NULL on verra plus tard
	ifs_ker->data[4].size = sizeof(int);
	ifs_ker->data[4].io_acces = CL_MEM_READ_ONLY; 

	branch_arg_to_kernel(ifs_ker, 5);
	return (check_ocl_err(ret, 5, __func__, __FILE__));
}

int	init_kernel_calcul_ifs(t_ocl_core *core, t_ocl_ker *ifs_cl)
{
	
//__kernel	void	calcul_ifs_point(__global float2 *pt_ifs, __global float2 *transform, __global int *beg_data_id, int trans_len, int num_iter)
		

	// et binder ce qu'il y a a faire	
	(void)core;
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

/*
 
typedef	struct			s_ocl_mem
{
	cl_mem				gpu_buff;
	void				*cpu_buff;
	size_t				size_total;
	size_t				size_used;
	short				io_acces;
}						t_ocl_mem;
 * */

/*
 * On va faire une fonction de lancement des kernel. Et en gros ce qu'il faut pour que ca marche
 * 	- formater la data a lui transmetre (tout les buffer)
 * 	- gerer l'envoie des data du CPU -> GPU
 * 	- lancer les kernel avec les bon parametre (le nombre la taille tout ca)
 * 	- gerer la reception des data opencl (donc pour nous le buffer graphique de la mlx)
 * */


