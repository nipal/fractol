/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 09:32:11 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 19:30:11 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**void	set_windir(t_matrix **corner, double fov_x, double fov_y)
**{
**	(void)corner;
**	(void)fov_x;
**	(void)fov_y;
**
**	int		i;
**	double	dx_cam;
**	double	dy_cam;
**	//	int		coefy;
**	//	int		coefx;
**
**	ft_putstr("a\n");
**	if (fov_y <= 0 || fov_y >= 180 || fov_y > 180 || fov_y < 0
**		|| !corner || !*corner)
**		return ;
**	ft_putstr("b\n");
**	dx_cam = tan(fov_x);
**	dy_cam = tan(fov_y);
**	ft_putstr("c\n");
**	i = 0;
**	while (i < 4 && corner[i])
**	{
**	ft_putstr("d\n");
**		matrix_buffer(corner[i]);
**	//		coefy = (i % 2) ? 1 : -1;
**	//		coefx = (i > 2) ? 1 : -1;
**	ft_putstr("e\n");
**	//		matrix_put_in(coefx * dx_cam, coefy * dy_cam, 1, 1);
**	ft_putstr("f\n");
**		i++;
**	}
**	ft_putstr("g\n");
**}
*/

void		set_normal(t_matrix **normal, t_matrix **corner)
{
	int	i;

	if (!normal || !corner || !corner[0])
		return ;
	i = 0;
	while (i < 4 && corner[(i + 1) % 4])
	{
		vector_product_in(corner[i], corner[(i + 1) % 4], normal[i]);
		i++;
	}
}

int			malloc_cam_tab(t_cam *cam)
{
	int	i;

	i = 0;
	if (!cam || !cam->corner || !cam->base)
		return (0);
	while (i < 3)
	{
		if (!(cam->corner[i] = matrix_init(1, 3))
			|| !(cam->base[i] = matrix_init(1, 3)))
			return (0);
		i++;
	}
	return (1);
}

t_matrix	**init_base(void)
{
	int			i;
	t_matrix	**base;

	if (!(base = (t_matrix**)malloc(sizeof(t_matrix*) * 3)))
		return (NULL);
	i = 0;
	while (i < 3)
	{
		if (!(base[i] = vect_new_vertfd(i == 0, i == 1, i == 2)))
			return (NULL);
		i++;
	}
	return (base);
}

t_cam		*init_cam(double fov_y, double fov_x, t_env *e)
{
	t_cam		*c;

	(void)fov_x;
	c = (t_cam*)malloc(sizeof(t_cam));
	if (!c || fov_y <= 0 || fov_y >= 180 || fov_x >= 180 || fov_x <= 0
		|| !(c->dir = vect_new_vertfd(0, 0, 1))
		|| !(c->rot = vect_new_vertfd(0, 0, 0))
		|| !(c->pos = vect_new_vertfd(0, 0, 0))
		|| !(c->corner = (t_matrix**)malloc(sizeof(t_cam*) * 4))
		|| !(c->base = init_base()))
	{
		ft_putstr("error on cam PARAMETER!!!\n");
		return (NULL);
	}
	c->pos->m[Z] = -700;
	c->pos->m[X] = 0;
	c->pos->m[Y] = 0;
	c->rot->m[0] = e->rot_x;
	c->rot->m[1] = e->rot_y;
	c->rot->m[2] = e->rot_z;
	return (c);
}
