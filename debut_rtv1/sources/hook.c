/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 05:46:36 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/06 11:15:50 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


int	init_obj(t_param_buffer *param)
{
	int	i;

	(void)param;
	i = 0;
	while (i < NB_OBJ)
	{
//		param[i] = {0, 10*i, 100*i, 1000*i, {i / 10, i 10 * i}, -i, 
//		{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}};
		/*
		all_obj[i].id = i;
		all_obj[i].color = 10 * i;
		all_obj[i].type = 100 * i;
		all_obj[i].coef = 1000 * i;
		all_obj[i].position = {};
		all_obj[i].angle = src.angle;
		all_obj[i].mat_rot = src.mat_rot;
	*/
		i++;
	}
	return (0);
}

t_mem_ocl	*init_mem_ocl(t_win *w, t_ocl *ocl)
{
	t_mem_ocl	*mem;
	cl_int		ret;
	int			size;

	if (!(mem = (t_mem_ocl*)ft_memalloc(sizeof(t_mem_ocl))))
		return (NULL);
	size = w->size_x * w->size_y;
	mem->img_data = (int*)w->data;
	mem->ocl_time = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE, sizeof(int), NULL, &ret);
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;

//	la c'est le buffer de l'image
	mem->ocl_data = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE, size * sizeof(int), NULL, &ret);
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	mem->ocl_ray_dir = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE, size * 4 * sizeof(float), NULL, &ret);
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	mem->ocl_cam = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE, 4 * 4 * sizeof(float), NULL, &ret);
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	mem->ray_dir = malloc(sizeof(float) * 4 * w->size_x * w->size_y);
		
	// La on set aussi les valeur des vecteur de la camera
	mem->cam[0 * 4 + 0] = 0;
	mem->cam[0 * 4 + 1] = 0;
	mem->cam[0 * 4 + 2] = 0;
	mem->cam[0 * 4 + 3] = 0;

	mem->cam[1 * 4 + 0] = 1;
	mem->cam[1 * 4 + 1] = 0;
	mem->cam[1 * 4 + 2] = 0;
	mem->cam[1 * 4 + 3] = 0;

	mem->cam[2 * 4 + 0] = 0;
	mem->cam[2 * 4 + 1] = 1;
	mem->cam[2 * 4 + 2] = 0;
	mem->cam[2 * 4 + 3] = 0;

	mem->cam[3 * 4 + 0] = 0;
	mem->cam[3 * 4 + 1] = 0;
	mem->cam[3 * 4 + 2] = 1;
	mem->cam[3 * 4 + 3] = 0;

	mem->ocl_zbuffer_id = clCreateBuffer(ocl->context, CL_MEM_READ_ONLY, 2 * size * sizeof(float), NULL, &ret);

	// kernel, id_arg, size_buffer, cl_adrr
	ret = clSetKernelArg((ocl->kernel)[INIT_FRAME], 0, sizeof(cl_mem), (void *)&(mem->ocl_ray_dir));
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	ret = clSetKernelArg((ocl->kernel)[INIT_FRAME], 1, sizeof(cl_mem), (void *)&(mem->ocl_cam));
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	ret = clSetKernelArg((ocl->kernel)[INIT_FRAME], 2, sizeof(cl_mem), (void *)&(mem->ocl_zbuffer_id));
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	
	ret = clSetKernelArg((ocl->kernel)[TEST_IMAGE], 0, sizeof(cl_mem), (void *)&(mem->ocl_time));
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	ret = clSetKernelArg((ocl->kernel)[TEST_IMAGE], 1, sizeof(cl_mem), (void *)&(mem->ocl_data));
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;


		/////////////////////// oui je sais il faudra faire le menage dans tout ca
	//NEW PARRT sauf que on est pas dans la bonne structure...
	mem->ocl_obj = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE, sizeof(mem->all_obj), NULL, &ret);   
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	mem->ocl_obj_out = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE, sizeof(mem->all_obj_out), NULL, &ret);   
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	ret = clSetKernelArg((ocl->kernel)[TEST_STRUCT], 0, sizeof(cl_mem), (void *)&(mem->ocl_obj_out));
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	ret = clSetKernelArg((ocl->kernel)[TEST_STRUCT], 1, sizeof(cl_mem), (void *)&(mem->ocl_obj));
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;


