/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rtv1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 07:46:21 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/19 22:26:10 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	On va juste alouer le memoir pour opencl. On ne fait ca qu'une fois au debut.
**		EN FAIT: ici on avait le genre de buffer qui etait alouer en mode tableau
*/

int	init_param_buffer(t_param_buffer *param, t_ocl *ocl)
{
	cl_int		ret;


	//OLD_PART
	param->ocl_type = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE, sizeof(param->all_type), NULL, &ret);
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	param->ocl_collor = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE, sizeof(param->all_collor), NULL, &ret);
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	param->ocl_coef = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE, sizeof(param->all_coef), NULL, &ret);
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	param->ocl_pos = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE, sizeof(param->all_pos), NULL, &ret);
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	param->ocl_mat_rot = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE, sizeof(param->all_mat_rot), NULL, &ret);
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	param->ocl_angle = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE, sizeof(param->all_angle), NULL, &ret);   
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	param->ocl_normal = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE, sizeof(param->all_pos), NULL, &ret);   
		(ret < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;

	return (0);
}

/*
**	La on va definir les truc de depart (position camera etc)
**	genre on va dire que c'est l'initialisation
*/

int	set_param_buffer(t_param_buffer *param)
{
	float	pos[4];
	float	dir[4];

	ft_bzero(pos, sizeof(pos));
	ft_bzero(pos, sizeof(dir));

	pos[1] = -3;
	pos[2] = 3;
	add_light(param, pos, 0xffffff);
	pos[1] = 1;
	pos[0] = 1;
	pos[2] = 0;
	add_sphere(param, pos, 0xffffff, 1);
	ft_bzero(pos, sizeof(pos));
	return (0);
}

/*
**	La c'est juste un truc pour syncroniser le data
*/

int	push_param_buffer(t_param_buffer *param, t_ocl *ocl)
{
	(void)param;
	(void)ocl;
	//	la le but ca va etre d'ecrire tout les param avec opencl
	return (0);
}

/*
**	fonction pour libere la memoir d'opencl
*/
int	destroy_param_buffer()
{
	return (0);
}


int	run_rtv1()
{
	t_env	e;


	// initialisation de la mlx
	if (!(e.mlx = mlx_init()))
		return (-1);
	// initialisation de mon micro module de fenetre
	if (!(e.win_rt = window_init(&e, SIZE_X, SIZE_Y, "rtv1")))
		return (-2);
	//*	initialisation des:
	//	recuperation des source opencl
	//	allocation de la structure qui garde un peu les info des opoiteur tout ca
	//	recuperation de info sur le materiel (cg, cpu etc..)
	//	initialisation des commande_queu (pour les kjernel apres)
	//	compilation des sources au runtime en fonciton du materiel
	//	creation des kernel aves les source compiler + (il sont cree mais pas associer a des comandeque ni des argument ni rien, les buffer on pas ete alouer)
	//		|
	//		|
	//*/	v
	if (!(e.ocl = init_kernel(SIZE_X, SIZE_Y, "src_cl/data_parallel.cl"))
		|| !(e.mem_ocl = init_mem_ocl(e.win_rt, e.ocl)))
		return (-3);

	//	la on va finir l'initialisation d'opencl
	init_param_buffer(&(e.win_rt->param), e.ocl);
	mlx_loop_hook(e.mlx, main_bcl, &e);
	mlx_loop(e.mlx);
//	mlx_do_sync(e.mlx);
	return (0);
}


int	main_bcl(t_env *e)
{


	main_while_ocl(e->mem_ocl, e->ocl, e->win_rt);
//	init_opencl(e, SIZE_X, SIZE_Y);
	return (0);
}
