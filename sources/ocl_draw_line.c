/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 19:58:57 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/13 22:47:05 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 *	Comment on connais la taille des baille
 *		-buff_img:	on la donne en paramete
 *		-le buffer des point... il faudrait avoir un truc qui gere la couleur
 *			on peu en faire un kernel...
 * */

int	ocl_mcreat_draw_line(t_ocl_core *core, t_ocl_ker *ifs_ker, size_t img_size, size_t nb_line, cl_mem pt_buff)
{
	cl_int	ret[3];

	ifs_ker->nb_arg = 3;
	ret[0] = ocl_create_mem(ifs_ker, 0, CL_MEM_READ_WRITE, img_size);
	ret[1] = ocl_init_mem(ifs_ker, 1, CL_MEM_READ_WRITE, sizeof(int), );
	ret[2] = ocl_create_mem(ifs_ker, 2, CL_MEM_READ_ONLY, sizeof(int));
	branch_arg_to_kernel(ifs_ker, 3);
	return (check_ocl_err(ret, 3, __func__, __FILE__));
	// les truc
}

//	normalement on a rien a lui envoyer... a part peut etre les dimention de l'ecran

int	ocl_write_to_draw_line()
{
	//	voila voila pas grand chose a faire ou peuetre une seul fois
}

//	on recupere les baille et on traite la data
int	ocl_read_from_draw_line()
{

}

//	c'est la fonction qu'on a besoin d'appeler
int	ocl_run_draw_line()
{

}
