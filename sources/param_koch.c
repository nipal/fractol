/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_koch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 13:27:00 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/24 03:08:13 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


int	reset_base(t_env *e)
{
	polygone_destroy(&(e->beg_actif));
	polygone_destroy(&(e->trans_model));
	polygone_destroy(&(e->base));
	e->actif = NULL;
	e->beg_actif = NULL;
	return (0);
}

int	reset_transform(t_env *e)
{
	polygone_destroy(&(e->transform));
	polygone_destroy(&(e->beg_actif));
	polygone_destroy(&(e->trans_model));
	e->actif = NULL;
	e->beg_actif = NULL;
	return (0);
}

/*
**	quand on reset l'un au l'aure on remet tout a zero
**	quand on clique dans un cadrde ET que base OU transform == null
*/

void	init_koch_param_border(t_env *e, t_win *win_param)
{
	int	border = 5;
	int	top = MIN(win_param->size_y * 0.5, win_param->size_x * 0.5);

	e->border_b.x0 = border;
	e->border_b.y0 = top;
	e->border_b.x1 = win_param->size_x * 0.5 - border * 0.5;
	e->border_b.y1 = win_param->size_y - border;
	e->border_t.x0 = win_param->size_x * 0.5 + border * 0.5;
	e->border_t.y0 = top;
	e->border_t.x1 = win_param->size_x - border;
	e->border_t.y1 = win_param->size_y - border;
}

void	draw_border(t_win *w, t_border *border, t_matrix *color)
{
	t_matline	mat_line;
	t_matrix	*pt1;
	t_matrix	*pt2;

	if (!(pt1 = vect_new_vertfd(border->x0, border->y0, 0))
			|| !(pt2 = vect_new_vertfd(border->x0, border->y1, 0)))
		return ;
	mat_line.pt1 = pt1;
	mat_line.pt2 = pt2;
	mat_line.c1 = color;
	mat_line.c2 = color;
	draw_line3(&mat_line, w);
	pt2->m[0] = border->x1;
	pt2->m[1] = border->y0;
	draw_line3(&mat_line, w);
	pt1->m[0] = border->x1;
	pt1->m[1] = border->y1;
	draw_line3(&mat_line, w);
	pt2->m[0] = border->x0;
	pt2->m[1] = border->y1;
	draw_line3(&mat_line, w);
	matrix_free(&pt1);
	matrix_free(&pt2);
}

int		mouse_in_border(t_border *border, t_matrix *mouse)
{
	(void)border;
	(void)mouse;
	if (mouse->m[0] < border->x0 || mouse->m[0] > border->x1
			|| mouse->m[1] < border->y0 || mouse->m[1] > border->y1)
		return (0);
	return (1);
}

void	draw_the_2_border(t_env *e)
{
	t_matrix	*color;
	if (!(color = tsl_to_rvb_new(120, (mouse_in_border(&((e->border_b)), e->param->mouse) ? 0.8 : 0.3 ), 0.8)))
		return ;
	draw_border(e->param, &(e->border_b), color);
	if (!(color = tsl_to_rvb_new(250, (mouse_in_border((&(e->border_t)), e->param->mouse) ? 0.8 : 0.3 ), 0.8)))
		return ;
	draw_border(e->param, &(e->border_t), color);
	matrix_free(&color);
}

/*
**	si on a trouver un clique dans un cadre, on envoie le polygone assosier
**	mais ca c'est cool que pour quand on clique
**	le mieux ca serrait de reperer quand on entre et 
**		on sort 				-> 	on suprime le dernier maillon
**		on rentre				->	on ajoute le maillon courrant
**		on bouge 				->	on modifi le maillon courrent
**
**		clique ET dans cadre	->	on copy le dernier maillon et on le met en avant dernier
*/

int		check_border_io(t_env *e, t_win *w, t_border *b)
{
	(void)e;
	//	La on veux juste saoir si on sor ou si on rentre
	if (mouse_in_border(b, w->mouse) && !mouse_in_border(b, w->prev_mouse))
		return (1);//dprintf(1, "on rentre\n");
	if (!mouse_in_border(b, w->mouse) && mouse_in_border(b, w->prev_mouse))
		return (-1);//dprintf(1, "on sort\n");
	return (0);
}

//	(1)	on actualise la fin avec le node de la souri (on le met ou on l'enleve)
//		==>	juste pour les mouvement de la souri
void	actu_polygone_io(t_env *e, t_win *w)
{
	int	ret;

	if (!e->actif)
		e->actif = creat_node_fv(0, w->mouse, vect_new_vertfd(255, 255, 255));
	if ((ret = check_border_io(e, w, &(e->border_b))))
		(ret > 0) ? polygone_push_back(&(e->base_model), e->actif)
			: polygone_forget_last(&(e->base_model));
	if ((ret = check_border_io(e, w, &(e->border_t))))
		(ret > 0) ? polygone_push_back(&(e->trans_model), e->actif)
			: polygone_forget_last(&(e->trans_model));
}

//	la si on a un clique ET au'on est en param on push beforback
void	complet_polygone(t_win *w)
{
	if (ft_strcmp(w->name, "param"))
		return ;
	if (mouse_in_border(&(w->e->border_b), w->mouse))
		polygone_push_befor_last(&(w->e->base_model), copy_node(w->e->actif, 0));
	if (mouse_in_border(&(w->e->border_t), w->mouse))
		polygone_push_befor_last(&(w->e->trans_model), copy_node(w->e->actif, 0));
}

//	meintenant il faut a chaque transformation des model redefinir 

/*
void	redefine_trans(t_polygone *mult)
{
	if (!mult)
		return ;
	polygone_destroy(&(e->transform));
	e->transform = trans_controle(mult);
}
*/

//	La on va unpeu tout faire d'un coup
void	redefine_base(t_polygone *new_base, t_border *from, t_win *to)
{
	double	coef_x;
	double	coef_y;
	t_polygone	*tmp;

	if (!new_base)
		return ;
	polygone_destroy(&(to->e->base));
	to->e->base = NULL;
	coef_x = (to->size_x) / (from->x1 - from->x0);
	coef_y = (to->size_y) / (from->y1 - from->y0);
	while (new_base)
	{
		tmp = copy_node(new_base, 0);
		tmp->pos->m[0] = (tmp->pos->m[0] - from->x0) * coef_x;
		tmp->pos->m[1] = (tmp->pos->m[1] - from->y0) * coef_y;
		polygone_push_back(&(to->e->base), tmp);
		new_base = new_base->next;
	}
}

/*
void	add_(t_polygone *poly, t_matrix *pos)
{
	
}
*/
