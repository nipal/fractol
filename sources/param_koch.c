/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_koch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 13:27:00 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/10 04:59:21 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


int	reset_base(t_env *e)
{
	e->base_add = 0;
//	if (e->base_model && e->base_model != e->actif)
//	{
	polygone_destroy(&(e->base_model));
	polygone_destroy(&(e->base));
	e->base_model = e->actif;
//	}
	//	il faudra aussi reinitialiser la base (en mode scaling)
	return (1);
}

int	reset_transform(t_env *e)
{
	e->trans_add = 0;
//	if (e->trans_model && e->trans_model != e->actif)
//	{
	polygone_destroy(&(e->trans_model));
	polygone_destroy(&(e->transform));
	e->trans_model = e->actif;
//	}
	//	il faudra aussi actualiser le truc de transformation
	return (1);
}

//	la on va faire un truc pas super modulable mais faice a utiilser
int	actu_base(t_env *e, t_polygone *src)
{
	polygone_destroy(&(e->base));
	e->base = scale_segment(src, &(e->border_b), e->fractal);
	print_fractal(e);
//	draw_simple_polygone(e->fractal, e->base);
	//	
	return (1);
}

int	actu_transform(t_env *e, t_polygone *src)
{
	polygone_destroy(&(e->transform));
	e->transform = transform(src);
	print_fractal(e);
//	draw_simple_polygone(e->fractal, e->base);
	return (1);
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
	//	oui
}

void	draw_border(t_win *w, t_border *border, t_matrix *color)
{
	t_matline	mat_line;
	t_matrix	*pt1;
	t_matrix	*pt2;

	if (!(pt1 = vect_new_vertfd(border->x0, border->y0, 0))
			|| !(pt2 = vect_new_vertfd(border->x0, border->y1, 1)))
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
	if (!border || ! mouse || mouse->m[0] < border->x0 || mouse->m[0] > border->x1
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
	if ((ret = check_border_io(e, w, &(e->border_b))) > 0 && (e->base_add) == 0)
		polygone_push_back(&(e->base_model), e->actif);
	else if (ret < 0 && (e->base_add) == 0)
		polygone_forget_last(&(e->base_model));
	if ((ret = check_border_io(e, w, &(e->border_t))) > 0 && (e->trans_add) == 0)
		polygone_push_back(&(e->trans_model), e->actif);
	else if (ret < 0 && (e->trans_add) == 0)
		polygone_forget_last(&(e->trans_model));
}

//	la si on a un clique ET au'on est en param on push beforback
void	complet_polygone(t_win *w)
{
	if (ft_strcmp(w->name, "param"))
		return ;
	if (mouse_in_border(&(w->e->border_b), w->mouse) && (w->e->base_add) == 0)
		polygone_push_befor_last(&(w->e->base_model), copy_node(w->e->actif, 0));
	if (mouse_in_border(&(w->e->border_t), w->mouse) && (w->e->trans_add) == 0)
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
	coef_x = (to->size_x ) / (from->x1 - from->x0);
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

/*
**	on va adapter les coordoner des segment dans la fenetre a la fenetre de rendu
*/

t_polygone	*scale_segment(t_polygone *src, t_border *border, t_win *w)
{
	t_polygone	*begin_new;
	t_polygone	*new_node;
	double		scale_x;
	double		scale_y;

	begin_new = NULL;
	scale_x = 1.0 * w->size_x / (1.0 * border->x1 - border->x0);
	scale_y = 1.0 * w->size_y / (1.0 * border->y1 - border->y0);
	while (src)
	{
		if (!(new_node = copy_node(src, 0)))
			return (NULL);
		new_node->pos->m[0] = (new_node->pos->m[0] - border->x0) * scale_x;
		new_node->pos->m[1] = (new_node->pos->m[1] - border->y0) * scale_y;

//		new_node->col->m[0] = 255;
//		new_node->col->m[1] = 255;
//		new_node->col->m[2] = 255;
		polygone_push_back(&begin_new, new_node);
		src = src->next;
	}
	return (begin_new);
}

//	on va juste commencer par afficher un truc degeulasse pour le debug
//

/*
t_polygone	*get_closer_node(t_polygone *beg, t_matrix *mouse, double min_dist)
*/

double	height_circle(double r, double x)
{
	if (x <= r)
		return (sqrt(r * r - x * x));
	return (0);
}

void	print_circle2(t_matrix *mid, t_matrix *col, double r, t_win *w)
{
	t_matrix	*pt1;
	t_matrix	*pt2;
	t_matrix	*mat_line;
	t_matrix	*c2;
	double		h[3];

	c2 = NULL;
	if (!mid || !w || !(pt1 = matrix_init(1, 3))
		|| (!col && !(c2 = vect_new_vertfd(180, 30, 30)))
		|| !(pt2 = matrix_init(1, 3)))
		return ;
	col = (col) ? col : c2;
//	dprintf(1, "a0\n");
	h[0] = 0;
	h[2] = mid->m[0] - r;
	while (h[2] < mid->m[0] + r)
	{
		pt1->m[0] = h[2];
		pt2->m[0] = h[2] + 1;
		h[0] = height_circle(r, h[2] - mid->m[0]);
		h[1] = height_circle(r, h[2] - mid->m[0] + 1);
		pt1->m[1] = mid->m[1] + h[0];
		pt2->m[1] = mid->m[1] + h[1];
		mat_line = init_mat_line(pt1, pt2, col, col);
		draw_line2(w, mat_line);
		matrix_free(&mat_line);
		pt2->m[1] -= 2 * h[1];
		pt1->m[1] -= 2 * h[0];
		mat_line = init_mat_line(pt1, pt2, col, col);
		draw_line2(w, mat_line);
		matrix_free(&mat_line);
		h[2]++;
//		dprintf(1, "bbb-> %.1f\n", h[2]);
	}
//	dprintf(1, "a10\n");
//	dprintf(1, "****************************************************************************\n");
	matrix_free(&c2);
}


int		move_the_node(t_env *e, t_polygone *seg)
{
	t_polygone *node;

	if (seg && (node = get_closer_node(seg, e->param->prev_mouse, e->r_select)))
	{
		node->pos->m[0] = e->param->mouse->m[0];
		node->pos->m[1] = e->param->mouse->m[1];
	}
	return (1);
}

/*
void		print_circle2(t_matrix *mid, t_matrix *col, double r, t_win *w)
void		translate_node(t_env *e, t_polygone *poly)
t_polygone	*get_closer_node(t_polygone *beg, t_matrix *mouse, double min_dist)


void	color_closer_node(t_env *e)
{
	t_matrix	*node;

	//	transform PRIO SUR base
	node = get_closer_node(e->);
}
*/


/*
	mat_line = init_mat_line(pt1->m, pt2->m, col->m, col->m);
	draw_line2(w, mat_line);
	matrix_free(&mat_line);
*/
//	
