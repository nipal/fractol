/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_win.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 18:47:38 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/18 12:23:41 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <mlx.h>

void	describe_window(t_win *w)
{
	dprintf(1, "\n\nwindow:	%s\n", (w? "OK": "null"));
	dprintf(1, "win:		%s\n", (w->win? "OK": "null"));
	dprintf(1, "env:		%s\n", (w->e? "OK": "null"));
	dprintf(1, "name:		%s\n", (w->name? w->name: "null"));
	dprintf(1, "data:		%s\n", (w->data? "OK": "null"));
	dprintf(1, "z_buff:		%s\n", (w->z_buff? "OK": "null"));
	dprintf(1, "is_z_buff:	%s\n", (w->is_z_buff? "OK": "null"));
	dprintf(1, "size_x:		%d\n", w->size_x);
	dprintf(1, "size_y:		%d\n", w->size_y);
}

t_win	*window_init(t_env *e, int size_x, int size_y, char *name)
{
	t_win	*window;

	if (!name)
		name = "new window";//ft_strdup("new window");
	if (!e || !(size_x > 0 && size_y > 0)
			|| !(window = (t_win*)malloc(sizeof(t_win)))
			|| !(window->win = mlx_new_window(e->mlx, size_x, size_y, name))
			|| !(window->data = (t_pix*)mlx_new_image(e->mlx, size_x, size_y))
			|| !(window->name = ft_strdup(name))
			|| !(window->z_buff = (double*)malloc(sizeof(double) * size_x * size_y)))
		return (NULL);
	window->e = e;
	window->is_z_buff = 1;	
	window->size_x = size_x;
	window->size_y = size_y;
//	describe_window(window);
	return (window);
}

int		window_destroy(t_env *e, t_win **window)
{
	if (!e || !window || !*window)
		return (0);	
//	free((*window)->z_buff);
//	free((*window)->data);
//	window[0]->win;
//	window[0]->win;
//	mlx_destroy_image(e->mlx, window[0]->data);
//	mlx_destroy_window(e->mlx, window[0]->win);
	window[0] = NULL;
	return (1);
}


/*

void	*mlx_new_image(void *mlx_ptr,int width,int height);
int	mlx_destroy_window(void *mlx_ptr, void *win_ptr);
int	mlx_destroy_image(void *mlx_ptr, void *img_ptr);

typedef	struct	s_win
{
	int			size_x;
	int			size_y;
}				t_win;


 * */
