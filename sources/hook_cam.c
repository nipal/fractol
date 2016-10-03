/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 22:53:23 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 23:46:06 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fdf.h"

int		increm_dir_cam(t_env *e)
{
	t_matrix	*tmp;
	t_matrix	*rot;
	t_matrix	*dir;

	if (!(rot = set_rotate(e->rot_x, e->rot_y, e->rot_z))
		|| (dir = matrix_put_in_new(0, 0, 1, 0)))
		return (0);
	tmp = matrix_product(rot, dir);
	matrix_free(&dir);
	dir = tmp;
	matrix_scalar_product(dir, 0.01 * e->speed);
	e->cam->pos->m[X] += dir->m[X];
	e->cam->pos->m[Y] += dir->m[Y];
	e->cam->pos->m[Z] += dir->m[Z];
	matrix_free(&rot);
	matrix_free(&dir);
	return (1);
}

void	increm_pos_cam(t_env *e)
{
	t_matrix	*move;

	if (!(move = matrix_scalar_product_new(e->cam->base[2], e->speed)))
		return ;
	matrix_add_in(e->cam->pos, move, e->cam->pos);
	matrix_free(&move);
}

int		reset_base_cam(t_cam *cam)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		matrix_free(cam->base + i);
		if (!(cam->base[i] = vect_new_vertfd(i == 0, i == 1, i == 2)))
			return (0);
		i++;
	}
	return (1);
}

void	incr_rotation(t_matrix *rot, t_env *e, double deg)
{
	rot->m[2] -= (e->key.rot_cam_z2 == 1) ? deg : 0;
	rot->m[2] += (e->key.rot_cam_z1 == 1) ? deg : 0;
	rot->m[1] -= (e->key.rot_cam_x2 == 1) ? deg : 0;
	rot->m[1] += (e->key.rot_cam_x1 == 1) ? deg : 0;
	rot->m[0] -= (e->key.rot_cam_y2 == 1) ? deg : 0;
	rot->m[0] += (e->key.rot_cam_y1 == 1) ? deg : 0;
}

void	manage_cam_rot(t_env *e)
{
	int					i;
	t_matrix			*tmp;
	static	t_matrix	*rot = NULL;
	t_matrix			*mat_rot;
	static	double		deg = 0.06;

	if (!(reset_base_cam(e->cam)))
		return ;
	if (!rot && !(rot = matrix_init(1, 3)))
		return ;
	if (!(mat_rot = set_rotate(rot->m[0], rot->m[1], rot->m[2])))
		return ;
	incr_rotation(rot, e, deg);
	i = -1;
	while ((++i < 3) || (matrix_free(&mat_rot)))
	{
		if (!(tmp = matrix_product(mat_rot, e->cam->base[i])))
			return ;
		matrix_free(e->cam->base + i);
		e->cam->base[i] = tmp;
	}
}
