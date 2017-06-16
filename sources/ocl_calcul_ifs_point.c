/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_calcul_ifs_point.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 10:39:22 by fjanoty           #+#    #+#             */
/*   Updated: 2017/06/16 21:42:13 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


int		set_id_isf_ptbuff(int nb_base, int nb_trans, int nb_iter, int *indice_beg);

int	ocl_mem_creat_calcul_ifs(t_ocl_ker *ifs_ker)
{
	cl_int	ret[2];

	ifs_ker->nb_arg = 2;
	ret[0] = ocl_create_mem(ifs_ker, 0	, CL_MEM_READ_WRITE, BIG_OCL_BUF_SIZE * sizeof(float) * 2);
	ret[1] = ocl_create_mem(ifs_ker, 1, CL_MEM_READ_WRITE, sizeof(t_ifs_spec));
	//	en fait il faudrai tester avec un set kernel arg pck on a pas besoind de plus ==> normalement c'est fait
	branch_arg_to_kernel(ifs_ker, 2);
	return (check_ocl_err(ret, 2, __func__, __FILE__));
}

int		format_data_to_ocl(t_ifs_ocl *data, int nb_iter, float col[6])
{
	float	hard_base[4][2] =
	{{657.534241, 341.694916},{250.684937, 919.322021},{1035.616455, 1004.745789},{661.643860, 341.694916}};

	int			i;
	double		col_val[6]; // param de couleur (les v1 et v2 des button)

	if (!data)
		return (-1);
	bzero(data, sizeof(t_ifs_ocl));
	data->base_len = HARD_BASE_LEN;
	data->trans_len = HARD_TRANS_LEN;
	i = 0;
	while (i < 4)
	{
		data->pt_base[i][0] = hard_base[i][0];
		data->pt_base[i][1] = hard_base[i][1];
		i++;
	}

	return (0);
}

//	on recupere toutes les data et on les envoie aux kernel
int	ocl_writeto_ifs_calcul(t_ocl_ker *ifs_cl, t_ifs_ocl *data)
{
	int		tab_id[MAX_ITER];
	cl_int	ret[1];


	ret[0] = clEnqueueWriteBuffer(ifs_cl->command_queue, ifs_cl->data[e_cip_pt_ifs].gpu_buff, CL_TRUE	, 0, MAX_NODE * sizeof(float) * 2, data->pt_base, 0, NULL, NULL);
	return (check_ocl_err(ret, 1, __func__, __FILE__));
}

void	print_id_tab(int *tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("id[%d]:%d\n", i, tab[i]);
		i++;
	}
}

// il faut initialiser les index
int		set_id_isf_ptbuff(int nb_base, int nb_trans, int nb_iter, int *indice_beg)
{
	int		sum;
	int		iter_max;
	int		i;

	i = 1;
	indice_beg[0] = 0;
	sum = nb_base;
	while (i < MAX_ITER)
	{
		sum += (sum - 1) * (nb_trans);// le truc presedent
		indice_beg[i] = indice_beg[i - 1] + sum;
		i++;
	}
	return (0);
}


//	le truc qui lance le calcule de tout les point
int	ocl_ifs_calcul_run(t_ocl_ker *ifs_cl, int nb_iter, float col[6])
{
	int			i;
	int			id_tab[MAX_ITER];
	t_ifs_ocl	data;
	cl_int		ret[MAX_ITER], ret2, ret3;
	size_t		global_work_size[3] = {1, 0, 0};
	size_t		local_work_size[3] = {1, 0, 0};

	// les work_size c'est le nombre de coeur qu'on execute en meme temps
	format_data_to_ocl(&data, nb_iter, col);	
	set_id_isf_ptbuff(4, 2, nb_iter, id_tab);
	ocl_writeto_ifs_calcul(ifs_cl, &data);
//	print_id_tab(id_tab, MAX_ITER);
	i = 1;
	while (i <= nb_iter)
	{
		global_work_size[0] = id_tab[i + 1] - id_tab[i]; // Soit calcul une id de plus; Soit avoir une varible qui stoque le resulta

		ret2 = clSetKernelArg(ifs_cl->kernel, 2, sizeof(int), &i);
		if (ret2)
			check_ocl_err(&ret2, 1, "tata yoyo", __FILE__);
		ret[i] = clEnqueueNDRangeKernel(ifs_cl->command_queue, ifs_cl->kernel, 1, NULL, global_work_size, local_work_size, 0, NULL, NULL);
		if (ret[i])
			check_ocl_err(ret, i + 1, __func__, __FILE__);
		i++;
	}
	return (0);
}

