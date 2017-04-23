/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:23:10 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/22 21:22:39 by fjanoty          ###   ########.fr       */
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
	if (ret[4])
	{
		size_t	size = 0;
		//main code
		clGetProgramBuildInfo(core->program, core->device_id, CL_PROGRAM_BUILD_LOG ,0,NULL,&size);
		char *buildlog=(char*)malloc(size);
		clGetProgramBuildInfo(core->program, core->device_id, CL_PROGRAM_BUILD_LOG ,size,buildlog,NULL);
		printf("\n\nBuildlog:   %s\n\n",buildlog);
		free(buildlog);
	}
	return (check_ocl_err(ret, 5, __func__, __FILE__));	
}

//	on va faire une fonction generique pour initialiser la base d'un kernel
int	init_kernel(t_ocl_core *core, t_ocl_ker *ker, const char *kernel_name)
{
	cl_int ret[2];

	if (!core || !ker)
		return (1);

	ker->command_queue = clCreateCommandQueue(core->context, core->device_id, 0, ret + 0);
	ker->kernel = clCreateKernel(core->program, kernel_name, ret + 1);
	ker->context = core->context;
	return (check_ocl_err(ret, 2, __func__, __FILE__));
}

int	branch_arg_to_kernel(t_ocl_ker *ker, int nb_arg_buff)
{
	int		i;
	cl_int	ret;

	i = 0;
	while (i < nb_arg_buff)
	{
		// peut etre un equivalent de write du buffer... a medite
		if ((ret = clSetKernelArg(ker->kernel, i, sizeof(cl_mem), (void *)&(ker->data[i].gpu_buff))))
			print_ocl_error(ret, i, __FILE__, __func__);
		i++;
	}
	return (0);
}

cl_int	ocl_create_mem(t_ocl_ker *ker, int id_arg, short io_acces, size_t size)
{
	cl_int	ret;
	
	ker->data[id_arg].gpu_buff = clCreateBuffer(ker->context, io_acces, size, NULL, &ret);
	ker->data[id_arg].cpu_buff = NULL;
	ker->data[id_arg].size = size;
	ker->data[id_arg].io_acces = io_acces;
	return (ret);
}

cl_int	ocl_init_mem(t_ocl_ker *ker, int id_arg, short io_acces, size_t size, cl_mem buff)
{
	cl_int	ret;
	
	ker->data[id_arg].gpu_buff = buff;
	ker->data[id_arg].cpu_buff = NULL;
	ker->data[id_arg].size = size;
	ker->data[id_arg].io_acces = io_acces;
	return (ret);
}

cl_int	ocl_set_mem(t_ocl_ker *ker, t_ocl_mem *mem_src, int id_arg, short io_acces, size_t size, cl_mem buff)
{
	cl_int	ret;
	
	ker->data[id_arg].gpu_buff = mem_src->gpu_buff;
	ker->data[id_arg].cpu_buff = mem_src->cpu_buff;
	ker->data[id_arg].size = mem_src->size;
	ker->data[id_arg].io_acces = mem_src->io_acces;
	return (ret);

}
