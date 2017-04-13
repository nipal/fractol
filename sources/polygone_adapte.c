/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone_adapte.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 03:46:55 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/13 11:15:27 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
struct			s_polygone
{
	int			lvl;
	t_matrix	*pos;
	t_matrix	*col;
	t_polygone	*next;
};

typedef struct	s_matrix
{
	double		*m;
	int			x;
	int			y;
}				t_matrix;
*/

t_data_nw	format_data_to_network(t_polygone *transform, t_polygone *base, int nb_iter, double col[6])
{
	t_data_nw	data;
	int			i;
	t_polygone	*node;
	double		col_val[6];

	bzero(&data, sizeof(t_data_nw));
	data.base_len = get_polygone_len(base);
	data.trans_len = get_polygone_len(transform);

	//	on copie juste la valeur des point de la base dans la structure de buffer
	node = base;
	i = 0;
	while (i < MAX_NODE && node)
	{
		data.pt_base[i][0] = node->pos->m[0];
		data.pt_base[i][1] = node->pos->m[1];
		node = node->next;
		i++;
	}

	//	on copie juste la valeur des point de la transformation dans la structure de buffer
	node = transform;
	i = 0;
	while (i < MAX_NODE && node)
	{
		data.pt_trans[i][0] = node->pos->m[0];
		data.pt_trans[i][1] = node->pos->m[1];
		node = node->next;
		i++;
	}
	data.max_iter = nb_iter;	
	memmove(&(data.col_val), col, sizeof(double) * 6);
	return (data);
}

t_polygone	*make_tpolygone_from_data(double pt_data[MAX_NODE][2], int len)
{
	t_polygone	*beg;
	t_polygone	*node;
	t_polygone	*prev;
	t_matrix	*vect_pos;
	t_matrix	*vect_col;
	double		pos[3];
	double		col[3];
	int	i;

	//	initialisation
	if (len >= MAX_NODE)	
		len = MAX_NODE;
	pos[2] = 0;
	col[0] = 0;
	col[1] = 0;
	col[2] = 0;
	node = NULL;
	prev = NULL;
	i = 0;
	//	recreation de toute les strucure et des truc qui se font malloc
	while (i < len)
	{
		pos[0] = pt_data[i][0];
		pos[1] = pt_data[i][1];
		if (!(vect_pos = vect_new_vert(pos, 3))
			|| !(vect_col = vect_new_vert(col, 3))
			|| !(node = creat_node_fv(0, vect_pos, vect_col)))
			return (NULL);
		if (prev)
			prev->next = node;
		else
			beg = node;
		prev = node;
		i++;
	}
	node->next = NULL;
	return (beg);
}

int		format_data_to_print(t_data_nw *data_src, t_ifs_param *data_dst)
{
	data_dst->transform_len = data_src->trans_len;
	data_dst->base_len = data_src->base_len;
	data_dst->max_iter = data_src->max_iter;
	data_dst->trans = make_tpolygone_from_data(data_src->pt_trans, data_src->trans_len);
	data_dst->base = make_tpolygone_from_data(data_src->pt_base, data_src->base_len);
	memmove(data_dst->col_val, data_src->col_val, sizeof(double) * 6);
	return (0);
}


void	print_data_network(t_data_nw *data)
{

}

void 	print_data_ifs(t_ifs_param *data)
{
	printf("segment transformation\n");
	polygone_describe(data->trans);
	printf("segment base\n");
	polygone_describe(data->base);

	printf("max_iter:%d\n", data->max_iter);
	printf("base_len:%d\n", data->base_len);
	printf("trans_len:%d\n", data->transform_len);
}
