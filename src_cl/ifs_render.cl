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

typedef	struct	s_pt_line
{
	float2		p1;
	float2		p2;
}				t_pt_line;

typedef	struct	s_col_line
{
	float4		c1;
	float4		c2;
}				t_col_line;



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

__kernel	void	draw_line(__global int *img, __global t_pt *pt, __global t_col *col, __global float2 *dim_ecr)
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
	float2	p;
	float4	c;
	int		indice;
	int		col_value;
	float	dist;
	int		nb_point;
	int		i;
	int		id;
	bool	is_inside;

	id = get_global_id(0);
	diff_pos = pt[id].p2 - pt[id].p1;
	diff_col = col[id].c2 - col[id].c1;
	dist = get_pt_length(pt[id].p1, pt[id].p2);
	nb_point = dist;
	unit_pos = diff_pos / dist;
	unit_col = diff_col / dist;
	i = 0;
	p = pt[id].p1;
	c = col[id].c1;
	while(i < nb_point)
	{
		//	Il faudra ne pas ecrire dans le buffer si on sort de l'ecran
		
		indice = ((int) p.x) + ((int)(p.y * dim_ecr[0].x));
		col_value = (((int)c1.x) << 16) | (((int)c1.y) << 8) | (((int)c1.z));
		is_inside = (p.x >= 0 && p.x < dim_ecr[0].x && p.y >= 0 && p.y < dim_ecr[0].y);	
		if (is_inside)
			img[indice] = col_value;
		p += unit_pos;
		c += unit_col;
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

__kernel	void	calcul_ifs_point(__global float2 *pt_ifs, __global float2 *transform, __global int *beg_data_id, __global int *trans_len, __global int *num_iter)
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
	id_trans = glob_id % trans_len[0];
	id_parent = (glob_id / trans_len[0]) + beg_data_id[num_iter[0] - 1];
	id_now = glob_id + beg_data_id[num_iter[0]];

	ux = pt_ifs[id_parent + 1] - pt_ifs[id_parent];
	uy = (float2)(-ux.y, ux.x);

	pt_ifs[id_now] = pt_ifs[id_parent] + transform[id_trans].x * ux + transform[id_trans].y * uy;
}
