/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_koch_final.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 22:25:43 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/10 14:56:23 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
/*
**	La on va faire la versione finale avec +- une grosse fonction + truc anonime etc
**	
 */

double	diff_2(t_matrix *pt1, t_matrix *pt2)
{
	int		i;
	int		max;
	double	sum;

	if (!pt1 || !pt2 || pt1->x != pt2->x || pt1->y != pt2->y)
		return (0);
	max = pt1->x * pt1->y;
	i = 0;
	sum = 0;
	while (i < max)
	{
		sum += pt1->m[i] * pt2->m[i];
		i++;
	}
	return (sum);
}

/*
**	CONSTANT:
**		t_polygone	*transform;
**		t_win		*win;
**		double		max_iter;
**		double		len_seg;
**		double		len_seg_beg;
**		double		min_print;
**	
**	EVOLUTIF:
**		t_polygone	*seg;
**		double		iteration;
**		double		dist;
**		double		prev_du;
**		
**	
**	PRINT NEED: (one_seg) (en gros les deux truc)
**		t_win		*win;
**		double		max_iter;
**		double		len_seg;
**		double		len_seg_beg;
**		
**		t_polygone	*seg;
**		double		iteration;
**		double		dist;
*/

t_koch_changing	init_kch(t_polygone *seg, double iteration, double dist, double prev_du)
{
	t_koch_changing	kch;

	kch.seg = seg;
  	kch.iter = iteration;
	kch.dist = dist;
	kch.prev_du = prev_du;
	return (kch);
}

void		init_koch_const(t_koch_const *kco, t_polygone *transform, t_win *w, double *data)
{
	kco->trans = transform;
	kco->w = w;
	kco->max_iter = data[0];
	kco->len_seg = data[1];
	kco->len_seg_beg = data[2];
	kco->min_print = data[3];
}

void	draw_seg_koch(t_koch_const *kco, t_koch_changing kch, t_polygone *seg, double i)
{
	// on aurra aussi besoin de recuperer la conertion des coueleur... enfin
	(void)kco;
	(void)kch;
	(void)i;
	int	sub;
	int	len = len = ((kch.iter == 0) ? kco->len_seg_beg : kco->len_seg);
	double	delta[3];
	double	min[3];

	delta[0] = kco->w->e->sliders[0]->v2 - kco->w->e->sliders[0]->v1;
	delta[1] = kco->w->e->sliders[1]->v2 - kco->w->e->sliders[1]->v1;
	delta[2] = kco->w->e->sliders[2]->v2 - kco->w->e->sliders[2]->v1;
	min[0] = kco->w->e->sliders[0]->v1;
	min[1] = kco->w->e->sliders[1]->v1;
	min[2] = kco->w->e->sliders[2]->v1;

//	min[0] + (coef * delta[0])
//void		tsl_to_rvb_new(double t, double s, double l, t_matrix *rvb)
	//	on actualise la couleur
	//	on imprime, (ca serrai cool de pouvoir activer ou non le fait de calculer la coueleur)	
//printf("lvl:%d\n", seg->lvl);
//printf("kco->max_iter:%f\n", kco->max_iter);
//printf("dist:%f\n", kch.dist);
	sub = (i == 0 || i == (len - 2)) ? 1: 0;
	tsl_to_rvb_in((delta[0] * kch.dist + (min[0])) * 360
			, ((double)(seg->lvl) / (double)kco->max_iter) * delta[1] + min[1]
			, (double)((seg->lvl) / kco->max_iter) * delta[2] + min[2], seg->col);

	tsl_to_rvb_in((kch.dist * delta[0] + min[0]) * 360
			, (min[1] + delta[1] * (double)(seg->lvl) / (double)kco->max_iter)
		, ((double)(seg->lvl) / (double)kco->max_iter) * delta[2] + min[2], seg->col);
//	tsl_to_rvb_in(kch.dist * 150 + 120, kch.iter / kco->max_iter * 0.5,  (i) / kco->len_seg, seg->col);
	draw_simple_polygone(kco->w, seg);
}

void	draw_all_little(t_koch_const *kco, t_koch_changing kch, t_polygone *seg)
{
	double	i;

	i = 0;
	while (seg)
	{
		draw_seg_koch(kco, kch, seg, i);
		i++;
		seg = seg->next;
	}
}

void	 print_koch_fractale(t_koch_const *kco, t_koch_changing kch)
{
	t_polygone	*cpy;
	t_polygone	*to_insert;
	double	i;
	double	du;
	double	len;

	cpy = NULL;
	i = 0;
	len = ((kch.iter == 0) ? kco->len_seg_beg : kco->len_seg);
	du = kch.prev_du / len;
	if (kch.iter >= kco->max_iter)
		draw_all_little(kco, kch, kch.seg);
	while (kch.seg->next)
	{
		if (kch.iter >= kco->max_iter || (diff_2(kch.seg->pos, kch.seg->next->pos) < kco->min_print))
			draw_seg_koch(kco, kch, kch.seg, i);
		else if (!(cpy = copy_node(kch.seg, kch.seg->lvl))
			|| !(cpy->next = copy_node(kch.seg->next, kch.seg->next->lvl)))
			return ;
		else if ((to_insert = creat_insert(cpy, kco->trans))
				&& (insert_portion(&(cpy), to_insert)))
			print_koch_fractale(kco, init_kch(cpy, kch.iter + 1 , kch.dist + (du * i / len), du));
		i += polygone_destroy(&(cpy)) > -1;
		kch.seg = kch.seg->next;
	}
}

void	print_fractal(t_env *e)
{
	double			data_koch[4];
	t_koch_const	kco;
	if (e->transform && e->base)
	{
		data_koch[0] = e->max_iter;
		data_koch[1] = get_polygone_len(e->transform) + 1;
		data_koch[2] = get_polygone_len(e->base);
		data_koch[3] = 25;
		init_koch_const(&kco, e->transform, e->fractal, data_koch);
		print_koch_fractale(&kco, init_kch(e->base, 0, 0, 1));
		actu_win_rest(e->fractal);
	//	actu_win_rest(e->fractal);
	}
}
