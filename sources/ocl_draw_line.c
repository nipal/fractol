/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 19:58:57 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/23 07:31:59 by fjanoty          ###   ########.fr       */
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

int	ocl_mem_creat_draw_line(t_ocl_ker *ifs_ker, size_t img_size, t_ocl_mem *buff_pt, t_ocl_mem *buff_col, t_ocl_mem *ifs_spec)
{
	cl_int	ret[1];

	ifs_ker->nb_arg = 4;
	ret[0] = ocl_create_mem(ifs_ker, 0, CL_MEM_READ_WRITE, img_size);
	memmove(ifs_ker->data + 1, buff_pt, sizeof(t_ocl_mem));
	memmove(ifs_ker->data + 2, buff_col, sizeof(t_ocl_mem));
	memmove(ifs_ker->data + 3, ifs_spec, sizeof(t_ocl_mem));
//	ret[1] = ocl_create_mem(ifs_ker, 3, CL_MEM_READ_ONLY, sizeof(float) * 2);
	branch_arg_to_kernel(ifs_ker, 4);
	return (check_ocl_err(ret, 1, __func__, __FILE__));
}

//	normalement on a rien a lui envoyer... a part peut etre les dimention de l'ecran

int	ocl_write_to_draw_line()
{
	//	voila voila pas grand chose a faire ou peuetre une seul fois
	// dans l'hyposthese ou on cacule et on trace les ligne en plusieur fois, lail faudrait... non

	return (0);
}

int	print_img_not_null(t_win *w)
{
	int	i;
	int	max;

	i = 0;
	max = w->size_x * w->size_y;
	return (max);
}

//	on recupere les baille et on traite la data
int	ocl_read_from_draw_line(t_win *w, t_ocl_ker *ker)
{
	size_t img_size;
	cl_int	ret;

	img_size = w->size_x * w->size_y * sizeof(int);
	ret = clEnqueueReadBuffer(ker->command_queue, ker->data[e_dl_img].gpu_buff, CL_TRUE, 0, img_size, w->data, 0, NULL, NULL);
	actu_win_rest(w);
	// ATENTION C'est TRES TRES SALE ce qui suit
	ret = clEnqueueWriteBuffer(ker->command_queue, ker->data[e_dl_img].gpu_buff, CL_TRUE, 0, img_size, w->data, 0, NULL, NULL);
	
	return (check_ocl_err(&ret, 1, __func__, __FILE__));
}

//	c'est la fonction qu'on a besoin d'appeler
int	ocl_run_draw_line(t_ocl_ker *dl, int *id_tab, int max_iter)
{
	size_t		global_work_size[3] = {1, 0, 0};
	size_t		local_work_size[3] = {1, 0, 0};
	cl_int	ret[1];

	global_work_size[0] = id_tab[max_iter] - id_tab[max_iter - 1];
//	printf("nb_pt:%zu\n", global_work_size[0]);
	ret[0] = clEnqueueNDRangeKernel(dl->command_queue, dl->kernel, 1, NULL, global_work_size, local_work_size, 0, NULL, NULL);

	return (check_ocl_err(ret, 1, __func__, __FILE__));
}
