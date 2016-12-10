/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_koch_final.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 22:25:43 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/09 10:00:04 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

	t_koch_changing	init_kch(t_polygone *seg, double iteration
		, double dist, double prev_du)
{
	t_koch_changing	kch;

	kch.seg = seg;
	kch.iter = iteration;
	kch.dist = dist;
	kch.prev_du = prev_du;
	return (kch);
}

	int				draw_seg_koch(t_koch_const *kco
		, t_koch_changing kch, t_polygone *seg, double i)
{
	int				sub;
	int				len;
	double			delta[3];
	double			min[3];
	double			coef[3];

	len = ((kch.iter == 0) ? kco->len_seg_beg : kco->len_seg);
	delta[0] = kco->w->e->sliders[0]->v2 - kco->w->e->sliders[0]->v1;
	delta[1] = kco->w->e->sliders[1]->v2 - kco->w->e->sliders[1]->v1;
	delta[2] = kco->w->e->sliders[2]->v2 - kco->w->e->sliders[2]->v1;
	min[0] = kco->w->e->sliders[0]->v1;
	min[1] = kco->w->e->sliders[1]->v1;
	min[2] = kco->w->e->sliders[2]->v1;
	coef[0] = kch.dist;
	coef[1] = (double)(seg->lvl) / (double)kco->max_iter;
	coef[2] = i / (double)len;
	sub = (i == 0 || i == (len - 2)) ? 1 : 0;
	tsl_to_rvb_in((delta[0] * kch.dist + (min[0])) * 360
		, ((double)(seg->lvl) / (double)kco->max_iter) * delta[1] + min[1]
		, (double)((seg->lvl) / kco->max_iter) * delta[2] + min[2], seg->col);
	draw_simple_polygone(kco->w, seg);
	return (1);
}

//static	inline	void			draw_all_little(t_koch_const *kco
	void			draw_all_little(t_koch_const *kco
				, t_koch_changing kch, t_polygone *seg)
{
	double	i;

	i = 0;
	while (seg)
	{
		(void)kco;
		(void)kch;
		draw_seg_koch(kco, kch, seg, i);
		i++;
		seg = seg->next;
	}
}

void							print_koch_fractale(t_koch_const *kco
				, t_koch_changing kch, double i)
{
	t_polygone	*cpy;
	t_polygone	*to_insert;
	double		du;
	double		len;

	cpy = NULL;
	len = ((kch.iter == 0) ? kco->len_seg_beg : kco->len_seg);
	du = kch.prev_du / len;
	if (kch.iter >= kco->max_iter)
		draw_all_little(kco, kch, kch.seg);
	while (kch.seg->next)
	{
		if (kch.iter >= kco->max_iter)
			draw_seg_koch(kco, kch, kch.seg, i);
		else if (!(cpy = copy_node(kch.seg, kch.seg->lvl))
			|| !(cpy->next = copy_node(kch.seg->next, kch.seg->next->lvl)))
		{
			polygone_destroy(&(cpy));
//			polygone_destroy(&to_insert);
			return ;
		}
		else if ((to_insert = creat_insert(cpy, kco->trans))
				&& (insert_portion(&(cpy), to_insert)))
			print_koch_fractale(kco, init_kch(cpy, kch.iter + 1, kch.dist + ((du * i) / len), du), 0);
		i++;
//		garbage_node(cpy, ADD);
//		garbage_node(cpy->next, ADD);
//push_addr(16 , "", cpy);
//		polygone_destroy(&to_insert);
		polygone_destroy(&(cpy));
		kch.seg = kch.seg->next;
	}
//	polygone_destroy(&to_insert);
//	polygone_destroy(&(cpy));
}
