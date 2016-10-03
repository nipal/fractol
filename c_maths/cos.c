/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 01:46:49 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/27 07:54:09 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

double	ft_cos(double deg)
{
	static	double	tab[TRIGO_ACCURACY];
	static	int		init = 1;
	int				i;

	if (init)
	{
		i = 0;
		init = 0;
		while (i < TRIGO_ACCURACY)
		{
			tab[i] = cos((((double)i) / ((double)TRIGO_ACCURACY)) * 2 * M_PI);
			i++;
		}
	}
	return (tab[((int)((deg / 360.0) * TRIGO_ACCURACY) % TRIGO_ACCURACY)]);
}
