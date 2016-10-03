/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maped.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 08:33:48 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/03 17:29:25 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "c_maths.h"

t_matrix	***malloc_tab_vect(int x, int y)
{
	t_matrix	***map_mat;
	int			j;

	map_mat = NULL;
	if (!(map_mat = (t_matrix***)malloc(sizeof(t_matrix**) * y)))
		return (NULL);
	j = 0;
	while (j < y)
	{
		if (!(map_mat[j] = (t_matrix**)malloc(sizeof(t_matrix*) * x)))
			return (NULL);
		j++;
	}
	return (map_mat);
}

/*
**	max:
**		[0] : size_map_x
**		[1] : size_map_y
**		[2] : emplitude sur z de l'objet dans le monde
**		[3] : emplitude sur y de l'objet sur l'ecran 	::R1::
**		[4] : emplitude sur x de l'objet sur l'ecran	::R2::
*/

void		define_position(t_matrix ***map_mat, double *max, int i, t_env *e)
{
	int			j;
	double		r;
	t_matrix	*rot_y;
	t_matrix	*tmp;
	int			vect_nb[3];

	j = -1;
	if (!(rot_y = set_rotate(0, e->dr1 + ((i - ((max[0] - 1) / 2)) * e->phi1)
		/ (max[0] - 1), 0)))
		return ;
	while (++j < max[1])
	{
		r = (300 * e->mult_z * e->map_d[j][i] / (max[2])) + (max[4] * e->k);
		vect_nb[0] = (max[3] * e->k) + r * cos(e->dr2 + (e->phi2
				* (j - ((max[1] - 1) / 2))) / (max[1] - 1));
		vect_nb[1] = r * sin(e->dr2 + (e->phi2 * (j - ((max[1] - 1) / 2)))
				/ (max[1] - 1));
		vect_nb[0] -= max[4] * (e->k - 1);
		if (!(tmp = vect_new_verti(vect_nb, 3))
				|| (!(map_mat[j][i] = matrix_product(rot_y, tmp))))
			return ;
		map_mat[j][i]->m[0] -= max[3] * (e->k) + max[4];
		matrix_free(&tmp);
	}
	matrix_free(&rot_y);
}

t_matrix	***finishe_get_map_torus(int *vect_nb, double *max, t_env *e)
{
	t_matrix	***map_mat;
	int			i;

	(void)vect_nb;
	if (!(map_mat = malloc_tab_vect(max[0], max[1])))
		return (NULL);
	i = 0;
	while (i < max[0])
	{
		define_position(map_mat, max, i, e);
		i++;
	}
	return (map_mat);
}

double		**cast_tab(int **tab, int x, int y)
{
	double	**tab_val;
	int		j;
	int		i;

	if (!(tab_val = (double**)malloc(sizeof(double*) * y)))
		return (NULL);
	j = 0;
	while (j < y)
	{
		if (!(tab_val[j] = (double*)malloc(sizeof(double) * x)))
			return (NULL);
		i = 0;
		while (i < x)
		{
			tab_val[j][i] = (double)tab[j][i];
			i++;
		}
		j++;
	}
	return (tab_val);
}

/*
**	max:
**		[0] : size_map_x
**		[1] : size_map_y
**		[2] : emplitude sur z de l'objet dans le monde
**		[3] : emplitude sur y de l'objet sur l'ecran 	::R1::
**		[4] : emplitude sur x de l'objet sur l'ecran	::R2::
*/

t_matrix	***get_map(t_env *e)
{
	double		max[5];
	int			vect_nb[3];

	if (!e)
		return (NULL);
	max[0] = e->size_map_x;
	max[1] = e->size_map_y;
	max[2] = ((e->z_max - e->z_min)) ? (e->z_max - e->z_min) : 1;
	max[3] = e->ecr_y * 0.70 / 5.0;
	max[4] = max[3] * 3.0 / 5.0;
	max[4] += max[3] * (1 - e->advence);
	max[3] *= e->advence;
	return (finishe_get_map_torus(vect_nb, max, e));
}
