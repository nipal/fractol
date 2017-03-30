/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_printing_koch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 23:23:51 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/31 01:03:48 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static	inline	t_koch_changing	init_kch(t_polygone *seg, double iteration
		, double dist, double prev_du)
{
	t_koch_changing	kch;

	kch.seg = seg;
	kch.iter = iteration;
	kch.dist = dist;
	kch.prev_du = prev_du;
	return (kch);
}

void							init_koch_const(t_koch_const *kco
		, t_polygone *transform, t_win *w, double *data)
{
	kco->trans = transform;
	kco->w = w;
	kco->max_iter = data[0];
	kco->len_seg = data[1];
	kco->len_seg_beg = data[2];
	kco->min_print = data[3];
}

void							print_fractal(t_env *e)
{
	double			data_koch[4];
	t_koch_const	kco;
	t_data_nw		data;
	int				*clients;

	if (e->transform && e->base)
	{
		if (e->status == SERVEUR)
		{
			data = format_data_to_network(e->transform, e->base, e->max_iter);
			clients = get_all_open_sockets(-1);
			int	i = 0;
			while (clients[i])
				write(clients[i], &data, sizeof(t_data_nw));
		}
		data_koch[0] = e->max_iter;
		data_koch[1] = get_polygone_len(e->transform);
		data_koch[2] = get_polygone_len(e->base);
		data_koch[3] = 400;	//	ne sert a rien
		init_koch_const(&kco, e->transform, e->fractal, data_koch);
		print_koch_fractale(&kco, init_kch(e->base, 0, 0, 1), 0);
		actu_win_rest(e->fractal);
	}
}

/*
**	liste de ce qu'on a besoin dans "t_env *e" pour dessiner une fractale:
**	
	e->transform
	e->base

	e->max_iter
	polygone_len(transform)
	polygone_len(base)
	e->fractal ==> le t_win mais donc ca le clien a le sien donc OSEF
*/

//# define MAX_NODE 16	// c'est deja enorme
//	typedef	struct	s_ifs_param
//	{
//		t_polygone	transform[MAX_NODE];	// il faudra le transformer en tableau et definir les next comme il le faut
//		t_polygone	base[MAX_NODE];
//		int			transform_len;
//		int			base_len;
//		int			max_iter;
//	
//	}				t_ifs_param;
//	

void		print_client_ifs(t_win *w, t_ifs_param *param)
{
	double			data_koch[4];
	t_koch_const	kco;

	printf("on imprime\n");
	if (w && param)
	{
		print_data_ifs(param);
		data_koch[0] = param->max_iter;
		data_koch[1] = param->transform_len;
		data_koch[2] = param->base_len;
		data_koch[3] = 0;	//	ne sert a rien
		init_koch_const(&kco, param->trans, w, data_koch);
		print_koch_fractale(&kco, init_kch(param->base, 0, 0, 1), 0);
//		actu_win_rest(w);
	}
}
