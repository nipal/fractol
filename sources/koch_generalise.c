/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   koch_generalise.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 04:10:47 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/11 17:12:22 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//		il faut faire le lien entre deux ligne
//		on stoque le truc sous frme de liste, comme ca on peu rajouter ou enlever point
//		
//		->	move de la souris actualise la position du gernier point
//		->	le clique ajoute un dernier maillon
//
//		->	dans un maillon on stoque la position du point et eventuelement l'iteration du  point
//
//		->	quand on ajoute une iteration on sauvgarde le point suivant et on rejoute entre ceux qui sont sensser y etre
//		->	a chaque fois on redessine toute la liste
//		->	pour le zoom on peu oublier un peu certian point mais il faudra reconstruire des truc pour le de zoom

	

void		print_polygone(t_env *e, t_polygone *seg)
{
	if (!seg)
		return ;
	while (seg->next)
	{
		trace_seg_line(e, seg);
		seg = seg->next;
	}
}

t_polygone	*get_last(t_polygone *node)
{

	if (node)
	{
		while (node && node->next)
			node = node->next;
	}
	return (node);
}

int			insert_portion(t_polygone **target, t_polygone *src)
{
	t_polygone	*tmp;

	if (!target || !src)
	{
		return (0);
	}
	if (*target)
	{
		if ((tmp = get_last(src)))
			tmp->next = (*target)->next;
		(*target)->next = src;
	}
	else
	{
		*target = src;
	}
	return (1);
}


//	description de transformation
//		homotecie puis translation
//			-on place une origine
//			-on mulipli
//			-on tourne
//			-on replace
//
//	determiner la transformation de deux point
//
//
//	creation de polygone avec click gauche , clique droit

void	push_back(t_polygone **root, t_polygone *node)
{
	t_polygone	*tmp;

	if (!root)
		return ;
	else if (*root)
	{
		if ((tmp = get_last(*root)))
			tmp->next = node;
		node->next = NULL;
	}
	else
		*root = node;
}

void	init_koch(t_env *e)
{
	e->actif = NULL;
	e->beg_actif = NULL;
	e->draw_base = 1;
	e->draw_transform = 0;
	e->add_iter = 0;
	e->transform = NULL;
	e->trans_controle = NULL;
	e->iter_koch = 0;
	e->mouse = NULL;
	e->prev_mouse = NULL;
	e->r_select = 20;
	e->left = 0;
	e->right = 0;
	e->min_val_trans = 0;
}

int		reset_koch(t_env *e)
{
	polygone_destroy(&(e->transform));
	polygone_destroy(&(e->beg_actif));
	polygone_destroy(&(e->trans_controle));
	polygone_destroy(&(e->base));
	e->base = NULL;
	init_koch(e);
	return (1);
}

void	add_point(t_polygone **node, int x, int y, int lvl)
{
	t_polygone	*last;
	double		pos[3];
	double		col[3];

	if (!node)
		return ;
	pos[0] = x;
	pos[1] = y;
	pos[2] = 0;
	col[0] = 250;
	col[1] = 250;
	col[2] = 250;
	if (!(last = creat_node(lvl, pos, col)))
		return ;
	if (*node)
		(*node)->next = last;
	*node = last;
	(*node)->next = NULL;
}

void	increm_polygone(int x, int y, t_env *e)
{
	add_point(&(e->actif), x, y, 0);
	if (!(e->beg_actif))
		e->beg_actif = e->actif;
}

void	move_last(int x, int y, t_env *e)
{
	if (e->actif)
	{
		e->actif->pos->m[0] = x;
		e->actif->pos->m[1] = y;
	}
}


void	end_base(t_env *e)
{
	t_polygone	*last;

	if (!e->actif || !e->beg_actif || !(last = copy_node(e->beg_actif, 0)))
		return ;
	e->draw_base = 0;
	e->draw_transform = 1;
	e->base = e->beg_actif;
//	e->actif->next = last;
	e->actif = NULL;
	e->beg_actif = NULL;
}

void	end_transform(t_env *e)
{
	e->draw_transform = 0;
	e->actif = NULL;
	e->transform = transform(e->beg_actif);

	init_trans_control(e);
	e->beg_actif = NULL;
}


void		zero_double(double *tab1, double *tab2, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		tab1[i] = 0;
		tab2[i] = 0;
		i++;
	}
}

//	on calcule un produit scalaire avec ux et uy sur des vecteur 
//	sauvgarde transformation e reference
//	aplication de la franformation
