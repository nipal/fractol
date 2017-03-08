/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sliding_button.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 04:46:43 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/05 04:52:23 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

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

int			select_button(t_win *w, t_slider **tab)
{
	double	dist;
	double	r[3];
	int		i;
	double	min;
	int		id_min;

	id_min = -1;
	min = -1;
	i = 0;
	while (tab[i / 2])
	{
		dist = tab[i / 2]->border->x1 - tab[i / 2]->border->x0;
		r[0] = (w->mouse->m[0] - (dist * (((i % 2) == 0) ? tab[i / 2]->v1
						: tab[i / 2]->v2)) - tab[1 / 2]->border->x0);
		r[1] = (w->mouse->m[1] - (((i / 2) + 1) * (tab[1 / 2]->border->y0
						+ tab[1 / 2]->border->y1) / 2));
		r[2] = sqrt(r[0] * r[0] + r[1] * r[1]);
		if (((r[2] <= min || min < 0) && r[2]
	<= ((fabs((double)(tab[i / 2]->border->y1 - tab[i / 2]->border->y0)) / 2)))
		&& (id_min = i) >= 0)
			min = r[2];
		i++;
	}
	return (id_min);
}

void		scroling_button(t_win *w, t_slider *slide, int pt)
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
