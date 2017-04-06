/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/14 00:25:54 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 18:56:59 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "c_maths.h"

static	t_matrix	*init_xrot_matrix(double thetx)
{
	t_matrix	*r;

	r = matrix_init(3, 3);
	r->m[4] = cos(thetx);
	r->m[5] = sin(thetx);
	r->m[7] = -sin(thetx);
	r->m[8] = cos(thetx);
	r->m[0] = 1;
	return (r);
}

static	t_matrix	*init_yrot_matrix(double thety)
{
	t_matrix	*r;

	r = matrix_init(3, 3);
	r->m[0] = cos(thety);
	r->m[2] = -sin(thety);
	r->m[4] = 1;
	r->m[6] = sin(thety);
	r->m[8] = cos(thety);
	return (r);
}

static t_matrix		*init_zrot_matrix(double thetz)
{
	t_matrix	*r;

	r = matrix_init(3, 3);
	r->m[0] = cos(thetz);
	r->m[1] = sin(thetz);
	r->m[3] = -sin(thetz);
	r->m[4] = cos(thetz);
	r->m[8] = 1;
	return (r);
}

t_matrix			*set_rotate(double thetx, double thety, double thetz)
{
	t_matrix	*rx;
	t_matrix	*ry;
	t_matrix	*rz;
	t_matrix	*r;

	rx = init_xrot_matrix(thetx);
	ry = init_yrot_matrix(thety);
	rz = init_zrot_matrix(thetz);
	r = matrix_product(ry, rx);
	matrix_free(&rx);
	matrix_free(&ry);
	ry = r;
	r = matrix_product(rz, r);
	matrix_free(&ry);
	matrix_free(&rz);
	return (r);
}
