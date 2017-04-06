/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_win.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 18:47:38 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/17 18:05:08 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_win		*window_init(t_env *e, int size_x, int size_y, char *name)
{
	t_win	*w;

	if (!name)
		name = "new w";
	if (!e || !(size_x > 0 && size_y > 0)
			|| !(w = (t_win*)ft_memalloc(sizeof(t_win)))
			|| !(w->win = mlx_new_window(e->mlx, size_x, size_y, name))
			|| !(w->img = mlx_new_image(e->mlx, size_x, size_y))
			|| !(w->data = (t_pix*)mlx_get_data_addr(w->img, &(w->depth)
					, &(w->size_line), &(w->endian)))
			|| !(w->name = ft_strdup(name)))
		return (NULL);
	init_win_event(w);
	w->cursor_on = 1;
	w->cam_ang_incr = 5 * ((2 * M_PI) / 360);
	w->e = e;
	w->size_x = size_x;
	w->size_y = size_y;
	return (w);
}

int	ft_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (1);
}

int			window_destroy(t_win **w)
{
	if (!w || !*w)
		return (0);
	ft_free((void**)&(w[0]->name));
	ft_free((void**)w);
	return (1);
}

void		init_win_event(t_win *w)
{
	mlx_hook(w->win, KEY_PRESS, (1 << 24) - 1, press_key, w);
	mlx_hook(w->win, KEY_RELEASE, (1 << 24) - 1, release_key, w);
	mlx_hook(w->win, BUTTON_PRESS, (1 << 24) - 1, press_cursor, w);
	mlx_hook(w->win, BUTTON_RELEASE, (1 << 24) - 1, release_cursor, w);
	mlx_hook(w->win, MOTION_NOTIFY, (1 << 24) - 1, motion_cursor, w);
}


