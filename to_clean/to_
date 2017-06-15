/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bezier.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 23:01:44 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/29 00:14:44 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

# define MAX_BEZIER 16

double	pascal_triangle[MAX_BEZIER][MAX_BEZIER];

void		init_pascal_coef(double pascal[MAX_BEZIER][MAX_BEZIER]);
t_polygone	*calcul_bezier_2d(t_polygone *pt, double pascal[MAX_BEZIER][MAX_BEZIER], double t);
void		draw_bezier_curve(t_polygone *pt);


void	init_pascal_coef(double pascal[MAX_BEZIER][MAX_BEZIER])
{
	int	i;
	int	j;

	//	premier passe
	for (j = 0; j < MAX_BEZIER; j++)
	{
		for (i = 0; i < MAX_BEZIER; i++)
		{
			if (i > j)
				pascal[j][i] = 0;
			else if (i == 0 || i == j)
				pascal[j][i] = 1;
		}
	}

	//	remplissage
	for (j = 1; j < MAX_BEZIER; j++)
	{
		for (i = 1; i < j; i++)
		{
			pascal[j][i] = pascal[j - 1][i - 1] + pascal[j - 1][i];
		}
	}
}

t_polygone	*calcul_bezier_2d(t_polygone *pt, double pascal[MAX_BEZIER][MAX_BEZIER], double t)
{
	int	i;
	int	len;
	sum;

	len = get_polygone_len(pt);
	if (len > MAX_BEZIER)
		return (0);
	i = 0;
	sum = 0;
	while (i < len)
	{
		
		pt = pt->next;
		i++;
	}
}


t_polygone	*calcul_polynome(double *val, int nb, double pascal[MAX_BEZIER][MAX_BEZIER], double t)
{
	int	i;
	int	len;
	sum;

	len = nb;
	if (len > MAX_BEZIER)
		return (0);
	i = 0;
	sum = 0;
	while (i < len)
	{

		pt = pt->next;
		i++;
	}
}
