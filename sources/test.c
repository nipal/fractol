/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 20:15:57 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/28 04:58:25 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	ici on va faire une genre de fonction pour pre inegrer des nouvelle feature
*/

#include "fractol.h"

///*
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
//*/

/* 
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

	if (e->transform && e->base)
	{
		data_koch[0] = e->max_iter;
		data_koch[1] = get_polygone_len(e->transform);
		data_koch[2] = get_polygone_len(e->base);
		data_koch[3] = 400;
		init_koch_const(&kco, e->transform, e->fractal, data_koch);
		print_koch_fractale(&kco, init_kch(e->base, 0, 0, 1), 0);
		actu_win_rest(e->fractal);
	}
}

//*/


/*
**	la on va faire une "classe" de fonction type pour les animation
**	elle on un parametrage et un nombre entre 0 et 1 pour l'avencement de l'anime
*/

void	anime_circle_pt(double *dst, double anime, double cx, double cy, double r)
{
	dst[0] = cos(anime * M_PI * 2) * r + cx;
	dst[1] = sin(anime * M_PI * 2) * r + cy;
}

/*
**	cette fonction va etre un ban de test pour imlpementer le module animation
**	donc pour l'instant je cree toute les data de base et donc je ne les recupere pas d'une interface (next stape)
**
**	donc pour linstant on aurra une base avec systementiquement que 1 segment (donc deux point)
*/

void	feature_testing(t_env *e)
{

	//	manage anime test
	double			NB_ANIME = 300;
	static	double	iter	= 0; (void)iter;
	double			anime;
	double			unite = 4;
//		static	int	started	= 0;
	double	pos[3] = {0, 0, 0};
	double	col[3] = {0, 0, 0};

	//	param anime
	t_polygone		*trans;
	t_polygone		*base;
	double			data_koch[4];
	t_koch_const	kco;

	anime = iter / NB_ANIME;
	anime = modf(anime, &unite);
//		t_koch_changing	kch;


	/*
	if (started == 0)
	{
		started = 1;
	}
	*/

	//	init_kch

	double	a, b, c, d;

	a = 10;
	b = 10;
//		c = 5;
	d = 3;

	base = NULL;	
	pos[2] = 0;
	pos[0] = 400; pos[1] = 400;
	push_back(&(base), creat_node(0, pos, col));
	pos[0] = 1000; pos[1] = 1000;
	push_back(&(base), creat_node(0, pos, col));

	trans = NULL;
	pos[0] = 0.0; pos[1] = 0.0;
	push_back(&(trans), creat_node(0, pos, col));

	anime_circle_pt(pos, a * anime, 0.1, 0.1, 0.05);
	push_back(&(trans), creat_node(0, pos, col));

//		anime_circle_pt(pos, b * anime, 0.3, -0.2, 0.02);
//		push_back(&(trans), creat_node(0, pos, col));

//		anime_circle_pt(pos, c * anime, 0.7, -0.2, 0.01);
//		push_back(&(trans), creat_node(0, pos, col));

	anime_circle_pt(pos, d * anime, 0.35, 0.3, 0.1);
	push_back(&(trans), creat_node(0, pos, col));


	pos[0] = 1; pos[1] = 0;
	push_back(&(trans), creat_node(0, pos, col));

	data_koch[0] = e->max_iter;
	data_koch[1] = get_polygone_len(trans);
	data_koch[2] = get_polygone_len(base);
	data_koch[3] = e->max_iter;
	init_koch_const(&kco, trans, e->fractal, data_koch);
	print_koch_fractale(&kco, init_kch(base, 0, 0, 1), 0);
	actu_win_rest(e->fractal);

	polygone_destroy(&trans);
	polygone_destroy(&base);
	iter += 1;
}
