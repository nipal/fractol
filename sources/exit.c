/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 12:17:52 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/30 04:56:31 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fdf.h"

void	free_map(t_matrix ****map, t_env *e)
{
	int	i;
	int	j;

	if (!e
		|| !map
		|| !(*map)
		|| !(**map)
		|| !(***map))
		return ;
	j = 0;
	while (j < e->size_map_y)
	{
		i = 0;
		while (i < e->size_map_x)
		{
			matrix_free((*map)[j] + i);
			i++;
		}
		free((*map)[j]);
		(*map)[j] = NULL;
		j++;
	}
	free(*map);
	*map = NULL;
}

int		free_int_map(t_env *e)
{
	int	j;

	j = 0;
	while (j < e->size_map_y)
	{
		free(e->map[j]);
		j++;
	}
	free(e->map);
	return (0);
}

int		free_cam(t_env *e)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		matrix_free(e->cam->base + i);
		i++;
	}
	matrix_free(&(e->cam->pos));
	matrix_free(&(e->cam->dir));
	matrix_free(&(e->cam->rot));
	free(e->cam);
	return (0);
}

int		ft_exit(t_env **e)
{
	free((*e)->z_buffer);
	free_int_map(*e);
	free_map(&((*e)->color_map), *e);
	free_cam(*e);
	mlx_destroy_image((*e)->mlx, (*e)->img);
	mlx_destroy_window((*e)->mlx, (*e)->win);
	exit(0);
	return (0);
}
