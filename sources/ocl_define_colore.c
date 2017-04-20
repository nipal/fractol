/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_define_colore.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 22:38:20 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/20 07:39:20 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

typedef	struct	s_ifs_param
{
	char	len_base;
	char	len_trans;
	char	max_iter;
	char	max_pt;
}				t_ifs_param;

int		ocl_mem_creat_define_color(t_ocl_ker *def_col  size_t size_colore)
{
	cl_int	ret[2];

	def_col->nb_arg = 2;
	ret[0] = ocl_create_mem(def_col, 0, CL_MEM_READ_WRITE, size_colore);
	ret[1] = ocl_create_mem(def_col, 1, CL_MEM_READ_WRITE, sizeof(t_ifs_param));
	branch_arg_to_kernel(def_col, 2);
	return (check_ocl_err(ret, 2, __func__, __FILE__));
}

int	ocl_write_to_define_color()
{
	cl_int	ret;
	//	voila voila pas grand chose a faire ou peuetre une seul fois
	// dans l'hyposthese ou on cacule et on trace les ligne en plusieur fois, lail faudrait... non
	ret = clEnqueueWriteBuffer(command_queue, memobj, CL_TRUE, 0, MEM_SIZE * sizeof(float), mem, 0, NULL, NULL);
	return (check_ocl_err(&re, 1, __func__, __FILE__));
}

//	on recupere les baille et on traite la data
int	ocl_read_from_draw_line(t_win *w, t_ocl_ker *ker, size_t img_size)
{
	cl_int	ret;

	ret = clEnqueueReadBuffer(ker->command_queue, ker->data[e_img].gpu_buff, CL_TRUE, 0, img_size, w->data, 0, NULL, NULL);
	actu_win(w);
	return (check_ocl_err(&ret, 1, __func__, __FILE__));
}

//	c'est la fonction qu'on a besoin d'appeler
int	ocl_run_draw_line()
{
		
	return (0);
}
