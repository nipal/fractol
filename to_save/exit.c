/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 12:17:52 by fjanoty           #+#    #+#             */
/*   Updated: 2017/06/16 18:19:22 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fractol.h"

void	free_img(int ***img, int size_y)
{
	int	j;

	if (!img || !img[0] || !img[0][0])
		return ;
	j = 0;
	while (j < size_y)
	{
		if (img[j])
		{
			free(img[0][j]);
			img[0] = NULL;
		}
		j++;
	}
	if (img[0])
	{
		free(img[0]);
		img[0] = NULL;
	}
}

int		free_slider(t_slider ***tabs)
{
	int	i;

	i = 0;
	while (tabs[0][i])
	{
		matrix_free(&(tabs[0][i]->color));
		free(tabs[0][i]->border);
		free(tabs[0][i]);
		tabs[0][i] = NULL;
		i++;
	}
	free(*tabs);
	*tabs = NULL;
	return (1);
}

/*
//	___Finalization__

`	ret = clFlush(command_queue);	
	ret = clFinish(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(Amobj);
	ret = clReleaseMemObject(Bmobj);
	ret = clReleaseMemObject(Cmobj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
*/

/*
**	on veut liberer tout plein de truc:
**		-le cl_program
**		-les cl_mem
*/

// 


int	ok_to_realease(cl_mem buff)
{
	static	int		k_mem = 0;
	static	int		first = 1;
	static	ulong	allreadty_rm[ARG_KER_MAX * NB_KER];
	int	i;

	if (first)
	{
		first = 0;
		bzero(allreadty_rm, sizeof(allreadty_rm));
	}
	if (!((ulong)buff))
		return (0);
	i = 0;
	while (i < k_mem)
	{
		if ((ulong)buff == allreadty_rm[i])
			return (0);
		i++;
	}
	allreadty_rm[k_mem] = (ulong)buff;
	k_mem++;
	return (1);
}

//	NB_KER
void	ocl_exit(t_ocl_core *core, t_ocl_ker *ker, int nb_ker, int nb_mem)
{
	cl_int	ret;
	int		i;
	int		j;


	i = 0;
	while (i < nb_ker)
	{
		if (ker[i].kernel)
		{
			ret = clFlush(ker[i].command_queue);	
			ret = clFinish(ker[i].command_queue);
			ret = clReleaseKernel(ker[i].kernel);
			j = 0;
			while (j < nb_mem)
			{
				if (ok_to_realease(ker[i].data[j].gpu_buff))
					ret = clReleaseMemObject(ker[i].data[j].gpu_buff);
				j++;
			}
			ret = clReleaseCommandQueue(ker[i].command_queue);
		}
		i++;
	}
	ret = clReleaseContext(core->context);
	ret = clReleaseProgram(core->program);
}

int		ft_exit(t_env *e)
{
//	static	int first_time = 1;
	
//	if (!first_time)
//		exit(0) ;
//	first_time = 0;
//	polygone_destroy(&(e->base));
//	polygone_destroy(&(e->transform));
//	polygone_destroy(&(e->beg_actif));
//	polygone_destroy(&(e->actif));
//	matrix_free(&(e->prev_mouse));
//	matrix_free(&(e->mouse));
	free(e->z_buffer);
	ocl_exit(&(e->ocl), e->ker, NB_KER, ARG_KER_MAX);
	if (e->img_low)
		free(e->img_low);
	exit(0);
	return (0);
}
