/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_parse_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 16:43:26 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 23:45:21 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>

void		get_size(t_list *begin, int *max_x, int *max_y)
{
	int		x_max;
	int		y_max;
	t_list	*elem;

	x_max = 0;
	y_max = 0;
	elem = begin;
	while (elem)
	{
		if ((int)(elem->content_size / sizeof(int)) > x_max)
			x_max = elem->content_size / sizeof(int);
		elem = elem->next;
		y_max++;
	}
	*max_x = x_max;
	*max_y = y_max;
}

int			**continu_get_map(int **tab, int *line, t_list *elem, int *max)
{
	int	i;
	int	j;

	j = max[1];
	while (j >= 0)
	{
		if (!(tab[j] = (int*)malloc(sizeof(int) * max[0])))
			return (NULL);
		ft_bzero(tab[j], sizeof(int) * max[0]);
		line = (int*)elem->content;
		i = 0;
		while (i < (int)(elem->content_size / sizeof(int)))
		{
			tab[j][i] = line[i];
			i++;
		}
		elem = elem->next;
		j--;
	}
	return (tab);
}

int			**get_map_lst(t_list *begin, int *max_x, int *max_y)
{
	int		*line;
	int		**tab;
	int		max[2];

	line = NULL;
	if (!begin || !max_x || !max_y)
		return (NULL);
	get_size(begin, max_x, max_y);
	if (!(tab = (int **)malloc(sizeof(int*) * *max_y)))
		return (NULL);
	max[0] = *max_x;
	max[1] = *max_y - 1;
	return (continu_get_map(tab, line, begin, max));
}

int			free_the_node(t_list *elem)
{
	t_list	*tmp;

	while (elem)
	{
		tmp = elem->next;
		free(elem->content);
		free(elem);
		elem = tmp;
	}
	return (1);
}

int			**get_the_map(int fd, int *x_max, int *y_max)
{
	t_list	*elem;
	t_list	*begin;
	int		**map;

	begin = NULL;
	while ((elem = read_line_number(fd)))
	{
		elem->next = begin;
		begin = elem;
	}
	if (!(map = get_map_lst(begin, x_max, y_max)))
	{
		if (errno)
			perror(maps_name(NULL));
		else
			ft_putstr("Error on getting the map");
	}
	free_the_node(begin);
	close(fd);
	return (map);
}
