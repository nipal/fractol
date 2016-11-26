/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_normalise.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 04:32:21 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/20 04:49:17 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

void			matrix_normalise(t_matrix *vect)
{
	double	norme;

	if (!vect)
		return ;
	norme = matrix_dot_product(vect, vect);
	matrix_scalar_product(vect, 1 / norme);
}

t_matrix		*matrix_normalise_new(t_matrix *vect)
{
	double		norme;
	t_matrix	*new;

	if (!vect)
		return (NULL);
	norme = matrix_dot_product(vect, vect);
	if (!(new = matrix_scalar_product_new(vect, 1 / norme)))
		return (NULL);
	return (new);
}

int				matrix_normalise_in(t_matrix *src, t_matrix *dest)
{
	double	norme;

	if (!src || !dest)
		return (0);
	norme = matrix_dot_product(src, src);
	matrix_copy_in(src, dest);
	matrix_scalar_product(dest, 1 / norme);
	return (1);
}
