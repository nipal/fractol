/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 03:54:36 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 23:54:42 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		is_visible(t_matrix **corner, t_matrix *pt)
{
	int		i;
	double	result;

	i = 0;
	if (pt->m[Z] < 0)
		return (0);
	while (i < 4)
	{
		if ((result = matrix_dot_product(corner[i], pt)) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	draw_link(t_env *e, t_cam *cam, t_matrix **pt)
{
	if (pt[0] && is_visible(cam->corner, pt[0]))
	{
		if (pt[1] && pt[1]->m[Z] > 0)
			draw_line(e, init_mat_line(pt[0], pt[1], pt[4], pt[5]));
		if (pt[2] && pt[2]->m[Z] > 0)
			draw_line(e, init_mat_line(pt[0], pt[2], pt[4], pt[6]));
		if (pt[3] && pt[3]->m[Z] > 0)
			draw_line(e, init_mat_line(pt[0], pt[3], pt[4], pt[7]));
	}
}

void	free_point(t_matrix ***pt, int size_x, int size_y)
{
	int					i;
	int					j;

	j = 0;
	while (j < size_y)
	{
		i = 0;
		while (i < size_x)
		{
			matrix_free(pt[j] + i);
			i++;
		}
		j++;
	}
}

int		init_color(t_matrix **point)
{
	int	i;

	i = 4;
	while (i < 8)
	{
		if (!(point[i] = matrix_init(1, 4)))
			return (0);
		i++;
	}
	return (1);
}

void	print_map(t_env *e, t_cam *cam, t_matrix ***map)
{
	int					i;
	int					j;
	static	t_matrix	**point = NULL;

	if (!cam || !map || !*map || !**map)
		return ;
	j = 0;
	if ((!point && (!(point = (t_matrix**)malloc(sizeof(t_matrix*) * 8))
					|| !init_color(point))))
		return ;
	while (j < e->size_map_y)
	{
		i = 0;
		while (i < e->size_map_x)
		{
			i++;
		}
		j++;
	}
}
