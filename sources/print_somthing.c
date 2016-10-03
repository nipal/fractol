/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_somthing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:50:43 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 22:51:43 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fdf.h"
#include <stdio.h>

void		vectpx_to_img(t_env *e, t_matrix *pos_color)
{
	int	x;
	int	y;
	int	r;
	int	g;
	int	b;

	x = (int)pos_color->m[0];
	y = (int)pos_color->m[1];
	x += SIZE_Y / 2;
	y += SIZE_X / 2;
	if (x < 0 || x >= e->ecr_x || y < 0 || y >= e->ecr_y || pos_color->m[2] < 0
		|| (pos_color->m[2] >
			e->z_buffer[x + y * e->ecr_x] && e->z_buffer[x + y * e->ecr_x]))
		return ;
	e->z_buffer[x + y * e->ecr_x] = pos_color->m[2];
	r = (int)pos_color->m[3] + 0.5;
	g = (int)pos_color->m[4] + 0.5;
	b = (int)pos_color->m[5] + 0.5;
	e->data[y * e->size_line + x * 4 + 2] = r;
	e->data[y * e->size_line + x * 4 + 1] = g;
	e->data[y * e->size_line + x * 4] = b;
}

void		string_put(char *s1, char *s2, t_env *e, int y)
{
	char *str;

	str = ft_strnew(60);
	str = ft_strcpy(str, s1);
	str = ft_strcat(str, s2);
	mlx_string_put(e->mlx, e->win, 1200, y, 0xFFFF00, str);
	free(str);
}

void		print_state(t_env *e)
{
	char	*str;

	string_put("Zoom : ", ft_itoa(e->zoom), e, 50);
	(e->proj == 0) ? str = ft_strdup("isometric") : (void)e->proj;
	(e->proj == 1) ? str = ft_strdup("parallel") : (void)e->proj;
	(e->proj == 2) ? str = ft_strdup("conic") : (void)e->proj;
	string_put("Projection : ", str, e, 60);
	ft_strdel(&str);
	string_put("Offset X : ", ft_itoa(e->decalx), e, 70);
	string_put("Offset Y : ", ft_itoa(e->decaly), e, 80);
	str = ft_strnew(20);
	str = ft_strcat(str, " R = ");
	str = ft_strcat(str, ft_itoa((int)e->r));
	str = ft_strcat(str, " G = ");
	str = ft_strcat(str, ft_itoa((int)e->g));
	str = ft_strcat(str, " B = ");
	str = ft_strcat(str, ft_itoa((int)e->b));
	string_put(str, "", e, 90);
	ft_strdel(&str);
}

/*
** 	ici il faudrait stoquer les dimetion maximale de la map
** 	on a deja le max x et y il maque le max et le min en z
*/

t_matrix	*get_max_zdim(int **map, int size_x, int size_y)
{
	int			i;
	int			j;
	t_matrix	*z_dim;

	if (!(z_dim = matrix_init(2, 1)))
		return (NULL);
	z_dim->m[0] = map[0][0];
	z_dim->m[1] = map[0][0];
	j = 0;
	while (j < size_y)
	{
		i = 0;
		while (i < size_x)
		{
			if (map[j][i] < z_dim->m[0])
				z_dim->m[0] = map[j][i];
			if (map[j][i] > z_dim->m[1])
				z_dim->m[1] = map[j][i];
			i++;
		}
		j++;
	}
	return (z_dim);
}

t_matrix	*finishe_color(t_env *e, double *pak)
{
	t_matrix	*color;

	if (e->z_max != 0 && e->z_min < 0)
		pak[0] = 255 * pak[3] / e->z_max;
	else if (pak[2] != 0)
		pak[0] = 255 * pak[3] / pak[2];
	else
		pak[0] = 255;
	pak[1] = 255 - pak[0];
	if (!(color = vect_new_vertfd(pak[0], pak[1], 0)))
		return (NULL);
	return (color);
}
