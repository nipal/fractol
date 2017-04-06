/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iteratif_ifs_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 02:49:05 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/06 04:57:28 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
		typedef	struct	s_data_nw
		{
			double	pt_trans[MAX_NODE][2];
			double	pt_base[MAX_NODE][2];
			int		trans_len;
			int		base_len;
			int		max_iter;
			double	col_val[6];	// les parametre de couleur
		}				t_data_nw;
*/

/*
 *	Il faut calculer tout les points. O n va les mettre dans un grand buffer. Il
 *	faudra donc en fonction d'un indice savoir aux quel indices on est relier.
 *
 * */

#include <stdlib.h>
#include <stdio.h>

//	
//	void	calcul_ifs_point(t_data_nw *param)
//	{
//		double	*(tab_pt[2]);
//	}

/*
 * 	Pour l'instant l'algo est fait pour des cas ou on a pas plus que MAX_INT de point
 * 	On prend en entre les nombres qui parametre les les iteration
 * 	et la memoir disponible. Et on (malloc puis) remplis un tableau avec
 * 	les inice de chaque debut de portion. La memoir est donner en octet
 *
 * Le tableau dindice serra deja allouer et avec un nombre max resonable
 * le pire cas possible c'est:
 * 		nb_base = 2
 * 		nb_trans = 3
 * 		2*3*3*3*3*3*3*3*3*3*3*3*3*3*3*3 = 28697814 :: donc c'est trop pour maxINT
 *
 * 		2*3*3*3*3*3*3*3*3*3*3*3*3*3*3 = 9565938
 * 		donc le pire des cas on a 15 indice (parceque on recopie tout les poitn)
 * */

int		calcul_nb_ite_max(int nb_base, int nb_trans, int size_mem, int *indice_beg)
{
	int		iter_max;
	int		i;
	int		sum;

	if (!indice_beg || nb_base <= 1 || nb_trans <= 2)
		return (-1);
	size_mem /= sizeof(float) * 2;
	sum = nb_base;
	iter_max = 0;
	while ((sum = sum * (nb_trans + 1)) <= size_mem)
		iter_max++;
	i = 1;
	sum = nb_base;
	indice_beg[0] = 0;
	while (i < iter_max)
	{
		indice_beg[i] = sum - 1;
		sum = sum * (nb_trans + 1);
		i++;
	}
	return (iter_max);
}

int main(int ac, char **av)
{
	int	start_indice[20];
	int	max_iter;
	int	size_mem;
	int	nb_pt;
	int	len_base;
	int	len_trans;
	int	i;

	if (ac < 3)
	{
		printf("usage: %s	len_base len_transformation\n", av[0]);
		return (0);
	}
	len_base = atoi(av[1]);
	len_trans = atoi(av[2]);
	nb_pt = 50000000;
	size_mem = (sizeof(float) * 2) * nb_pt;
	max_iter = calcul_nb_ite_max(len_base, len_trans, size_mem, start_indice);
	printf("len_base:%d	len_trans:%d	size_mem:%d\n", len_base, len_trans, size_mem);
	printf("max_iter:%d\n", max_iter);
	for (i = 0; i < max_iter; i++)
		printf("	begin[%d]:%d\n", i, start_indice[i]);
	return (0);
}
