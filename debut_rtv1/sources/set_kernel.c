/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_kernel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 03:58:11 by fjanoty           #+#    #+#             */
/*   Updated: 2017/01/05 10:08:32 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	Ici on va juste set les kernel
**	-on lit le fichier
**	-on on re cree program
**	-on re cree les kernel
**	-on definie les buffeur en argument
**	-on reset les comandequeu
*/


/*
**	char		*read_file(char *name);
*/

typedef	struct		s_kp_init
{
	char			*ker_names[NB_KERNEL];
	int				ker_nb;
	char			*src_name;
	char			*file_str;
	size_t			source_size;
	cl_program		program;				// on le construit
	cl_kernel		kernel[NB_KERNEL]		// on le reconstruit pendant
	cl_context		context;				// on le defini avant mais on peu aussi le reconstruire
	cl_device_id	device_id				// on le defii AVANT mais on peu aussi le reconstruire
}					t_kp_init;

int	set_context_device_id(t_kp_init *param, cl_context context, cl_device_id device_id)
{
	param->context = context;
	param->device_id = device_id;
}

//	on initialise les nom de kernel
int	set_ker_names(t_kp_init *param, char **ker_names)
{
	int	i;

	i = 0;
	while (i < NB_KERNEL && ker_names[i])
	{
		param->ker_names[i] = ker_names[i];
		i++;
	}
	param->nb_kernel = i;
	return (1);
}

int	init_param(t_kp_init *param, cl_context context, char *src_name, char **ker_names)
{
	if (!param || !src_name, || !ker_names, || !*ker_names)
		return (0);
	param->context = context;
	param->src_name = src_name;
	set_ker_names(param, ker_names);
	if (!(param->source_str = read_file(src_name, &(param->source_size))))
		return (0);;
	return (1);
}



