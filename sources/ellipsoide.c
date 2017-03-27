/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoide.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 23:41:50 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/28 01:16:30 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


void		draw_ellipsoide_(t_win *w, t_polygone *pt);

void		ellipsoid_modify_centre(t_polygone *pt, t_polygone *old_pos);
void		ellipsoid_modify_ux(t_polygone *pt, t_polygone *old_pos);
void		ellipsoid_modify_uy(t_polygone *pt, t_polygone *old_pos);

/*
void		draw_ellipsoide_(t_win *w, t_polygone *pt)
{
	int			i;
	int			len;
	double		r1;	// ux
	double		r2; // uy
	t_matrix	*diff;
	t_matrix	*pta;
	t_matrix	*ptb;
	t_matrix	*col;
	t_matrix	*ux;
	t_matrix	*uy;

	if (!pt || !(pt->next) || !(pt->next->next))
		return ;
	if (!(pta = matrix_init(1, 3))
		|| !(ptb = matrix_init(1, 3)))
		return ;
	if (!(ux = matrix_sub(pt->next->pos, pt->pos)))
		return ;
	if (!(uy = matrix_sub(pt->next->next->pos, pt->pos)))
		return ;

	diff->pos->m[2] = 0;
	i = 0;
	r1 = sqrt(matrix_scalar_product(ux, ux));
	r2 = sqrt(matrix_scalar_product(uy, uy));
	len = (int) r1;
	while (i < len)
	{

		i++;
	}
	matrix_free(&col);
}
*/
