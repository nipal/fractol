/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 07:31:16 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 19:13:49 by fjanoty          ###   ########.fr       */
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

int		main(int ac, char **av)
{
	int		fd;
	int		**map;
	int		size_x;
	int		size_y;
	char	*str;

	if (ac == 2)
		str = av[1];
	else
		str = "maps/42.fdf";
	maps_name(str);
	fd = open(str, O_RDONLY);
	if (fd > 0)
	{
		if ((map = get_the_map(fd, &size_x, &size_y)))
			env(map, size_x, size_y);
	}
	else
		perror(str);
	return (0);
}
