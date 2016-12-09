/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_modulo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 21:49:40 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/29 10:34:30 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>


double		modulo(double a, double b)
{
	double	modulo;
	int		r;

	b = (b > 0) ? b : -b;
	if (a >= 0)
	{
		if (a < b)
			return (a);
		r = (long)(a / b);
		return (a - r * b);
	}
	else
	{
		r = (long)(a / b);
		return (a - ((r - 1)) * b);
	}
}

int		main(int ac, char **av)
{
	double	a, b, c;

	if (ac == 3)
	{
		a = atof(av[1]);
		b = atof(av[2]);
		c = modulo(a, b);
		dprintf(1, "%.2f	modulo	%.2f	= %.2f\n", a, b, c);
	}
	return (1);
}
