/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 07:31:16 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/09 05:10:54 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "fractol.h"

void	init_fractol(int id)
{
	t_env	e;

	ft_bzero(&e, sizeof(t_env));
	if (id & 1)
		env(&e);
	else
		(init_mandel(&e, id));
}

void	print_binary(int nb)
{
	if (nb == -2147483648)
		ft_putstr("10000000000000000000000000000000");
	if (nb < 0)
	{
		ft_putstr("1|");
		print_binary(-nb);
	}
	if (nb > 0)
		print_binary(nb / 2);
	ft_putchar('0' + (nb % 2));
}

int		main(int ac, char **av)
{
	static	char	tab[NB_NAME_FRAC][NB_NAME_ALT][NB_LETTER_NAME] = {
		{"[ifs]", "[m | [ot | bs]]", "[ju | [ot | bs]]"},
		{"ifs", "koch", "koch_generalise"},
		{"m", "mandelbrot", "mandel"},
		{"ju", "julia"},
		{"ot", "orbit_trap", "trap"},
		{"bs", "burning_ship", "burning", "ship"}};

	if (!(init_debug(NB_MALLOC)))
		return (1);
	if (ac == 1)
	{
		print_usage(tab, ((!ft_strncmp(av[0], "./", 2)) ? av[0] : av[0] + 2));
		return (1);
	}
	else
		parse_imput(ac, av, tab);
	close_all_debug(NB_MALLOC);
	return (0);
}
