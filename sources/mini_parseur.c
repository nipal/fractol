/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parseur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:34:21 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/04 20:55:52 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fractol.h"

void	print_usage(char tab[NB_NAME_FRAC][NB_NAME_ALT][NB_LETTER_NAME]
		, char *name)
{
	int	i;
	int	j;

	j = 0;
	ft_putstr("usage:\n");
	while (j < (NB_NAME_FRAC - 1) && tab[j][0][0] && !(i = 0))
	{
		(!j) ? ft_putstr("  syntax:\n")
			: (j == 1) && ft_putstr("  alternativ names:\n");
		ft_putstr("\t");
		ft_putstr(name);
		(!i && !j) ? ft_putstr("\t") : ft_putstr(" [");
		while (i < (NB_NAME_ALT - 1) && tab[j][i][0])
		{
			(j && i) ? ft_putstr(" | ") : (i >= 1) && !j && ft_putstr(name)
				&& ft_putstr("\t");
			ft_putstr(tab[j][i]);
			(j) ? 0 : ft_putstr("\n\t");
			i++;
		}
		(j) ? ft_putstr("]\n") : 0;
		if (!j)
			ft_putstr("\n");
		j++;
	}
}

int		check_one_id(char tab[NB_NAME_FRAC][NB_NAME_ALT][NB_LETTER_NAME]
		, char *name, int *id)
{
	int		i;
	int		j;
	int		found;

	if (!tab || !name || !id)
		return (0);
	j = 0;
	found = -1;
	while (++j < NB_NAME_FRAC && tab[j][0][0])
	{
		i = -1;
		while (++i < NB_NAME_ALT && tab[j][i][0])
		{
			if (!(ft_strcmp(tab[j][i], name)) && (found = j)
					&& (*id & (1 << (j - 1))))
				return (ft_putstr("##\tdoubule information\t##\n") * 0);
			else if ((found) && !(*id & (1 << (j - 1))))
				*id |= (1 << (found - 1));
		}
	}
	if (found < 0)
		return (ft_putstr("##\tstring not found in alterntiv\t##\n") * 0);
	return (1);
}

int		check_id(char tab[NB_NAME_FRAC][NB_NAME_ALT][NB_LETTER_NAME]
		, int ac, char **av, int *id)
{
	int		k;

	if (!tab || !av || !*av || !id || ac <= 1)
	{
		ft_putstr("##\tnothing\t##\n");
		return (0);
	}
	*id = 0;
	k = 1;
	while (av[k] && k < ac)
	{
		if (!check_one_id(tab, av[k], id))
			return (0);
		++k;
	}
	return (1);
}

int		check_syntax(int *id)
{
	*id %= 2 << 10;
	if (1 & *id && ~1 & *id)
	{
		ft_putstr("##\tincompatible assosiation: ifs and other\t##\n");
		return (0);
	}
	if (((*id & (*id >> 1)) & (1 << 1)))
	{
		ft_putstr("##\tincompatible assosiation: mandelbrot and julia\t##\n");
		return (0);
	}
	if (!(*id & 1) && !(*id & (1 << 1) && !(*id & (1 << 2))))
		*id |= 1 << 1;
	return (1);
}

int		parse_imput(int ac, char **av
		, char tab[NB_NAME_FRAC][NB_NAME_ALT][NB_LETTER_NAME])
{
	int	id;

	id = 0;
	if (check_id(tab, ac, av, &id))
	{
		if (check_syntax(&id))
		{
			print_binary(id);
			init_fractol(id);
		}
		else
		{
			ft_putstr("syntax error!\n");
			print_usage(tab, ((!ft_strncmp(av[0], "./", 2)) ? av[0] : av[0]
						+ 2));
			return (0);
		}
	}
	else
	{
		ft_putstr("arg eror!\n");
		print_usage(tab, ((!ft_strncmp(av[0], "./", 2)) ? av[0] : av[0] + 2));
		return (0);
	}
	return (1);
}
