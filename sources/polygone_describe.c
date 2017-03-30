/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone_describe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 22:20:14 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/30 23:24:16 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	matrix_describe(t_matrix *mat)
{
	int	i;
	int	j;

	printf("{");
	if (!mat)
		printf("	no matrix\n");
	else
	{
		printf("	x:%d	y:%d	",mat->x, mat->y);
		if (mat->x == 1)
		{
//				printf("---------------------------------------");
			for (i = 0;i < 3; i++)
			{
				printf("	[%d] %f", i, mat->m[i]);
			}
		}
		else
		{
			for (j = 0; j < mat->y; j++)
			{
				printf("	");
				for (i = 0; i < mat->x; i++)
				{
					printf("[%d] %f", i, mat->m[i + j * mat->x]);
				}
				printf("\n");
			}
		}
	}
	printf("	}\n");
}

void	polygone_describe(t_polygone *node)
{
	int	i;
	if (!node)
	{
		printf("empty segment!\n");
		return ;
	}
	i = 0;
	while (node)
	{
		printf("pos:\n");
		matrix_describe(node->pos);
		printf("col:\n");
		matrix_describe(node->col);
		printf("\n");
		node = node->next;
		i++;
	}
}
