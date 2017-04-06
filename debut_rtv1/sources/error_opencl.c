/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_opencl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 01:24:46 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/06 10:42:42 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_ocl_error()
{
	ft_bzero(g_ocl_error, sizeof(g_ocl_error));
	g_ocl_error[0]	= "CL_SUCCESS";
	g_ocl_error[1]	= "CL_DEVICE_NOT_FOUND";
	g_ocl_error[2]	= "CL_DEVICE_NOT_AVAILABLE";
	g_ocl_error[3]	= "CL_COMPILER_NOT_AVAILABLE";
	g_ocl_error[4]	= "CL_MEM_OBJECT_ALLOCATION_FAILURE";
	g_ocl_error[5]	= "CL_OUT_OF_RESOURCES";
	g_ocl_error[6]	= "CL_OUT_OF_HOST_MEMORY";
	g_ocl_error[7]	= "CL_PROFILING_INFO_NOT_AVAILABLE";
	g_ocl_error[8]	= "CL_MEM_COPY_OVERLAP";
	g_ocl_error[9]	= "CL_IMAGE_FORMAT_MISMATCH";
	g_ocl_error[10]	= "CL_IMAGE_FORMAT_NOT_SUPPORTED";
	g_ocl_error[11]	= "CL_BUILD_PROGRAM_FAILURE";
	g_ocl_error[12]	= "CL_MAP_FAILURE";
	g_ocl_error[30]	= "CL_INVALID_VALUE";
	g_ocl_error[31]	= "CL_INVALID_DEVICE_TYPE";
	g_ocl_error[32]	= "CL_INVALID_PLATFORM";
	g_ocl_error[33]	= "CL_INVALID_DEVICE";
	g_ocl_error[34]	= "CL_INVALID_CONTEXT";
	g_ocl_error[35]	= "CL_INVALID_QUEUE_PROPERTIES";
	g_ocl_error[36]	= "CL_INVALID_COMMAND_QUEUE";
	g_ocl_error[37]	= "CL_INVALID_HOST_PTR";
	g_ocl_error[38]	= "CL_INVALID_MEM_OBJECT";
	g_ocl_error[39]	= "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
	g_ocl_error[40]	= "CL_INVALID_IMAGE_SIZE";
	g_ocl_error[41]	= "CL_INVALID_SAMPLER";
	g_ocl_error[42]	= "CL_INVALID_BINARY";
	g_ocl_error[43]	= "CL_INVALID_BUILD_OPTIONS";
	g_ocl_error[44]	= "CL_INVALID_PROGRAM";
	g_ocl_error[45]	= "CL_INVALID_PROGRAM_EXECUTABLE";
	g_ocl_error[46]	= "CL_INVALID_KERNEL_NAME";
	g_ocl_error[47]	= "CL_INVALID_KERNEL_DEFINITION";
	g_ocl_error[48]	= "CL_INVALID_KERNEL";
	g_ocl_error[49]	= "CL_INVALID_ARG_INDEX";
	g_ocl_error[50]	= "CL_INVALID_ARG_VALUE";
	g_ocl_error[51]	= "CL_INVALID_ARG_SIZE";
	g_ocl_error[52]	= "CL_INVALID_KERNEL_ARGS";
	g_ocl_error[53]	= "CL_INVALID_WORK_DIMENSION";
	g_ocl_error[54]	= "CL_INVALID_WORK_GROUP_SIZE";
	g_ocl_error[55]	= "CL_INVALID_WORK_ITEM_SIZE";
	g_ocl_error[56]	= "CL_INVALID_GLOBAL_OFFSET";
	g_ocl_error[57]	= "CL_INVALID_EVENT_WAIT_LIST";
	g_ocl_error[58]	= "CL_INVALID_EVENT";
	g_ocl_error[59]	= "CL_INVALID_OPERATION";
	g_ocl_error[60]	= "CL_INVALID_GL_OBJECT";
	g_ocl_error[61]	= "CL_INVALID_BUFFER_SIZE";
	g_ocl_error[62]	= "CL_INVALID_MIP_LEVEL";
	g_ocl_error[63]	= "CL_INVALID_GLOBAL_WORK_SIZE";
}

int		print_ocl_error(int err_cl, int nbl, char *name)
{
	ft_putstr("file:");
	ft_putstr(name);
	ft_putstr("	line:");
	ft_putnbr(nbl);
	ft_putstr("		*** ");
	if (err_cl > 0)
	{
		ft_putstr("not a cl error ***\n");
		exit(1);
		return (1);
	}
	err_cl *= -1;
	if ((err_cl > 12 && err_cl < 30) || err_cl > 63)
	{
		ft_putstr("invalid cl error ***\n");
		exit(1);
	}
	else if (g_ocl_error[err_cl])
	{
		ft_putstr(g_ocl_error[err_cl]);
		ft_putstr(" ***\n");
		exit(1);
	}
		exit(1);
	return (1);
}

/*
void	print_ocl_error(int err_cl, int nbl, char *name)
{
	printf("line:%d	on file:%s", nbl, name);
	print_ocl_error(err_cl);
}
*/
