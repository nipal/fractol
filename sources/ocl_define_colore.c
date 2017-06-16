/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_define_colore.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 22:38:20 by fjanoty           #+#    #+#             */
/*   Updated: 2017/06/16 14:22:52 by fjanoty          ###   ########.fr       */
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

int		ocl_mem_creat_define_color(t_ocl_ker *def_col, size_t size_colore, t_ocl_mem *spec)
{
	cl_int	ret[2];

	def_col->nb_arg = 2;
	ret[0] = ocl_create_mem(def_col, 0, CL_MEM_READ_WRITE, size_colore);
	memmove(def_col->data + 1, spec, sizeof(t_ocl_mem));
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

void	set_range_val(t_range *value, float beg, float end)
{
	value->beg = beg;
	value->end = end;
	value->delta = end - beg;
}

//	ici on remplis tout les champ de la structure pour envoyer
//	tout d'un coup a l'api opencl
void	set_dc_spec(t_ifs_spec *spec, t_env *e, t_win *w, int *id_tab)
{
	int			i;
	t_polygone	*node;

	node = e->transform;

	spec->pt_trans[0][0] = 0;
	spec->pt_trans[0][1] = 0;
	for (i = 1; i < MAX_NODE - 1 && node; i++)
	{
		spec->pt_trans[i][0] = node->pos->m[0];
		spec->pt_trans[i][1] = node->pos->m[1];
		node = node->next;
	}
	spec->pt_trans[i][0] = 1;
	spec->pt_trans[i][1] = 0;

	spec->len_base = get_polygone_len(e->base);
	spec->len_trans = get_polygone_len(e->transform);
	spec->max_iter = e->max_iter;
	set_id_isf_ptbuff(spec->len_base, spec->len_trans, e->max_iter, id_tab);

	spec->max_pt = id_tab[e->max_iter] - id_tab[e->max_iter - 1]; 
	spec->ecr_x = w->size_x;
	spec->ecr_y = w->size_y;
	spec->nb_iter = e->max_iter;

	set_range_val(&(spec->hue), e->sliders[0]->v1, e->sliders[0]->v2);
	set_range_val(&(spec->sat), e->sliders[1]->v1, e->sliders[1]->v2);
	set_range_val(&(spec->val), e->sliders[2]->v1, e->sliders[2]->v2);

	memmove(&(spec->beg_id), id_tab, sizeof(int) * MAX_ITER);
//	printf("spec->ecrX:%d	spec->ecrY:%d\n", spec->dim_ecr[0], spec->dim_ecr[1]);
}

int		need_col_update(t_ifs_spec *spec)
{
	static	int	first = 1;
	static	t_ifs_spec	prev_spec;
	int		ret;

	return (1);
	ret = 0;
	if (first)
	{
		first = 0;
		ret = 1;
		prev_spec = *spec;
	}
	else
	{
		if (spec->len_trans != prev_spec.len_trans
			|| spec->len_base != prev_spec.len_trans
			|| spec->max_iter != prev_spec.max_iter
			|| ft_memcmp(&spec->hue, &prev_spec.hue, sizeof(t_range))
			|| ft_memcmp(&spec->sat, &prev_spec.sat, sizeof(t_range))
			|| ft_memcmp(&spec->val, &prev_spec.val, sizeof(t_range)))
		{
			ret = 1;
			prev_spec = *spec;
		}
	}
	return (ret);
}

//	c'est la fonction qu'on a besoin d'appeler
int	ocl_run_define_colore(t_env *e, t_ocl_ker *def_col, int *id_tab)
{
//	int			id_tab[MAX_ITER];
	size_t		global_work_size[3] = {1, 0, 0};
	size_t		local_work_size[3] = {1, 0, 0};
	size_t		offset_pt;
	t_ifs_spec	spec;
	cl_int		ret[2];
	(void)def_col;


	//	on initialise les data pour le kernel 
	set_dc_spec(&spec, e, e->fractal, id_tab);
	ret[0] = clEnqueueWriteBuffer(def_col->command_queue, def_col->data[e_dc_param].gpu_buff, CL_TRUE, 0, sizeof(t_ifs_spec), &spec, 0, NULL, NULL);
	if (!need_col_update(&spec))
		return (0);
	global_work_size[0] = id_tab[e->max_iter - 1] - id_tab[e->max_iter - 2];
	//printf("define_color:%zu\n", global_work_size[0]);
	ret[1] = clEnqueueNDRangeKernel(def_col->command_queue, def_col->kernel, 1, NULL, global_work_size, local_work_size, 0, NULL, NULL);

	/*
	int i = e->max_iter - 1;
	printf("define_color[%d]	beg:%d	eng:%d	total:%d\n", i, id_tab[i + 1], id_tab[i], (id_tab[i + 1] - id_tab[i]));
	*/
		return (check_ocl_err(ret, 2, __func__, __FILE__));
	return (0);
}
