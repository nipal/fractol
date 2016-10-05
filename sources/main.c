/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 07:31:16 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/05 04:13:10 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "fdf.h"

char	*maps_name(char *str)
{
	static	char	*name = NULL;

	if (str)
		name = str;
	return (name);
}

int		main(void)
{
//	int		fd;
	int		**map;
	int		size_x;
	int		size_y;
//	char	*str;

	size_x = 0;
	size_y = 0;
	ft_putstr("ahahah\n");
	map = ft_memalloc(sizeof(int *));
	map[0] = ft_memalloc(sizeof(int) * 300);
	env(map, size_x, size_y);
	env(map, size_x, size_y);
	ft_putstr("wesh\n");
	return (0);
}
