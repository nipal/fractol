/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 22:06:44 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/14 07:40:51 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void		*mem;

	if (!(mem = malloc(sizeof(char) * size)))
		return (NULL);
	ft_bzero(mem, size);
	return ((void *)mem);
}
