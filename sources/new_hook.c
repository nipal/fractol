/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 10:37:32 by fjanoty           #+#    #+#             */
/*   Updated: 2017/12/06 20:02:12 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mouse_inside(int x, int y, t_win *w)
{
	if (!w || x < 0 || x >= w->size_x || y < 0 || y >= w->size_y)
		return (0);
	return (1);
}

int		calcul_nb_ite_max(int nb_base, int nb_trans, int size_mem, int *indice_beg)
{
	int		iter_max;
	int		i;
	int		sum;

	(void)indice_beg;
	if (!indice_beg || nb_base <= 1 || nb_trans <= 2)
		return (-1);
	size_mem /= sizeof(float) * 2;
	sum = nb_base;
	iter_max = 0;
	while ((sum = sum * (nb_trans + 1)) <= size_mem)
		iter_max++;
//	i = 1;
//	sum = nb_base;
//	indice_beg[0] = 0;
//	while (i < iter_max)
//	{
//		indice_beg[i] = sum - 1;
//		sum = sum * (nb_trans + 1);
//		i++;
//	}
	return (iter_max);
}

void	change_iter(t_win *w, int incr)
{
	int		indice_beg[MAX_NODE];
	int		iter_max;
	size_t	all_node;
	size_t	size;
	size_t	len_base;
	size_t	len_transform;
	size_t	nb_iter;
	int		i;


	if (incr >= 0)	
	{
		// len_base
		// len_trans
		// max_iter
		// il faudrait calculer la size
		len_base = get_polygone_len(w->e->base_model);
		len_transform = get_polygone_len(w->e->trans_model);
		iter_max = 1 + calcul_nb_ite_max(len_base, len_transform, MAX_GPU_BUFF, indice_beg);
//		printf("iter_max:%d\n", iter_max);
		if (w->e->max_iter < iter_max && incr)
			w->e->max_iter++;
	}
	else if  (w->e->max_iter > 0)
		w->e->max_iter--;
	if (w->e->max_iter > iter_max)
		w->e->max_iter = iter_max;
}

int		press_key(int key_code, t_win *w)
{
//	printf("--------->	%d\n", key_code);
	(key_code == 53) ? ft_exit(w->e) : 0;
	(key_code == 36) ? change_iter(w, 1) : 0;
	(key_code == 51) ? change_iter(w, -1): 0;
	(key_code == 49) ? w->e->add_point = 1 : 0;
	(key_code == 45) ? print_param(w->e) : 0;
	(key_code == 46) ? print_direct_trans(w->e) : 0;
	(key_code == 11) ? printf("\n"): 0;
	if (key_code == 15 && ft_strcmp(w->name, "param") == 0)
	{
		if (mouse_in_border(&(w->e->border_b), w->mouse))
			reset_base(w->e);
		else if (mouse_in_border(&(w->e->border_t), w->mouse))
			reset_transform(w->e);
	}
	change_iter(w, 0);
	(key_code == 36 || key_code == 51) ? print_fractal(w->e) : (void)w;
	return (1);
}

int		release_key(int key_code, t_win *w)
{
	(key_code == 49) ? w->e->add_point = 0 : 0;
	return (1);
}

int		motion_cursor(int x, int y, t_win *w)
{
	int		on;
	int		id;

	w->mx = x;
	w->my = y;
	if (!ft_strcmp(w->name, "param"))
		actu_polygone_io(w->e, w);
	actu_mouse_pos(w, x, y);
	if (w->e->base_add != 0 && w->button1 && mouse_in_border(&(w->e->border_b)
				, w->mouse))
		on = move_the_node(w->e, w->e->base_model)
			+ actu_base(w->e, w->e->base_model);
	if (w->e->trans_add != 0 && w->button1 && mouse_in_border(&(w->e->border_t)
				, w->mouse))
		on = move_the_node(w->e, w->e->trans_model)
			+ actu_transform(w->e, w->e->trans_model);
	if (w->e->id_scrol >= 0 && w->e->max_iter >= -1)
		actu_base(w->e, w->e->base_model);
	if (!ft_strcmp("fractal", w->name) && w->e->move_set)
	{
		w->e->tr_base[0] += w->mouse->m[0] - w->prev_mouse->m[0];
		w->e->tr_base[1] += w->mouse->m[1] - w->prev_mouse->m[1];
		actu_base(w->e, w->e->base_model);
	}
	if (!ft_strcmp("param", w->name) && w->button1)
	{
		id = w->e->id_anime_clicked;
		move_the_node(w->e, lst_anime[id].ovaloide);	
	}
	main_work(w->e);
	return (on + 1);
}
