/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_parse_time_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 23:10:27 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/01 23:20:26 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>

void		ft_replace(char *str, char *to_find, char replace)
{
	int	i;

	i = 0;
	if (!str || !to_find)
		return ;
	while (str[i])
	{
		if (ft_strrchr(to_find, str[i]) != 0)
			str[i] = replace;
		i++;
	}
}

int			ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		i++;
	}
	return (i);
}

int			*get_number_from_str(char **char_nb, int *size)
{
	int	*tab_nb;
	int	i;

	i = 0;
	if (!char_nb || !*char_nb)
		return (NULL);
	if (!size)
		return (NULL);
	*size = ft_tablen(char_nb);
	if (*size <= 0 || !(tab_nb = (int*)malloc(*size * sizeof(int))))
		return (NULL);
	while (i < *size)
	{
		tab_nb[i] = ft_atoi(char_nb[i]);
		i++;
	}
	return (tab_nb);
}

int			free_char_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (1);
}

t_list		*read_line_number(int fd)
{
	char	**tab_nb;
	char	*line;
	int		ret;
	int		*line_nb;
	t_list	*elem;

	ret = get_next_line(fd, &line);
	if (ret <= 0)
		return (NULL);
	ft_replace(line, "\t\v\r", ' ');
	tab_nb = ft_strsplit(line, ' ');
	free(line);
	if (!(line_nb = get_number_from_str(tab_nb, &ret)))
		return (NULL);
	if (!(elem = ft_lstnew(line_nb, ret * sizeof(int))))
		return (NULL);
	free_char_split(tab_nb);
	return (elem);
}
