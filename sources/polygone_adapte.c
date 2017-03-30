/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone_adapte.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 03:46:55 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/30 20:27:23 by fjanoty          ###   ########.fr       */
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

t_data_nw	format_data_to_network(t_polygone *transform, t_polygone *base, int nb_iter)
{
	t_data_nw	data;
	int			i;
	t_polygone	*node;	

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
		data.pt_base[i][0] = node->pos->m[0];
		data.pt_base[i][1] = node->pos->m[1];
		node = node->next;
		i++;
	}
	return (data);
}

int		format_data_to_print(t_data_nw *data_src, t_ifs_param *data_dst)
{
	//	il faut recree les segment
	t_polygone	*beg;
	t_polygone	*node;
	t_polygone	*prev;
	int			i;
	double		pos[3];
	double		col[3];

	//	copy des parametre facile
	data_dst->transform_len = data_src->trans_len;
	data_dst->base_len = data_src->base_len;
	data_dst->max_iter = data_src->max_iter;

	//	initialisation
	pos[2] = 0;
	col[0] = 0;
	col[1] = 0;
	col[2] = 0;

	//	creation du t_polygone trans
	node = NULL;
	prev = NULL;
	i = 0;
	while (i < data_src->trans_len)
	{
		pos[0] = data_src->pt_trans[i][0];
		pos[1] = data_src->pt_trans[i][1];
		if (!(node = creat_node(0, pos, col)))
			return (-1);
		if (prev)
			prev->next = node;
		else
			beg = node;
		prev = node;
		i++;
	}
	node->next = NULL;
	data_dst->trans = beg;
		
	//	creation du t_polygone base
	node = NULL;
	prev = NULL;
	i = 0;
	while (i < data_src->base_len)
	{
		pos[0] = data_src->pt_trans[i][0];
		pos[1] = data_src->pt_trans[i][1];
		if (!(node = creat_node(0, pos, col)))
			return (-1);
		if (prev)
			prev->next = node;
		else
			beg = node;
		prev = node;
		i++;
	}
	node->next = NULL;
	data_dst->trans = beg;
	return (0);
}

//	ca c'est pour reorganiser les adresse des next des liste chianer recu par le reso
//	void	adapte_polygone_next(t_ifs_param *param)
//	{
//		int	i;
//	
//		i = 0;
//		while (i < MAX_NODE && param->transform[i]->next)
//		{
//			param->transform[i]->next = &(param->transform[i + 1]);
//			i++;
//		}
//		param->transform[i]->next = NULL;
//	
//		i = 0;
//		while (i < MAX_NODE && param->base[i]->next)
//		{
//			param->base[i]->next = &(param->base[i + 1]);
//			i++;
//		}
//		param->base[i]->next = NULL;
//	}
//	
//	t_ifs_param	creat_param_to_send(t_env *e)
//	{
//		t_ifs_param	buffer;
//		int			i;
//		t_polygone	*node
//	
//		node = e->transform;
//		for (i = 0; i < MAX_NODE; i++)
//		{
//			if (node)
//			{
//				
//				node = node->next;
//			}
//		}
//	
//		node = e->transform;
//	}

//	serveur --> RESEAU --> client
//	il faut transmetre les t_polygone: 
//	il faut aussi adapter les t_matrix

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


