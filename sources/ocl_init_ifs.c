/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_init_ifs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 05:18:36 by fjanoty           #+#    #+#             */
/*   Updated: 2017/06/16 00:21:17 by fjanoty          ###   ########.fr       */
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
	ocl_mem_creat_define_color(&(e->ker[e_define_color]), size_colore);
	ocl_mem_creat_draw_line(&(e->ker[e_draw_line]), size_img,
					&(e->ker[e_ifs_calcul_pt].data[e_cip_pt_ifs]),
					&(e->ker[e_define_color].data[e_dc_col]),
					&(e->ker[e_define_color].data[e_dc_param]));
	return (0);
}

//	on va faire du sale ==> on doit l'appeler avec le kernel dc pck je suis mauvais...
int	ocl_ifs_push_spec(t_win *w, t_data_nw *data, t_ocl_ker *ker_dc)
{
	cl_int		ret;
	t_ifs_spec	param;

	param.len_base = data->base_len;
	param.len_trans = data->trans_len;
	param.max_iter = data->max_iter;
	param.max_pt = data->base_len * pow(data->trans_len, data->max_iter);
	param.ecr_x = w->size_x;
	param.ecr_y = w->size_y;
	ret = clEnqueueWriteBuffer(ker_dc->command_queue, ker_dc->data[e_dc_param].gpu_buff,
			CL_TRUE, 0, sizeof(t_ifs_spec), &param, 0, NULL, NULL);
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
	float		col[6] = {e->sliders[0]->v1, e->sliders[0]->v2,
						e->sliders[1]->v1, e->sliders[1]->v2,
						e->sliders[2]->v1, e->sliders[2]->v2};

	ocl_run_define_colore(e, &(e->ker[e_define_color]), id_tab);
	ocl_ifs_calcul_run(&(e->ker[e_ifs_calcul_pt]), e->transform, e->base, e->max_iter, col);
	ocl_run_draw_line(&(e->ker[e_draw_line]), id_tab, e->max_iter);

	ocl_read_from_draw_line(e->fractal, &(e->ker[e_draw_line]));
	return (0);
}
