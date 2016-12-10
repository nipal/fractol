/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 12:17:52 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/10 09:21:21 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fractol.h"

void	free_img(int ***img, int size_y)
{
	int	j;

	if (!img || !img[0] || !img[0][0])
		return ;
	j = 0;
	while (j < size_y)
	{
		if (img[j])
		{
			free(img[0][j]);
			img[0] = NULL;
		}
		j++;
	}
	if (img[0])
	{
		free(img[0]);
		img[0] = NULL;
	}
}

int		ft_exit(t_env *e)
{
//**	la il faudra un peu reflechir a quoi free a la fin
	(void)e;
	exit(0);
	return (0);
}
