/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_init_ifs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 05:18:36 by fjanoty           #+#    #+#             */
/*   Updated: 2017/06/16 17:26:50 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
	La on va faire tout les baille pas generique mais qui sont globale a tous les kernel du projet
*/

int	init_ifs(t_env *e, t_win *w)
{
 	size_t	size_buff_pt;
	size_t	size_colore;
	size_t	size_img;
	size_t	nb_pt;

	nb_pt = (MAX_GPU_BUFF) / (sizeof(float) * 2);
	size_img = w->size_x * w->size_y * sizeof(int);
	size_buff_pt = MAX_GPU_BUFF;
	size_colore = MAX_GPU_BUFF;
	
	init_kernel(&(e->ocl), &(e->ker[e_ifs_calcul_pt]), "calcul_ifs_point");
	init_kernel(&(e->ocl), &(e->ker[e_define_color]), "define_color");
	init_kernel(&(e->ocl), &(e->ker[e_draw_line]), "draw_line");

	ocl_mem_creat_calcul_ifs(&(e->ker[e_ifs_calcul_pt]));
	ocl_mem_creat_define_color(&(e->ker[e_define_color]), size_colore
			, &(e->ker[e_ifs_calcul_pt].data[e_cip_param]));
	ocl_mem_creat_draw_line(&(e->ker[e_draw_line]), size_img,
					&(e->ker[e_ifs_calcul_pt].data[e_cip_pt_ifs]),
					&(e->ker[e_define_color].data[e_dc_col]),
					&(e->ker[e_define_color].data[e_dc_param]));
	return (0);
}

int	ocl_init_ifs(t_env *e)
{
	init_ocl_error();
	init_ocl_core(&(e->ocl), "src_cl/ifs_render.cl");
	init_ifs(e, e->fractal);
	return (0);
}

int	ocl_read_from_draw_line(t_win *w, t_ocl_ker *ker);

int	ocl_render_run(t_env *e)
{
	int			id_tab[MAX_ITER];
//	float		col[6] = {e->sliders[0]->v1, e->sliders[0]->v2,
//						e->sliders[1]->v1, e->sliders[1]->v2,
//						e->sliders[2]->v1, e->sliders[2]->v2};

	ocl_run_define_colore(e, &(e->ker[e_define_color]), id_tab);
	ocl_ifs_calcul_run(&(e->ker[e_ifs_calcul_pt]), e->transform, e->base, e->max_iter, NULL);
	ocl_run_draw_line(&(e->ker[e_draw_line]), id_tab, e->max_iter);

	ocl_read_from_draw_line(e->fractal, &(e->ker[e_draw_line]));
	return (0);
}

/*
	while (i < nb_iter)
	{
		global_work_size[0] = id_tab[i + 1] - id_tab[i]; // Soit calcul une id de plus; Soit avoir une varible qui stoque le resulta

		ret2 = clSetKernelArg(ifs_cl->kernel, 2, sizeof(int), &i);
		if (ret2)
			check_ocl_err(&ret2, 1, "tata yoyo", __FILE__);
		if (ret[i])
			check_ocl_err(ret, i + 1, __func__, __FILE__);
		i++;
	}


		ret[i] = clEnqueueNDRangeKernel(ifs_cl->command_queue, ifs_cl->kernel, 1, NULL, global_work_size, local_work_size, 0, NULL, NULL);
 * */
