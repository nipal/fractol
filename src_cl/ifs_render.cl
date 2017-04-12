/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_parallel.cl                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 07:31:16 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/14 07:07:45 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	le truc qui permet d'avoir un teste facile d'une image...
__kernel void test_image(__global int *time, __global int *data)
{
	int	id = get_global_id(0);
	int	val;
	
	val = (id + *time) % 256;
	data[id] = ((val * 7)% 256) << 16 | (256 - val) << 8 | abs(128 - val) * 2;
}

float	get_line_length(float2 p1, float2 p2)
{
	float	dist;
	int		id_max;
	int		max_p[2];

	max_p[0] = p1.x - p2.x;
	max_p[1] = p1.y - p2.y;
	max_p[0] *= (max_p[0] > 0) ? 1 : -1; 
	max_p[1] *= (max_p[1] > 0) ? 1 : -1; 
	id_max = (max_p[0] > max_p[1]) ? 0 : 1;
	return (max_p[id_max]);
}

__kernel	void	draw_line(__global int *img, int line_width, float2 p1, float4 c1, float2 p2, float4 c2)
{

	//	2  vecteur unitaire : {direction + couleur}
	//	nombre d' iteration 
	// comment faire pour ne pas avoir de boucle???
	// si c' est une ligne qui est juste le prolongement d' une autre,
	// on peu se permetre de smplifier des calcule mais on verra ca plus tard 

	float2	diff_pos;
	float4	diff_col;
	float2	unit_pos;
	float4	unit_col;
	int		indice;
	int		col_value;
	float	dist;
	int		nb_point;
	int		i;

	diff_pos = p2 - p1;
	diff_col = c2 - c1;
	dist = get_line_length(p1, p2);
	nb_point = dist;
	unit_pos = diff_pos / dist;
	unit_col = diff_col / dist;
	i = 0;

	while(i < nb_point)
	{
		indice = ((int) unit_pos.x) + ((int)unit_pos.y * line_width);
		col_value = (((int)c1.x) << 16) | (((int)c1.y) << 8) | (((int)c1.z));
		img[indice] = col_value;
		p1 += unit_pos;
		c1 += unit_col;
		i++;
	}
}

/*
**	au debut on peu juste tester avec un truc qui ne remet pas a zero
**	puis on pourra faire un genre de bzero_cl
*/

/*
*	pt_ifs 		=>	le buffer de tout les point a calculer pour la fractale
*	transform	=>	le buffer de point de la transformation
*	beg_data_id	=>	le tableau qui recense les offset d'indice pour "pt_ifs" en fonction de "num_iter"
*	num_iter	=>	la passe de rendu qu'on est entrain de calculer (si on en est par exemple a la 5eme passe de rendue sur pt_ifs)
*
*	On a pas la base pck le buffer "pt_ifs" serra deja un peu remplis, generalement on peu considerer que au moins la base serra dedans
*/

__kernel	void	calcul_ifs_point(__global float2 *pt_ifs, __global float2 *transform, __global int *beg_data_id, int trans_len, int num_iter)
{
	int		glob_id;
	float2	ux;
	float2	uy;
	float2	new;
	int		id_trans;
	int		id_parent;
	int		id_now;

//	calcule des id pour apres tout faire en une ligne
	glob_id = get_global_id(0);
	id_trans = glob_id % trans_len;
	id_parent = (glob_id / trans_len) + beg_data_id[num_iter - 1];
	id_now = glob_id + beg_data_id[num_iter];

	ux = pt_ifs[id_parent + 1] - pt_ifs[id_parent];
	uy = (float2)(-ux.y, ux.x);

	pt_ifs[id_now] = pt_ifs[id_parent] + transform[id_trans].x * ux + transform[id_trans].y * uy;
}
