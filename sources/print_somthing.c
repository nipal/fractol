/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_somthing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:50:43 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/16 18:05:17 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fractol.h"
#include <stdio.h>

void		vectpx_to_img(t_env *e, t_matrix *pos_color)
{
	int		x;
	int		y;

	x = (int)pos_color->m[0];
	y = (int)pos_color->m[1];
	x += SIZE_Y / 2;
	y += SIZE_X / 2;
	if (x < 0 || x >= e->x_maxl || y < 0 || y >= e->y_maxl)
		return ;
	e->data[y * e->x_maxl + x].nb = ((int)pos_color->m[3]) << 16 | ((int)pos_color->m[4]) << 8
		| (int)pos_color->m[5];
}
