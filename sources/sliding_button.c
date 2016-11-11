/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sliding_button.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 09:54:54 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/10 15:22:22 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

void	paint_circle(t_matrix *mid, t_matrix *col, double r, t_win *w)
{
	t_matrix	*pt1;
	t_matrix	*pt2;
	t_matrix	*mat_line;
	t_matrix	*c2;
	double		h[3];

	c2 = NULL;
	if (!mid || !w || !(pt1 = matrix_init(1, 3))
		|| (!col && !(c2 = vect_new_vertfd(50, 100, 70)))
		|| !(pt2 = matrix_init(1, 3)))
	{
//		dprintf(1, "go fuck yourself\n");
		return ;
	}
	col = (col) ? col : c2;
//	dprintf(1, "a0\n");
//	h[0] = 0;
//	dprintf(1, "r:%f\n", r);
//	r = 20;
	h[2] = mid->m[0] - r;
	while (h[2] < mid->m[0] + r)
	{
//		dprintf(1, "yes i::%f\n", (h[2] - r));
		pt1->m[0] = h[2];
		pt2->m[0] = h[2];
		h[0] = height_circle(r, h[2] - mid->m[0]);
//		h[1] = height_circle(r, h[2] - mid->m[0]);
		pt1->m[1] = mid->m[1] + h[0];
		pt2->m[1] = mid->m[1] - h[0];
		mat_line = init_mat_line(pt1, pt2, col, col);
		draw_line2(w, mat_line);
/*	
		matrix_free(&mat_line);
		pt2->m[1] -= 2 * h[1];
		pt1->m[1] -= 2 * h[0];
		mat_line = init_mat_line(pt1, pt2, col, col);
		draw_line2(w, mat_line);
		matrix_free(&mat_line);
		*/
		h[2]++;
	}
	matrix_free(&c2);
}


double	get_rmax(t_slider *s)
{
	double	to_return;

	to_return = fabs((double)(s->border->y1 - s->border->y0)) / 2;
	return (to_return);
}

t_matrix	*get_button_pos(t_slider *s, int nb)
{
	t_matrix	*pos;
	double		length;
	double		mid_y;

	if (!(pos = matrix_init(1, 3)))
		return (NULL);
	length = fabs(((double)(s->border->x1 - s->border->x0)));
	mid_y = ((double)(s->border->y1 + s->border->y0) / 2);
	pos->m[0] = s->border->x0 + ((nb == 0) ? s->v1 : s->v2) * length;
	pos->m[1] = mid_y;
	pos->m[2] = 0;
	return (pos);
}	


//	on dessine une ligne, un cercle.
//	on fait scroller le cercle sur la bar avec deux limite
int		select_button(t_win *w, t_slider **tabs)
{
	double	dist;
	double	r[3];
	int		i;
	double	min;
	int		id_min;

	id_min = -1;
	min	= -1;
//	r_max = ABS(w->border->y1 - s->border->y0);
	i = 0;
	while (tabs[i / 2])
	{
		dist = tabs[i / 2]->border->x1 - tabs[i / 2]->border->x0;
		r[0] = (w->mouse->m[0] - (dist * (((i % 2) == 0) ? tabs[i / 2]->v1 : tabs[i / 2]->v2)) - tabs[1 / 2]->border->x0);
		r[1] = (w->mouse->m[1] - (((i/ 2) + 1) * (tabs[1 / 2]->border->y0 + tabs[1 / 2]->border->y1) / 2));
		r[2] = sqrt(r[0] * r[0] + r[1] * r[1]);
		if ((r[2] <= min || min < 0) && r[2] <= get_rmax(tabs[i / 2]))
		{
			min = r[2];
			id_min = i;
		}
		i++;
	}
	return (id_min);
}

/*
**	la on met juste a jour la valeur d'un poid en fonction de la souri
**		on appelle cette fonction en sachant deja qui atteindre
*/
void	scroling_button(t_win *w, t_slider *slide, int pt)
{
	double	dist;

	dist = slide->border->x1 - slide->border->x0;
	if (pt == 0)
	{
		slide->v1 = -(slide->border->x0 - w->mouse->m[0]) / dist;
		slide->v1 = (slide->v1 < 0) ? 0 : slide->v1;
		slide->v1 = (slide->v1 > 1) ? 1 : slide->v1;
	}
	if (pt == 1)
	{
		slide->v2 = -(slide->border->x0 - w->mouse->m[0]) / dist;
		slide->v2 = (slide->v2 < 0) ? 0 : slide->v2;
		slide->v2 = (slide->v2 > 1) ? 1 : slide->v2;
	}
}

