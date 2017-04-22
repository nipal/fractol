/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_define_colore.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 22:38:20 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/22 03:44:11 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
typedef	struct	s_ifs_spec
{
	char	len_base;
	char	len_trans;
	char	max_iter;
	char	max_pt;
	int		dim_ecr[2];
}				t_ifs_spec;
*/

int		ocl_mem_creat_define_color(t_ocl_ker *def_col, size_t size_colore)
{
	cl_int	ret[2];

	def_col->nb_arg = 2;
	ret[0] = ocl_create_mem(def_col, 0, CL_MEM_READ_WRITE, size_colore);
	ret[1] = ocl_create_mem(def_col, 1, CL_MEM_READ_WRITE, sizeof(t_ifs_param));
	branch_arg_to_kernel(def_col, 2);
	return (check_ocl_err(ret, 2, __func__, __FILE__));
}


//	on recupere les baille et on traite la data
int	ocl_read_from_define_colore(t_win *w, t_ocl_ker *ker)
{
	cl_int	ret;

	ret = clEnqueueReadBuffer(ker->command_queue, ker->data[e_dl_img].gpu_buff, CL_TRUE, 0, ker->data[e_dl_img].size, w->data, 0, NULL, NULL);
	actu_win(w);
	return (check_ocl_err(&ret, 1, __func__, __FILE__));
}

//	c'est la fonction qu'on a besoin d'appeler
int	ocl_run_define_colore(t_env *e, t_ocl_ker *def_col)
{
	int			id_tab[MAX_ITER];
	size_t		global_work_size[3] = {1, 0, 0};
	size_t		local_work_size[3] = {1, 0, 0};
	size_t		offset_pt;
	t_ifs_spec	spec;
	cl_int		ret;
	(void)def_col;


	spec.len_base = get_polygone_len(e->base);
	spec.len_trans = get_polygone_len(e->transform);
	spec.max_iter = e->max_iter;
	spec.max_pt = id_tab[e->max_iter] - id_tab[e->max_iter - 1]; 
	set_id_isf_ptbuff(data.base_len, e->trans_len, e->max_iter, id_tab);
	 	ret = clEnqueueWriteBuffer(ifs_cl->command_queue, ifs_cl->data[4].gpu_buff, CL_TRUE, 0, ifs_cl->data[4].size, &(i), 0, NULL, NULL);

	if ((ret = clEnqueueNDRangeKernel(ifs_cl->command_queue, def_col->kernel, 1, NULL, global_work_size, local_work_size, 0, NULL, NULL)))
	{
		printf("ohh trop triste!\n");
		exit(0);
	}
	return (0);
}