//	mem->cam = malloc(100);
	return (mem);
}


void	print_test(t_mem_ocl *mem, t_win *w)
{
	int	i;
	int	j;

	j = 0;
	while (j < w->size_y)
	{
		i = 0;
		printf("[%d]	->", j);
		while (i < w->size_x)
		{
			printf("{%.2f, %.2f, %.2f} "
				, mem->ray_dir[(i + j * SIZE_X) * 4 + 0]
				, mem->ray_dir[(i + j * SIZE_X) * 4 + 1]	
				, mem->ray_dir[(i + j * SIZE_X) * 4 + 2]);
			i++;
		}
		printf("\n");
		j++;
	}
	printf("------------------------------------------------------------------------------------------\n");
}


int		main_while_ocl(t_mem_ocl *mem, t_ocl *ocl, t_win *w)
{
	static	int count = 0;
	cl_int	ret;
	size_t	global_item_size;
	size_t	local_item_size;
	int		size;
	char	tmp[1000];


	global_item_size = w->size_x * w->size_y;
	size = global_item_size;
	local_item_size = 1;
	
//		tmp[0] = '\0';
//		ft_strcat(tmp, __FILE__);
//		ft_strcat(tmp, " func:");
//		ft_strcat(tmp, __func__);
//	//		
//		set_landmark(mem->cam, w->cam_angle, w->cam_pos);
//		ret = clEnqueueWriteBuffer(ocl->command_queue[INIT_FRAME], mem->ocl_cam, CL_TRUE, 0, 4 * 4 * sizeof(float), mem->cam, 0, NULL, NULL);
//			(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, tmp) : 0;
//	//	
//	//		ret = clSetKernelArg((ocl->kernel)[INIT_FRAME], 0, sizeof(cl_mem), (void *)&(mem->ocl_ray_dir));
//	//			(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, tmp) : 0;
//	//		ret = clSetKernelArg((ocl->kernel)[INIT_FRAME], 1, sizeof(cl_mem), (void *)&(mem->ocl_cam));
//	//			(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, tmp) : 0;
//	//		ret = clSetKernelArg((ocl->kernel)[INIT_FRAME], 2, sizeof(cl_mem), (void *)&(mem->ocl_zbuffer_id));
//	//			(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, tmp) : 0;
//	//		
//		ret = clEnqueueNDRangeKernel(ocl->command_queue[INIT_FRAME], ocl->kernel[INIT_FRAME], 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
//			(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, tmp) : 0;
//		ret = clEnqueueReadBuffer(ocl->command_queue[INIT_FRAME], mem->ocl_ray_dir, CL_TRUE, 0, 4 * size * sizeof(float), mem->ray_dir, 0, NULL, NULL);
//			(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, tmp) : 0;
//	


//mlx_put_image_to_window(w->e->mlx, w->win, w->img, 0, 0);


//****************************	On fait juste la couleur bizard	 ****************************
	ret = clEnqueueWriteBuffer(ocl->command_queue[TEST_IMAGE], mem->ocl_time, CL_TRUE, 0, sizeof(int), &count, 0, NULL, NULL);
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;

	ret = clEnqueueNDRangeKernel(ocl->command_queue[TEST_IMAGE], (ocl->kernel)[TEST_IMAGE], 1, NULL,&global_item_size, &local_item_size, 0, NULL, NULL);
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	ret = clEnqueueReadBuffer(ocl->command_queue[TEST_IMAGE], mem->ocl_data, CL_TRUE, 0,size * sizeof(int), mem->img_data, 0, NULL, NULL);
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	mlx_put_image_to_window(w->e->mlx, w->win, w->img, 0, 0);
	(void)tmp;


///	print_test(mem, w);

//	ret = clFlush((ocl)->command_queue);	
//	ret = clFinish((ocl)->command_queue);
	count++;
	return (0);
}
