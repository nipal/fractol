/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 12:17:52 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/10 10:42:57 by fjanoty          ###   ########.fr       */
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

int		free_slider(t_slider ***tabs)
{
	int	i;

	i = 0;
	while (tabs[0][i])
	{
		matrix_free(&(tabs[0][i]->color));
		free(tabs[0][i]->border);
		free(tabs[0][i]);
		tabs[0][i] = NULL;
		i++;
	}
	free(*tabs);
	*tabs = NULL;
	return (1);
}

int		ft_exit(t_env *e)
{
	polygone_destroy(&(e->base_model));
	polygone_destroy(&(e->trans_model));
	polygone_destroy(&(e->base));
	polygone_destroy(&(e->transform));
	polygone_destroy(&(e->transform));
	polygone_destroy(&(e->beg_actif));
	polygone_destroy(&(e->actif));
	matrix_free(&(e->prev_mouse));
	matrix_free(&(e->mouse));
	free(e->z_buffer);
	if (e->img_low)
		free(e->img_low);
	exit(0);
	return (0);
}
