/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 07:31:16 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/26 16:07:44 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "fractol.h"


int		get_id_config(char tab[NB_NAME_FRAC][NB_NAME_FRAC][NB_LETTER_NAME])
{
	if (tab[0][0])
		return (1);
	return (0);
}

void	print_usage(char tab[NB_NAME_FRAC][NB_NAME_ALT][NB_LETTER_NAME], char *name)
{
	int	i;
	int	j;

	j = 0;
	ft_putstr("usage:\n");
	while (j < (NB_NAME_FRAC - 1) && tab[j][0][0])
	{
		i = 0;
		(!j) ? ft_putstr("  syntax:\n") : (j == 1) && ft_putstr("  alternativ names:\n");
		ft_putstr("\t");
		ft_putstr(name);
		(!i && !j) ? ft_putstr("\t") : ft_putstr(" [");
		while (i < (NB_NAME_ALT - 1) && tab[j][i][0])
		{
			(j && i) ? ft_putstr(" | ") : (i >= 1) && !j && ft_putstr(name) && ft_putstr("\t");
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

/*
**	[[m] | [ju]] | [ot] | [bc] | [ifs]
**	[1 | 2] []

 	0 et 1	=>	base
	2, 3 	=>	combinaison
	4		=>	allone

	// (non) | 
	//	 	 |
	//	 	 |
	//	 	 v
	//
	{0}, {(1, 2)->(3, 4)}
	//	on gere le parsing des implication
	//	{}	: famille de fratal
	//	()	: ensemble combinable
	//		()->	: graine
	//		->()	: option
	//
	//	symbole:	
	//				'{', '}', '(', ')', '->', '%d', 
	//
	
	// 0 et rien d'autre
	// [1-4]
	// 		[*1, 2] | 3 | 4 
	// 		si ni 1 ni 2 alors 1 , [3 | 4] 
	// 	on ne repete jamais deux fois un meme indice, mais il peuvent etre dans le desodre
	// 	une seule etoile par groupe de ^, elle precise un choix par default
	// {0}, {(*1 ^ 2) | 3 | 4}
*/

/*
**	
*/

/*
**	verifi si deux id on ete utilise (ex: 2 mots de la meme liste)
*/

int		check_one_id(char tab[NB_NAME_FRAC][NB_NAME_ALT][NB_LETTER_NAME], char *name, int *id)
{
	int		i;
	int		j;
	int		found;

	if (!tab || !name || !id)
	{
		(!tab) ? ft_putstr("no tab\n"): 0;
		(!name) ? ft_putstr("no name\n"): 0;
		(!id) ? ft_putstr("no id\n"): 0;
		ft_putstr("hum... !!!===>  NOOOOOO <===!!\n");
		return (0);
	}
	j = 0;
	found = -1;
	while (++j < NB_NAME_FRAC && tab[j][0][0])
	{
		i = -1;
		while (++i < NB_NAME_ALT && tab[j][i][0])
		{
			if (!(ft_strcmp(tab[j][i], name)) && (found = j))
			{
				if ((*id & (1 << j)))
				{
					ft_putstr("##\tdoubule information\t##\n");
					return (0);
				}
				else
					*id |= (1 << (found - 1));
			}
		}
	}
	if (found < 0)
	{
		ft_putstr("##\tstring not found in alterntiv\t##\n");
		return (0);
	}
	return (1);
}

int		check_id(char tab[NB_NAME_FRAC][NB_NAME_ALT][NB_LETTER_NAME], int ac, char **av, int *id)
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
		{
			ft_putstr("##\tone has fail\t##\n");
			return (0);
		}
		++k;
	}
	return (1);
}

/*
**	(si check_id == valide) chechre si il i a des association impossible:'
**
**		A la fin on sait construire les capaciter, on sait qu'elle ne snt pas fausse
**		donc c'est bon 
*/

int		check_syntax(int *id)
{
	if (1 & *id && ~1 & *id)
	{
		ft_putstr("##\tincompatible assosiation\t##\n");
		return (0);
	}
	if (((*id & (*id >> 1)) & (1 << 1)))
	{
		ft_putstr("##\tincompatible assosiation\t##\n");
		return (0);
	}
	if (!(*id & (1 << 1) && !(*id & (1 << 2))))
		*id |= 1 << 1;
	return (1);
}

void	init_fractol(int id)
{
	t_env	e;

	ft_bzero(&e, sizeof(t_env));
	get_env(&e);
	if (id & 1)
	{
		env(&e);
	}
	else
	{
		(init_mandel(&e, id));
	}
}

int		parse_imput(int ac, char **av, char tab[NB_NAME_FRAC][NB_NAME_ALT][NB_LETTER_NAME])
{
	int	id;
	id = 0;
	
	if (check_id(tab, ac, av, &id))
	{
		if (check_syntax(&id))
			init_fractol(id);
		else
		{
			ft_putstr("syntax error!\n");
			print_usage(tab, ((!ft_strncmp(av[0], "./", 2)) ? av[0]: av[0]  + 2));
			return (0);
		}
	}
	else
	{
		ft_putstr("arg eror!\n");
		print_usage(tab, ((!ft_strncmp(av[0], "./", 2)) ? av[0]: av[0]  + 2));
		return (0);
	}
	return (1);
}

int		main(int ac, char **av)
{
	static	char	tab[NB_NAME_FRAC][NB_NAME_ALT][NB_LETTER_NAME] =
		{
			{"[ifs]", "[m | [ot | bc]]", "[ju | [ot | bc]]"},
			{"ifs", "koch", "koch_generalise"},
			{"m", "mandelbrot", "mandel"},
			{"ju", "julia"},
			{"ot", "orbit_trap", "trap"},
			{"bc", "burning_chip", "burning", "chip"}
		};

	if (ac == 1)
	{
		print_usage(tab, ((!ft_strncmp(av[0], "./", 2)) ? av[0]: av[0]  + 2));
		return (1);
	}
	else
		parse_imput(ac, av, tab);
	return (0);
}
