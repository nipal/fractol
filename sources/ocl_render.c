/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:23:10 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/12 16:57:56 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// init -> on definie des valeur de base et on ne fait pas de malloc
// 		-> on malloc une structure

#include "fractol.h"

#include <CL/cl.h>	

#define MEM_SIZE (128)	
#define MAX_SOURCE_SIZE (0x100000)	

# define ARG_KER_MAX 10

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

int	init_ocl_core(t_ocl_core *core, const char *file_name)
{
	cl_uint	ret_num_devices;
	cl_uint	ret_num_platforms;
	cl_int ret;
	size_t source_size;
	char *source_str;

	if (!core)	
		return (-1);
	if ((source_str = read_file(file_name, &source_size)))
		return (-2);

	ret = clGetPlatformIDs(1, &(core->platform_id), &(ret_num_platforms));
	ret = clGetDeviceIDs(core->platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &(core->device_id), &ret_num_devices);
	core->context = clCreateContext(NULL, 1, &(core->device_id), NULL, NULL, &ret);
	core->program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);
	ret = clBuildProgram(ocl->program, 1, &(core->device_id), NULL, NULL, NULL);
	return (0);	
}

/*
int	init_ocl_ker();
int	init_ocl_ker_mem();
int	init_ocl_ker_arg();
*/

//	pour l'instant je peu faire un truc un peu monolitique pour la partie kernel et tout
//	apres on vera pour faire un archi supercool toutca toutca

int	init_ocl_ker(t_ocl_core *core, t_ocl_ker *ker, const char *kernel_name)
{	
	cl_int ret;

	if (!core || !ker)
		return (-1);

	// Create Command Queue 
	ker->command_queue = clCreateCommandQueue(core->context, core->device_id, 0, &ret);
	// Create OpenCL Kernel 
	kernel = clCreateKernel(program, "vecAdd", &ret);

	return (0);
}

int	init_ocl_ker_mem()
{
	cl_int ret;

	// Create memory buffer
	memobj = clCreateBuffer(context, CL_MEM_READ_WRITE, MEM_SIZE * sizeof(float), NULL, &ret);
}



int	init_ocl_ker_arg()
{
	cl_int ret;

	// Set OpenCL kernel argument 
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);
}

//	on va faire une fonction generique pour initialiser la base d'un kernel
int	init_ker(t_ocl_core *core, t_ocl_ker *ker, const char *kernel_name)
{
	cl_int ret;

	if (!core || !ker)
		return (-1);

	// Create Command Queue 
	ker->command_queue = clCreateCommandQueue(core->context, core->device_id, 0, &ret);
	// Create OpenCL Kernel 
	ker->kernel = clCreateKernel(core->program, kernel_name, &ret);
	return (0);
}

//	pour allouer la memoir sur le gpu et tout ca onva fairedes fonction specifique

int init_opencl(const char *file_name)
{	
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_context context = NULL;
	cl_program program = NULL;

	cl_kernel kernel = NULL;
	cl_command_queue command_queue = NULL;
	cl_mem memobj = NULL;

	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret;

	float mem[MEM_SIZE]; // le buffer qu'on ecrit sur le truc d'opencl via l'api pour les kernel

	size_t source_size;
	char *source_str;
	cl_int i;

	// ouverture + lecure + recuperation du fichier opencl + recuperation de la taille du fichier
	if ((source_str = read_file(file_name, &source_size)))
		return (-1);

	// Get platform/device information 
	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
	// Create OpenCL Context 
	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	// Create Kernel program from the read in source 
	program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);
	// Build Kernel Program 
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);


	// Create Command Queue 
	command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
	// Create memory buffer
	memobj = clCreateBuffer(context, CL_MEM_READ_WRITE, MEM_SIZE * sizeof(float), NULL, &ret);
	// Create OpenCL Kernel 
	kernel = clCreateKernel(program, "vecAdd", &ret);
	// Set OpenCL kernel argument 
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);

	// Transfer data to memory buffer 
	ret = clEnqueueWriteBuffer(command_queue, memobj, CL_TRUE, 0, MEM_SIZE * sizeof(float), mem, 0, NULL, NULL);


	size_t global_work_size[3] = {MEM_SIZE, 0, 0};
	size_t local_work_size[3] = {MEM_SIZE, 0, 0};

	// Execute OpenCL kernel 
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, global_work_size, local_work_size, 0, NULL, NULL);

	// Transfer result from the memory buffer 
	ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0, MEM_SIZE * sizeof(float), mem, 0, NULL, NULL);

	// Display result 
	for (i=0; i < MEM_SIZE; i++) {

	}

	// Finalization 
	ret = clFlush(command_queue);
	ret = clFinish(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(memobj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);

	free(source_str);

	return 0;
}

/*
 *	Il faut determiner des structure de variable pour facilement nitialiser les bail
 *	des fonction qui ne font qu'une seul tache
 * */
