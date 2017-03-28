/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoide.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 23:41:50 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/28 05:15:12 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


void		draw_ellipsoide_(t_win *w, t_polygone *pt);

void		ellipsoid_modify_centre(t_polygone *pt, t_polygone *old_pos);
void		ellipsoid_modify_ux(t_polygone *pt, t_polygone *old_pos);
void		ellipsoid_modify_uy(t_polygone *pt, t_polygone *old_pos);

void		draw_ellipsoide_(t_win *w, t_polygone *pt)
{
	int			i;
	int			len;
	double		r1;	// ux
	double		r2; // uy
	t_matrix	*diff;
	t_matrix	*pt_a1;
	t_matrix	*pt_b1;
	t_matrix	*pt_a2;
	t_matrix	*pt_b2;
	t_matrix	*col;
	t_matrix	*ux;
	t_matrix	*uy;

	if (!pt || !(pt->next) || !(pt->next->next))
		return ;
	if (!(pt_a1 = matrix_init(1, 3))
		|| !(pt_b1 = matrix_init(1, 3))
		|| !(pt_a2 = matrix_init(1, 3))
		|| !(pt_b2 = matrix_init(1, 3)))
		return ;
	if (!(ux = matrix_sub(pt->next->pos, pt->pos)))
		return ;
	if (!(uy = matrix_sub(pt->next->next->pos, pt->pos)))
		return ;

	diff->m[2] = 0;
	i = 0;
	r1 = sqrt(matrix_dot_product(ux, ux));
	r2 = sqrt(matrix_dot_product(uy, uy));
	len = (int) r1;
	while (i < len)
	{
		
		i++;
	}
	matrix_free(&col);
}
