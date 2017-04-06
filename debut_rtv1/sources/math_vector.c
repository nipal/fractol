/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 18:06:37 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/20 14:09:46 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	La on va viteuf refaire les fonction de math avec des float
*/

/*
**	Genere un reper a partir de 3 angle et d'un position
**	on ne travialle que avec des float[4]
*/

float	vect_dot4(float *vecta, float *vectb)
{
	int		i;
	float	sum;

	i = 0;
	sum = 0;
	while (i < 4)
	{
		sum += vecta[i] * vectb[i];
		i++;
	}
	return (sum);
}

void	mult_mat4_in(float *mat1, float *mat2, float *mat_in)
{
	int	j;
	int	i;
	int	k;
	float	tmp[16];

	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			k = 0;
				tmp[j * 4 + i] = 0;
			while (k < 4)
			{
				tmp[j * 4 + i] += mat2[k * 4 + i] * mat1[k + j * 4];
				k++;
			}
			i++;
		}
		j++;
	}
	ft_memmove(mat_in, tmp, sizeof(tmp));
}

void	set_rot_mat4(float *mat, float angle, int id1, int id2)
{
	int	id;

	id = 3 - (id1 + id2);
	ft_bzero(mat, sizeof(float) * 16);
	mat[id1 * 4 + id1] = cos(angle);
	mat[id2 * 4 + id2] = cos(angle);
	mat[id1 * 4 + id2] = -sin(angle);
	mat[id2 * 4 + id1] = sin(angle);
	mat[15] = 1;
	mat[id + 4 * id] = 1;

}

void	set_identity_in(float *dest)
{
	static	float	identity[16] = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1};

	ft_memcpy(dest, identity, sizeof(identity));
}

void	set_rot_mat4_all(float *mat, float x, float y, float z)
{
	float	mult[16];
	float	tmp[16];

	set_identity_in(mult);
	set_rot_mat4(tmp, x, 1, 2);
	mult_mat4_in(mult, tmp, mult);
	set_rot_mat4(tmp, y, 2, 0);
	mult_mat4_in(mult, tmp, mult);
	set_rot_mat4(tmp, z, 0, 1);
	mult_mat4_in(mult, tmp, mult);
	ft_memmove(mat, mult, sizeof(mult));
}

void	set_vect_val(float *vect, float a, float b, float c)
{
	vect[0] = a;
	vect[1] = b;
	vect[2] = c;
	vect[3] = 0;
}

//	on applique la matrice dans le vecteur
void	mat_vector_prod(float *mat, float *vect)
{
	int		i;
	int		k;
	int		j;
	float	tmp[4];

	i = 0;
	j = 0;
	while (i < 4)
	{
		tmp[i] = 0;
		k = 0;
		while (k < 4)
		{
			tmp[i] += vect[k] * mat[j];
			j++;
			k++;
		}
		i++;
	}
	ft_memmove(vect, tmp, sizeof(tmp));
}

void	print_vect4(float *vect)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		printf("	[%d]:%f", i, vect[i]);
		i++;
	}
	printf("\n");
}

void	print_mat4(float *mat)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		printf("[%d]::::", i);
		print_vect4(mat + 4 * i);
		i++;
	}
	printf("\n");
}

void	set_landmark(float *landmark, float *ang, float *pos)
{
	float	ux[4];
	float	uy[4];
	float	uz[4];
	float	rot[16];
	float	rot_tmp1[16];
	float	rot_tmp2[16];

	set_identity_in(rot);			

	set_rot_mat4(rot_tmp1, ang[0], 1, 2);
	mult_mat4_in(rot, rot_tmp1, rot_tmp2);
	ft_memmove(rot, rot_tmp2, sizeof(rot));

	set_rot_mat4(rot_tmp1, ang[1], 2, 0);
	mult_mat4_in(rot, rot_tmp1, rot_tmp2);
	ft_memmove(rot, rot_tmp2, sizeof(rot));

	set_rot_mat4(rot_tmp1, ang[2], 0, 1);
	mult_mat4_in(rot, rot_tmp1, rot_tmp2);
	ft_memmove(rot, rot_tmp2, sizeof(rot));	

	set_vect_val(ux, 1, 0, 0);
	set_vect_val(uy, 0, 1, 0);
	set_vect_val(uz, 0, 0, 1);
mat_vector_prod(rot, ux);
mat_vector_prod(rot, uy);
mat_vector_prod(rot, uz);
	ft_memmove(landmark, pos, sizeof(float) * 4);
	ft_memmove(landmark + 4, ux, sizeof(ux));
	ft_memmove(landmark + 8, uy, sizeof(uy));
	ft_memmove(landmark + 12, uz, sizeof(uz));
}
