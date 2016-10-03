/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_adapt_to_cam.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 03:57:44 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 04:12:04 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "fdf.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

void		conique_adapte(t_matrix *vect)
{
	double	norme;

	norme = vect->m[2] / 500;
	vect->m[0] /= norme;
	vect->m[1] /= norme;
}

int			is_out(t_matrix *vect, t_env *e)
{
	if (vect->m[0] < e->ecr_x * -0.5
		|| vect->m[0] > e->ecr_x * 0.5
		|| vect->m[1] < e->ecr_y * -0.5
		|| vect->m[1] > e->ecr_y * 0.5)
		return (1);
	return (0);
}

int			ato(t_matrix *vect1, t_matrix *vect2, t_env *e)
{
	if (!vect1 || !vect2 || !e
		|| ((is_out(vect1, e) && is_out(vect2, e))
		|| vect1->m[2] < 1 || vect2->m[2] < 1))
		return (1);
	return (0);
}

t_matrix	*base_change_scalar(t_cam *cam, t_matrix *vect)
{
	t_matrix	*tmp;

	if (!(tmp = matrix_init(1, 3)))
		return (NULL);
	tmp->m[0] = matrix_dot_product(cam->base[0], vect);
	tmp->m[1] = matrix_dot_product(cam->base[1], vect);
	tmp->m[2] = matrix_dot_product(cam->base[2], vect);
	return (tmp);
}

void		base_change(t_env *e, t_cam *c, t_matrix ***map, t_matrix *rot_cam)
{
	int			i;
	int			j;
	t_matrix	*tmp;
	t_matrix	*rot_obj;

	if (!(rot_obj = set_rotate(e->rot_x, e->rot_y, e->rot_z))
		|| !(rot_cam = set_rotate(c->rot->m[0], c->rot->m[1], c->rot->m[2])))
		return ;
	j = -1;
	while (++j < e->size_map_y)
	{
		i = -1;
		while (++i < e->size_map_x)
		{
			tmp = matrix_product(rot_obj, map[j][i]);
			matrix_free(map[j] + i);
			matrix_sub_in(tmp, c->pos, tmp);
			map[j][i] = base_change_scalar(c, tmp);
			matrix_free(&tmp);
			conique_adapte(map[j][i]);
		}
	}
	matrix_free(&rot_obj);
	matrix_free(&rot_cam);
}
