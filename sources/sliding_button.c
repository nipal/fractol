/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sliding_button.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 09:54:54 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/10 11:41:34 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

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

t_slider	**init_tab_slider(int nb, t_border *inside, t_matrix *color
		, double margin)
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
	while (++i < nb)
	{
		bslide.y0 = deltay * (i + 1) + margin / 2;
		bslide.y1 = deltay * (i + 1) - margin / 2;
		if (!(tabs_slide[i] = init_slider(color, &bslide)))
			return (NULL);
	}
	(!(tabs_slide[i] = NULL) && was_null) ? matrix_free(&color) : 0;
	return (tabs_slide);
}

int			init_the_sliders(t_win *w, t_border *the_other)
{
	double		margin;
	t_border	border;

	if (!w || !the_other)
		return (0);
	margin = 4 * (w->size_y - the_other->y1);
	border.y0 = margin;
	border.y1 = the_other->y0 - margin;
	border.x0 = margin;
	border.x1 = w->size_x / 2;
	if (!(w->e->sliders = init_tab_slider(w->e->nb_sliders, &border
					, NULL, margin)))
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

int			tab_slider_free(t_slider ***tab, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		slider_free(*(tab + i));
		i++;
	}
	return (1);
}
