/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_define_colore.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 22:38:20 by fjanoty           #+#    #+#             */
/*   Updated: 2017/06/16 21:42:34 by fjanoty          ###   ########.fr       */
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

#define TRANS_TEST 128
float	trans_raw[128][4][2] = {
						{{0.000000, 0.000000},{0.635547, -0.700717},{0.497671, -0.047698},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.632301, -0.705343},{0.498261, -0.055883},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.628625, -0.709354},{0.499492, -0.064428},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.624500, -0.712602},{0.502829, -0.078653},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.620572, -0.714682},{0.505140, -0.086400},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.616174, -0.716030},{0.508161, -0.094419},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.610507, -0.716476},{0.512607, -0.103850},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.605804, -0.715903},{0.516688, -0.110991},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.601543, -0.714738},{0.520644, -0.116973},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.589454, -0.708508},{0.525849, -0.123808},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.552019, -0.704856},{0.531664, -0.130383},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.515712, -0.696356},{0.538711, -0.137191},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.494961, -0.684888},{0.552370, -0.147664},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.481361, -0.669327},{0.568687, -0.156634},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.469257, -0.652953},{0.583624, -0.162199},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.456048, -0.632641},{0.600124, -0.165852},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.444431, -0.612817},{0.614636, -0.167087},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.431905, -0.589485},{0.630123, -0.166435},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.426014, -0.577830},{0.637303, -0.165437},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.410929, -0.546023},{0.655247, -0.160913},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.399228, -0.519408},{0.668588, -0.155490},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.392276, -0.502778},{0.676216, -0.151488},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.384232, -0.482761},{0.684714, -0.146136},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.371881, -0.450345},{0.696971, -0.136414},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.366094, -0.434429},{0.702335, -0.131233},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.353310, -0.397504},{0.713181, -0.118357},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.341748, -0.361836},{0.721602, -0.104990},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.330590, -0.325105},{0.728216, -0.090495},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.319751, -0.286905},{0.732915, -0.074850},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.314728, -0.268232},{0.734408, -0.067053},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.310216, -0.250863},{0.735324, -0.059738},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.304387, -0.227487},{0.735836, -0.049833},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.311041, -0.256407},{0.734786, -0.032917},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.305594, -0.229550},{0.731287, -0.016159},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.322235, -0.264583},{0.728398, -0.007365},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.326028, -0.256324},{0.721563, 0.007688},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.325805, -0.240756},{0.714018, 0.019818},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.325880, -0.232812},{0.709613, 0.025640},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.326552, -0.214374},{0.698008, 0.038089},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.327156, -0.205123},{0.691480, 0.043724},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.328080, -0.194467},{0.683396, 0.049659},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.330009, -0.178001},{0.669750, 0.057552},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.331287, -0.169303},{0.661992, 0.061034},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.332751, -0.160621},{0.653879, 0.063991},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.334383, -0.152098},{0.645562, 0.066351},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.336539, -0.142190},{0.635465, 0.068361},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.338780, -0.133105},{0.625808, 0.069448},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.340918, -0.125326},{0.617243, 0.069746},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.343209, -0.117764},{0.608659, 0.069422},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.345658, -0.110413},{0.600075, 0.068471},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.348209, -0.103425},{0.591701, 0.066922},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.350563, -0.097503},{0.584444, 0.065066},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.353300, -0.091167},{0.576517, 0.062463},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.356243, -0.084934},{0.568560, 0.059203},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.359793, -0.078120},{0.559686, 0.054727},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.363016, -0.072527},{0.552267, 0.050222},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.366295, -0.067355},{0.545302, 0.045265},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.369698, -0.062491},{0.538664, 0.039776},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.373821, -0.057227},{0.531389, 0.032720},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.380994, -0.049551},{0.520627, 0.019576},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.375419, 0.053154},{0.509721, 0.084999},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.402057, 0.109247},{0.518605, 0.114001},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.414170, 0.139253},{0.514511, 0.124288},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.418727, 0.170628},{0.505835, 0.138252},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.418727, 0.170628},{0.505835, 0.138252},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.414170, 0.139253},{0.514511, 0.124288},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.402057, 0.109247},{0.518605, 0.114001},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.375419, 0.053154},{0.509721, 0.084999},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.380994, -0.049551},{0.520627, 0.019576},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.373821, -0.057227},{0.531389, 0.032720},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.369698, -0.062491},{0.538664, 0.039776},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.366295, -0.067355},{0.545302, 0.045265},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.363016, -0.072527},{0.552267, 0.050222},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.359793, -0.078120},{0.559686, 0.054727},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.356243, -0.084934},{0.568560, 0.059203},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.353300, -0.091167},{0.576517, 0.062463},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.350563, -0.097503},{0.584444, 0.065066},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.348209, -0.103425},{0.591701, 0.066922},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.345658, -0.110413},{0.600075, 0.068471},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.343209, -0.117764},{0.608659, 0.069422},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.340918, -0.125326},{0.617243, 0.069746},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.338780, -0.133105},{0.625808, 0.069448},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.336539, -0.142190},{0.635465, 0.068361},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.334383, -0.152098},{0.645562, 0.066351},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.332751, -0.160621},{0.653879, 0.063991},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.331287, -0.169303},{0.661992, 0.061034},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.330009, -0.178001},{0.669750, 0.057552},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.328080, -0.194467},{0.683396, 0.049659},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.327156, -0.205123},{0.691480, 0.043724},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.326552, -0.214374},{0.698008, 0.038089},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.325880, -0.232812},{0.709613, 0.025640},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.325805, -0.240756},{0.714018, 0.019818},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.326028, -0.256324},{0.721563, 0.007688},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.322235, -0.264583},{0.728398, -0.007365},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.305594, -0.229550},{0.731287, -0.016159},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.311041, -0.256407},{0.734786, -0.032917},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.304387, -0.227487},{0.735836, -0.049833},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.310216, -0.250863},{0.735324, -0.059738},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.314728, -0.268232},{0.734408, -0.067053},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.319751, -0.286905},{0.732915, -0.074850},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.330590, -0.325105},{0.728216, -0.090495},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.341748, -0.361836},{0.721602, -0.104990},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.353310, -0.397504},{0.713181, -0.118357},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.366094, -0.434429},{0.702335, -0.131233},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.371881, -0.450345},{0.696971, -0.136414},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.384232, -0.482761},{0.684714, -0.146136},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.392276, -0.502778},{0.676216, -0.151488},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.399228, -0.519408},{0.668588, -0.155490},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.410929, -0.546023},{0.655247, -0.160913},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.426014, -0.577830},{0.637303, -0.165437},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.431905, -0.589485},{0.630123, -0.166435},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.444431, -0.612817},{0.614636, -0.167087},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.456048, -0.632641},{0.600124, -0.165852},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.469257, -0.652953},{0.583624, -0.162199},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.481361, -0.669327},{0.568687, -0.156634},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.494961, -0.684888},{0.552370, -0.147664},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.515712, -0.696356},{0.538711, -0.137191},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.552019, -0.704856},{0.531664, -0.130383},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.589454, -0.708508},{0.525849, -0.123808},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.601543, -0.714738},{0.520644, -0.116973},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.605804, -0.715903},{0.516688, -0.110991},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.610507, -0.716476},{0.512607, -0.103850},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.616174, -0.716030},{0.508161, -0.094419},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.620572, -0.714682},{0.505140, -0.086400},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.624500, -0.712602},{0.502829, -0.078653},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.628625, -0.709354},{0.499492, -0.064428},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.632301, -0.705343},{0.498261, -0.055883},{1.000000, 0.000000}},
						{{0.000000, 0.000000},{0.635547, -0.700717},{0.497671, -0.047698},{1.000000, 0.000000}},
																												};




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
	static		int id_trans = 0;
	int			i;


	for (i = 0; i < 4; i++)
	{
		spec->pt_trans[i][0] = trans_raw[id_trans][i][0];
		spec->pt_trans[i][1] = trans_raw[id_trans][i][1];
	}
	id_trans = (id_trans + 1) % TRANS_TEST;
	spec->len_trans = 2;


	spec->len_base = 4;//get_polygone_len(e->base);

	spec->max_iter = 4;
	set_id_isf_ptbuff(spec->len_base, spec->len_trans, spec->max_iter, id_tab);

	spec->max_pt = id_tab[HARD_ITER] - id_tab[HARD_ITER - 1]; 
	spec->ecr_x = w->size_x;
	spec->ecr_y = w->size_y;
	spec->nb_iter = e->max_iter;

	set_range_val(&(spec->hue), 0, 1);
	set_range_val(&(spec->sat), 0, 1);
	set_range_val(&(spec->val), 0, 1);

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
			|| memcmp(&spec->hue, &prev_spec.hue, sizeof(t_range))
			|| memcmp(&spec->sat, &prev_spec.sat, sizeof(t_range))
			|| memcmp(&spec->val, &prev_spec.val, sizeof(t_range)))
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
	global_work_size[0] = id_tab[HARD_ITER - 1] - id_tab[HARD_ITER - 2];
	//printf("define_color:%zu\n", global_work_size[0]);
	ret[1] = clEnqueueNDRangeKernel(def_col->command_queue, def_col->kernel, 1, NULL, global_work_size, local_work_size, 0, NULL, NULL);

	/*
	int i = e->max_iter - 1;
	printf("define_color[%d]	beg:%d	eng:%d	total:%d\n", i, id_tab[i + 1], id_tab[i], (id_tab[i + 1] - id_tab[i]));
	*/
		return (check_ocl_err(ret, 2, __func__, __FILE__));
	return (0);
}
