/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 00:32:54 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/27 07:58:39 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

t_matrix	*vect_new_vertfd(double a, double b, double c)
{
	t_matrix	*vect;

	if (!(vect = matrix_init(1, 3)))
		return (NULL);
	vect->m[0] = a;
	vect->m[1] = b;
	vect->m[2] = c;
	return (vect);
}

t_matrix	*vect_new_vertfi(int a, int b, int c)
{
	t_matrix	*vect;

	if (!(vect = matrix_init(1, 3)))
		return (NULL);
	vect->m[0] = (double)a;
	vect->m[1] = (double)b;
	vect->m[2] = (double)c;
	return (vect);
}

t_matrix	*vect_new_vert(double *tab, int size)
{
	int			i;
	t_matrix	*vect;

	if (!(vect = matrix_init(1, size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		vect->m[i] = tab[i];
		i++;
	}
	return (vect);
}

t_matrix	*vect_new_horz(double *tab, int size)
{
	int			i;
	t_matrix	*vect;

	if (!(vect = matrix_init(size, 1)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		vect->m[i] = tab[i];
		i++;
	}
	return (vect);
}

t_matrix	*vect_new_verti(int *tab, int size)
{
	int			i;
	t_matrix	*vect;

	if (!(vect = matrix_init(1, size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		vect->m[i] = (double)tab[i];
		i++;
	}
	return (vect);
}
