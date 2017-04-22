/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 19:58:57 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/21 19:04:29 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 *	Comment on connais la taille des baille
 *		-buff_img:	on la donne en paramete
 *		-le buffer des point... il faudrait avoir un truc qui gere la couleur
 *			on peu en faire un kernel...
 * */

//	on pourrai faire un truc pour copier un truc de que voila
//	pck on ne se ferri pas chier du coup

int	ocl_mem_creat_draw_line(t_ocl_ker *ifs_ker, size_t img_size, t_ocl_mem *buff_pt, t_ocl_mem *buff_col)
{
	cl_int	ret[2];

	ifs_ker->nb_arg = 4;
	ret[0] = ocl_create_mem(ifs_ker, 0, CL_MEM_READ_WRITE, img_size);
	memmove(ifs_ker->data + 1, buff_pt, sizeof(t_ocl_mem));
	memmove(ifs_ker->data + 2, buff_col, sizeof(t_ocl_mem));
	ret[1] = ocl_create_mem(ifs_ker, 3, CL_MEM_READ_ONLY, sizeof(float) * 2);
	branch_arg_to_kernel(ifs_ker, 4);
	return (check_ocl_err(ret, 2, __func__, __FILE__));
}

//	normalement on a rien a lui envoyer... a part peut etre les dimention de l'ecran

int	ocl_write_to_draw_line()
{
	//	voila voila pas grand chose a faire ou peuetre une seul fois
	// dans l'hyposthese ou on cacule et on trace les ligne en plusieur fois, lail faudrait... non
	return (0);
}

//	on recupere les baille et on traite la data
int	ocl_read_from_draw_line(t_win *w, t_ocl_ker *ker, size_t img_size)
{
	cl_int	ret;

	ret = clEnqueueReadBuffer(ker->command_queue, ker->data[e_dl_img].gpu_buff, CL_TRUE, 0, img_size, w->data, 0, NULL, NULL);
	actu_win(w);
	return (check_ocl_err(&ret, 1, __func__, __FILE__));
}

//	c'est la fonction qu'on a besoin d'appeler
int	ocl_run_draw_line()
{

	return (0);
}