int	set_program(t_kp_init *param)
{
	cl_int	ret[2];

	param->program = clCreateProgramWithSource(param->context, 1, (const char **)&param.source_str, (const size_t *)&param.source_size, ret);	
	(ret[0] < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	ret[1] = clBuildProgram(program, 1, &info->device_id, NULL, NULL, NULL);
	(ret[1] < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	return (1);
}

int	set_kernels(t_kp_init *param)
{
	int		i;
	cl_int	ret[2];

	if (!param || !param->name_file || !param->names_kernel
			|| !(*(param->names_kernel)) || (param->nb_kernel <= 0))
		return (0);
	i = 0;
	while (i < NB_KERNE L&& i < param->ker_nb && param->ker_names[i])
	{
		param->kernel[i] = clCreateKernel(param->program, param->names_kernel[i], ret);
		(ret[0] < 0) ? print_ocl_error(ret[0], __LINE__ - 1, __FILE__) : 0;
		ret[1] = clBuildProgram(param->program, 1, &(param->device_id), NULL, NULL, NULL);
		(ret[1] < 0) ? print_ocl_error(ret[1], __LINE__ - 1, __FILE__) : 0;
		if (ret[0] < 0 || ret[1] < 0)
			return (0);
		i++;
	}
	return (1);
}

int	cleanning_refres_ocl(t_kp_init *param, int ret_refresh[2], t_ocl *ocl)
{
	int	i;
	cl_int	ret_ocl;

	if (param->source_str)
		free(param->source_str);
	param->source_str = NULL;
	if (!(ret[0] && ret[1]))	
		return (ft_putstr("error on refresh opencl sources\n") * 0);
	if ((ret_ocl = clReleaseProgram(ocl->program)))
		return (print_ocl_error(ret_ocl, __LINE__ - 1, __FILE__) * 0);
	i = 0;
	while (i < NB_KERNEL && i < param->ker_nb)
	{
		if ((ret_ocl = clReleaseKernel((ocl->kernel)[i])) < 0)
			return (print_ocl_error(ret_ocl, __LINE__ - 1, __FILE__) * 0);
		i++;
	}
	return (1);
}

int	copy_new_prog_ker(t_kp_init *param, t_ocl *ocl)
{
	int	i;

	ocl->program = param->program;
	i = 0;
	while (i < NB_KERNEL && i < param->ker_nb)
	{
		ocl->kernel[i] = param->kernel[i];
		i++;
	}
	return (1);
}

int	set_kernel_arg(t_ocl *ocl, t_kp_init *param)
{

}

int	refresh_ocl_source(t_kp_init *param, t_ocl *ocl)
{
	int		i;
	int		ret[2];

	if (!(param->source_str = read_file(src_name, &(param->source_size))))
		return (0);;
	ret[0] = set_program(param);
	ret[1] = set_kernels(param);
	if (!(cleanning_refres_ocl(param, ret, ocl)))
		return (0);
	copy_new_prog_ker(param, ocl);
	return (1);
}


/*
**	donc la ce qui rest a faire:
**	(A)	initialiser les patametre de ocl pour ajouter les info qui nous manque.
**	(b)	regardder vriament en fait si on a besoin de ocl
**	(C)	finir de bien initialiser la structure
**	(D)	avoir une fonction qui englobe toutes les fonctionalie
**	(E)	faire la copie des nouveau parametre
**	(F)	reflechir un peu sur la manire de faire remonter les bug (ou pas)
**	(G)	regarder comment le truc peu etre integre au projet
**	(H)	regarder si on ne peu pas commencer a faire des test unitaire
*/

/*		==> (B) <==
**	En fait la structur ocl il faut la garder.
**	La structur t_kp_init sert a reinitialiser les kernel.
**	[t_kp_init]	stoque les parametre d'initialisation
**				des sources et des kernel voir meme de llinitislisation des argument
**
*/



/*
**	On assemble tout les parmetre pour cree un nouveau PROGRAM et des nouveau KERNEL
**	on fait aussi la fonction pour les detruire, ou on ne fonction que par copy.
**	l'aventage des pointeur c'est que l'objet de retour transporte en l'ui l'information
**	du bon deroulement de l'iformation. On pourrai aussi dire que l'a notion de pointeur n'est
**	qu'une notion d'index. c'est a dire que on pourais un peu reconstruire la notion de pointeur juste
**	en manipulant des index. Ca serra probablement complex de reproduire le fonctionement des pointeur sur fonction
**	En tout cas il faudrait represente un genre d'arbre des relation pour un peu joue avec sertain mecanime
**	pour changer certaine maniere d'execution mais en ayant un peu optimiser le fonctionement.
*/

/* on a bedoin de   */
t_kernel_param	*get_source_info()
{
}

int				destroy_source_info()
{


}

{
	char		(*names_kernel)[NB_KERNEL];
	int			nb_kernel;
	char		*name_file;
	char		*source_file;
	cl_context	context;
}

int	reset_ocl_source(t_init_ocl_param *info, t_ocl *ocl)
{
	cl_program		new_program;
	cl_kernel		new_kernel[NB_KERNEL];
	cl_int			ret[2];
	t_kernel_param param;

	if (!info || !ocl)
		return (-2);
	ft_bzero(new_kernel, sizeof(new_kernel));
	if (!(param.source_str = read_file(name_file, &param.source_size)))
		return (-1);
	program = clCreateProgramWithSource(ocl->context, 1, (const char **)&param.source_str, (const size_t *)&param.source_size, ret);	
//	(ret[0] < 0) ? print_ocl_error(ret, __LINE__ - 1, __FILE__) : 0;
	ret[1] = clBuildProgram(program, 1, &info->device_id, NULL, NULL, NULL);
//	(ret[1] < 0) ? print_ocl_error(ret + 1, __LINE__ - 1, __FILE__) : 0;
	if (set_kernels(ocl, &param, new_kernel) && ret[0] >= 0 && ret[1] >= 0)
	{
		ocl->kernel = kernel;
		ft_memmove(ocl->kernel, new_kernel, sizeof(new_kernel));
		return (1);
	}
	else
		return (-1);
}

//	On doit changer le programme et les kernel
