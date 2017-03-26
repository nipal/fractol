/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 12:48:14 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/10 11:44:04 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

int				free_matrix(t_matrix *mat)
{
	if (mat)
	{
		if (mat->m)
			free(mat->m);
		free(mat);
	}
	return (1);
}

int				matrix_free(t_matrix **mat)
{
	if (mat && *mat)
	{
		if ((*mat)->m)
		{
			free((*mat)->m);
			(*mat)->m = NULL;
		}
		if (*mat)
		{
			free(*mat);
			*mat = NULL;
		}
	}
	return (1);
}