void	draw_slider(t_win *w, t_slider *s)
{
	double		dist;
	double		r;
	t_matrix	*mat_line;
	t_matrix	*pt1;
	t_matrix	*pt2;

	if (!(pt1 = vect_new_vertfd(s->border->x0, 0.5 * (s->border->y0 + s->border->y1), 0))
		|| !(pt2 = vect_new_vertfd(s->border->x1, 0.5 * (s->border->y0 + s->border->y1), 0))
		|| !(mat_line = init_mat_line(pt1, pt2, s->color, s->color)))
		return ;
	dist = abs(s->border->x1 - s->border->x0);
	r = s->border->y0 - s->border->y1;
	draw_line2(w, mat_line);
	pt1->m[0] = s->v1 * dist + s->border->x0;
	pt2->m[0] = s->v2 * dist + s->border->x0;
	paint_circle(pt1, s->color, r * 0.7, w);
	paint_circle(pt2, s->color, r * 0.7, w);
}

void	draw_the_sliders(t_win *w, t_slider **sliders)
{
	int	i;

	i = 0;
	while (sliders[i])
	{
		draw_slider(w, sliders[i]);
		i++;
	}
}

/*
**	On fait une copy de tout les parametre
*/
t_slider	*init_slider(t_matrix *color, t_border *b)
{
	t_slider	*slider;

	if (!(slider = (t_slider*)malloc(sizeof(t_slider)))
		|| !(slider->border = malloc(sizeof(t_slider)))
		|| ((!color) ? !(color = vect_new_vertfd(50, 100, 70))
			: !(color = matrix_copy(color))))
		return (NULL);
	slider->v1 = 0;
	slider->v2 = 1;
	slider->color = color;
	ft_memcpy(slider->border, b, sizeof(t_border));
	return (slider);
}

t_slider	**init_tab_slider(int nb, t_border *inside, t_matrix *color, double margin)
{
	int			i;
	int			was_null;
	t_slider	**tabs_slide;
	t_border	bslide;
	double		deltay;

	was_null = 0;
	if (!(inside)
		|| (!color && (!(was_null = 1)
				&& !(color = vect_new_vertfd(120, 120, 120))))
		|| !(tabs_slide = malloc(sizeof(t_slider) * (nb + 1))))
		return (NULL);
	bslide.x0 = inside->x0 + margin / 2;
	bslide.x1 = inside->x1 - margin / 2;
	deltay = abs(inside->y1 - inside->y0) / 3;
	i = -1;
	dprintf(1, "i:%d	nb:%d\n", i, nb);
	while (++i < nb)
	{
		dprintf(1, "i:%d", i);
		bslide.y0 = deltay * (i + 1) + margin / 2;
		bslide.y1 = deltay * (i + 1) - margin / 2;
		if (!(tabs_slide[i] = init_slider(color, &bslide)))
			return (NULL);
	}
	tabs_slide[i] = NULL;
	return (tabs_slide);
}

/*
**	la c'est une fcontion unpeu salle pck auttan ca fera un peu d'overlap
*/
int			init_the_sliders(t_win *w, t_border *the_other)
{
	double		margin;
	t_border	border;

	if (!w || !the_other)
		return (0);
	margin = 4 * (w->size_y - the_other->y1);
	//	on prend juste 1/3 sur x
	// on init les border de dedans	--> efait ca va etre plus simple
	border.y0 = margin;
	border.y1 = the_other->y0 - margin;
	border.x0 = margin;
	border.x1 = w->size_x / 2;
	if (!(w->e->sliders = init_tab_slider(w->e->nb_sliders, &border, NULL, margin)))
		return (0);	
	return (1);
}

int			slider_free(t_slider **slider)
{
	if (slider)
	{
		if (*slider)
		{
			matrix_free(&((*slider)->color));
			free((*slider)->border);
			(*slider)->border = NULL;
			free(*slider);
			*slider = NULL;
		}
	}
	return (1);
}

/*
**	il manque le fonctionement qui li tou ca
*/

/*
	BUTTON DOWN	(1)	--> on verifi si on peu set un id_scrol
	BUTTON UP  	(1)	--> on init id_scrol a -1
	
	(tour de boucle)
	=> (id_scrol >= 0)
		on set la position du scrol avec l'id qui corespond
	=> on les dessinne tous

		
*/
