/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_win.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 18:47:38 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/18 20:33:10 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <mlx.h>

t_win		*window_init(t_env *e, int size_x, int size_y, char *name)
{
	t_win	*w;

	if (!name)
		name = "new w";
	if (!e || !(size_x > 0 && size_y > 0)
			|| !(w = (t_win*)malloc(sizeof(t_win)))
			|| !(w->mouse = matrix_init(1, 3))
			|| !(w->prev_mouse = matrix_init(1, 3))
			|| !(w->win = mlx_new_window(e->mlx, size_x, size_y, name))
			|| !(w->img = mlx_new_image(e->mlx, size_x, size_y))
			|| !(w->data = (t_pix*)mlx_get_data_addr(w->img, &(w->depth)
					, &(w->size_line), &(w->endian)))
			|| !(w->name = ft_strdup(name))
			|| !(w->z_buff = (double*)malloc(sizeof(double) * size_x * size_y)))
		return (NULL);
	w->e = e;
	w->is_z_buff = 1;
	w->size_x = size_x;
	w->size_y = size_y;
	w->mx = 0;
	w->my = 0;
	return (w);
}

static	int	ft_free(void **ptr)
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
	ft_free((void**)&(w[0]->z_buff));
	ft_free((void**)&(w[0]->name));
	ft_free((void**)&(w[0]->mouse));
	ft_free((void**)&(w[0]->prev_mouse));
	ft_free((void**)w);
	return (1);
}
