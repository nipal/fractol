/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_objet.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 07:27:32 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/20 15:04:36 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	On va faire une fonction qui permetera aux t_obj de se remplir a fonction
**	de t_param_buffer
**
**	normalement toute les structure est a 0
*/

int	add_light(t_param_buffer *param, float *pos, int color)
{
	int	id;

	if (!param || !pos || param->current >= NB_OBJ)
		return (-1);
	id = param->current;
	ft_memmove(&(param->all_pos[id * 4]), pos, sizeof(float) * 3);
	param->all_collor[id] = color;
	param->all_type[id] = LIGHT;
	param->current++;
	return (0);
}

int	add_sphere(t_param_buffer *param, float *pos, int color, float radius)
{
	int	id;

	if (!param || !pos || param->current >= NB_OBJ)
		return (-1);
	id = param->current;
	ft_memmove(&(param->all_pos[id * 4]), pos, sizeof(float) * 3);
	param->all_collor[id] = color;
	param->all_type[id] = SPHERE;
	param->all_coef[id] = radius;
	param->current++;
	return (0);

}

int	add_plan(t_param_buffer *param, float *pos, int color, float *dir)
{
	int		id;

	if (!param || !pos || param->current >= NB_OBJ || !dir)
		return (-1);
	id = param->current;
	ft_memmove(&(param->all_pos[id * 4]), pos, sizeof(float) * 3);
	ft_memmove(&(param->all_angle [id * 4]), dir, sizeof(float) * 3);
	param->all_collor[id] = color;
	param->all_type[id] = PLAN;
	param->current++;
	return (0);

}

//	le rayon est dans la quatrieme composante du vecteur directeur
//	il faudra probablement retravailler sur les angle
int	add_cylindre(t_param_buffer *param, float *pos, int color, float *dir)
{
	int		id;
	float	angle[4];
	float	mat_rot[16];

	if (!param || !pos || param->current >= NB_OBJ)
		return (-1);
	id = param->current;
	ft_memmove(&(param->all_pos[id * 4]), pos, sizeof(float) * 3);
	param->all_collor[id] = color;
	param->all_type[id] = CYLINDER;
	angle[0] = (dir[1] > 0) ? acosf(dir[0]) : -acosf(dir[0]);
	angle[1] = 0;
	angle[2] = asinf(dir[2]);
	angle[3] = 0;
	ft_memmove(&(param->all_angle[id * 4]), angle, sizeof(float) * 3);
	set_rot_mat4_all(mat_rot, angle[0], 0, angle[2]);
	ft_memmove(&(param->all_mat_rot[id * 16]), mat_rot, sizeof(mat_rot));
	param->all_coef[id] = dir[3];
	param->current++;
	return (0);

}

//	le rayon est dans la quatrieme composante du vecteur directeur
int	add_cone(t_param_buffer *param, float *pos, int color, float *dir)
{
	int		id;
	float	angle[4];
	float	mat_rot[16];

	if (!param || !pos || param->current >= NB_OBJ)
		return (-1);
	id = param->current;
	ft_memmove(&(param->all_pos[id * 4]), pos, sizeof(float) * 3);
	param->all_collor[id] = color;
	param->all_type[id] = CONE;
	angle[0] = (dir[1] > 0) ? acosf(dir[0]) : -acosf(dir[0]);
	angle[1] = 0;
	angle[2] = asinf(dir[2]);
	angle[3] = 0;
	ft_memmove(&(param->all_angle[id * 4]), angle, sizeof(float) * 3);
	set_rot_mat4_all(mat_rot, angle[0], 0, angle[2]);
	ft_memmove(&(param->all_mat_rot[id * 16]), mat_rot, sizeof(mat_rot));
	param->all_coef[id] = dir[3];
	param->current++;
	return (0);
}
