/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_translate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/14 00:25:54 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 18:57:03 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

t_matrix	*set_translate(double dx, double dy, double dz)
{
	t_matrix	*t;

	t = matrix_init(4, 4);
	t->m[0] = 1;
	t->m[3] = dx;
	t->m[5] = 1;
	t->m[7] = dy;
	t->m[10] = 1;
	t->m[11] = dz;
	t->m[15] = 1;
	return (t);
}
