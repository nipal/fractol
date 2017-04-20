/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_calcul_ifs_point.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 10:39:22 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/19 22:30:18 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


int	init_mem_calcul_ifs(t_ocl_core *core, t_ocl_ker *ifs_ker)
{
	cl_int	ret[5];

	ifs_ker->nb_arg = 5;
	ret[0] = ocl_create_mem(ifs_ker, 0, CL_MEM_READ_WRITE, BIG_OCL_BUF_SIZE * sizeof(float) * 2);
	ret[1] = ocl_create_mem(ifs_ker, 1, CL_MEM_READ_ONLY, MAX_ITER * sizeof(int));
	ret[2] = ocl_create_mem(ifs_ker, 2, CL_MEM_READ_ONLY, sizeof(int));
	ret[3] = ocl_create_mem(ifs_ker, 3, CL_MEM_READ_ONLY, sizeof(int));
	ret[4] = ocl_create_mem(ifs_ker, 4, CL_MEM_READ_ONLY, sizeof(int));
	branch_arg_to_kernel(ifs_ker, 5);
	return (check_ocl_err(ret, 5, __func__, __FILE__));
}

int		format_data_to_ocl(t_ifs_ocl *data, t_polygone *transform, t_polygone *base, int nb_iter, float col[6])
{
	int			i;
	t_polygone	*node;
	double		col_val[6]; // param de couleur (les v1 et v2 des button)

	if (!data)
		return (-1);
	bzero(data, sizeof(t_data_nw));
	data->base_len = get_polygone_len(base);
	data->trans_len = get_polygone_len(transform);

	//	on copie juste la valeur des point de la base dans la structure de buffer
	node = base;
	i = 0;
	while (i < MAX_NODE && node && i < data->base_len)
	{
		data->pt_base[i][0] = (float) node->pos->m[0];
		data->pt_base[i][1] = (float) node->pos->m[1];
		node = node->next;
		i++;
	}

	//	on copie juste la valeur des point de la transformation dans la structure de buffer
	node = transform;
	i = 0;
	while (i < MAX_NODE && node && i < data->trans_len)
	{
		data->pt_trans[i][0] = (float) node->pos->m[0];
		data->pt_trans[i][1] = (float) node->pos->m[1];
		node = node->next;
		i++;
	}
	data->max_iter = nb_iter;
	
	//	on copie les parametre de couleur
	i = 0;
	while (i < 6)
	{
		data->col_val[i] = (float) col[i];
		i++;
	}
	return (0);
}

// il faut initialiser les index
int		set_id_isf_ptbuff(int nb_base, int nb_trans, int nb_iter, int *indice_beg)
{
	int		iter_max;
	int		i;
	int		sum;

	i = 1;
	sum = nb_base;
	indice_beg[0] = 0;
	while (i < nb_iter)
	{
		indice_beg[i] = sum - 1;
		sum = sum * (nb_trans + 1);
		i++;
	}
	return (0);
}

//	On va commencer par juste copier la base il faut encore

//	on recupere toutes les data et on les envoie aux kernel
int	ocl_writeto_ifs_calcul(t_ocl_ker *ifs_cl, t_ifs_ocl *data)
{
	int		tab_id[MAX_ITER];
	cl_int	ret[5];


	// pour l'initialisation de ifs_pt
	ret[0] = clEnqueueWriteBuffer(ifs_cl->command_queue, ifs_cl->data[0].gpu_buff, CL_TRUE, 0, data->base_len * sizeof(float) * 2, data->pt_base, 0, NULL, NULL);
	
	// pour la liste de transformation
	ret[1] = clEnqueueWriteBuffer(ifs_cl->command_queue, ifs_cl->data[1].gpu_buff, CL_TRUE, 0, data->trans_len * sizeof(float) * 2, data->pt_trans, 0, NULL, NULL);
	
	// pour le tableau d'indice
	ft_bzero(tab_id, sizeof(tab_id));
	set_id_isf_ptbuff(data->base_len, data->trans_len, data->max_iter, tab_id);
	ret[2] = clEnqueueWriteBuffer(ifs_cl->command_queue, ifs_cl->data[2].gpu_buff, CL_TRUE, 0, sizeof(tab_id), tab_id, 0, NULL, NULL);

	
	ret[3] = clEnqueueWriteBuffer(ifs_cl->command_queue, ifs_cl->data[3].gpu_buff, CL_TRUE, 0, ifs_cl->data[3].size, &(data->trans_len), 0, NULL, NULL);
	ret[4] = clEnqueueWriteBuffer(ifs_cl->command_queue, ifs_cl->data[4].gpu_buff, CL_TRUE, 0, ifs_cl->data[4].size, &(data->max_iter), 0, NULL, NULL);

	// Il me manque les write buffer pour les parametre qui ne sont pas forcement des buffer si non bah il le faut quoi
	return (check_ocl_err(ret, 5, __func__, __FILE__));
}



//	le truc qui lance le calcule de tout les point
int	ocl_ifs_calcul_run(t_ocl_ker *ifs_cl, t_polygone *transform, t_polygone *base, int nb_iter, float col[6])
{
	int			i;
	int			id_tab[MAX_ITER];
	t_ifs_ocl	data;
	cl_int		ret[MAX_ITER];
	size_t		global_work_size[3] = {1, 0, 0};
	size_t		local_work_size[3] = {1, 0, 0};

	// les work_size c'est le nombre de coeur qu'on execute en meme temps
	format_data_to_ocl(&data, transform, base, nb_iter, col);	
	set_id_isf_ptbuff(data.base_len, data.trans_len, nb_iter, id_tab);
	ocl_writeto_ifs_calcul(ifs_cl, &data);
	// on faire une boucle pour lancer les kernel pour faire les differente passe de rendu
	i = 1;
	while (i < nb_iter)
	{
		global_work_size[0] = id_tab[i + 1] - id_tab[i]; // Soit calcul une id de plus; Soit avoir une varible qui stoque le resulta
		ret[i] = clEnqueueNDRangeKernel(ifs_cl->command_queue, ifs_cl->kernel, 1, NULL, global_work_size, local_work_size, 0, NULL, NULL);
		i++;
	}
	return (0);
}

/*
 * Alors il faut rajouter les 2 variable qu'il manquait
 * - il leurs faut un cl_buff et transmetre les data et voila
 * */

int	ocl_init_ifs(t_env *e)
{
	init_ocl_core(&(e->ocl), "src_cl/ifs_render.cl");
	return (0);
}
