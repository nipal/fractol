/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/14 00:25:54 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 18:56:41 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "c_maths.h"

void	matrix_display(t_matrix *a)
{
	int		i;
	int		j;

	if (!a)
		return ;
	i = 0;
	while (i < a->y)
	{
		j = 0;
		while (j < a->x)
		{
			ft_putnbr(a->m[j + a->x * i]);
			ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
