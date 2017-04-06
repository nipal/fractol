/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 20:27:04 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/09 22:18:40 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

t_matrix	*matrix_buffer(t_matrix *mat)
{
	static	t_matrix	*buff;

	if (!mat)
		return (buff);
	else
		return (buff = mat);
}
