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
}				t_pt;

typedef	struct	s_col_line
{
	float4		c1;
	float4		c2;
}				t_col;



//	le truc qui permet d'avoir un teste facile d'une image...
__kernel void test_image(__global int *time, __global int *data)
{
	int	id = get_global_id(0);
	int	val;
	
	val = (id + *time) % 256;
	data[id] = ((val * 7)% 256) << 16 | (256 - val) << 8 | abs(128 - val) * 2;
}

float	modulo(__const float x, __const float mod)
{
	float	r;

	r = x / mod;
	r = r - (int)r;
	r *= mod;
	return (r);
}

char4	hsv_to_rgb(__const float __const hue, __const float sat, __const float val)
{
	float	c, x, m, rgb[3];
	char	id_x, id_c, id_0, i;

	c = val * sat;
	x = c * (1 - fabs(fmod(hue / 60, 2) - 1));
	m = val - c;
	i = val / 60;
	id_x = (7 - i) % 3;
	id_c = (2 + i >> 1) % 3;
	id_0 = 3 - (id_x, id_c);
	rgb[id_x] = (x + m) * 255;
	rgb[id_c] = (c + m) * 255;
	rgb[id_0] = (0 + m) * 255;
	return ((char4)(rgb[0], rgb[1], rgb[2], 0));
}

float	get_iter(int id, __const char max_iter, __const char len_trans, __const char len_base)
{
	char	iter;

	iter = 0;
	id /= len_base;
	while ((id % len_trans) == 0 && iter < max_iter)
	{
		id = id / len_trans;
		iter++;
	}
	return ((float)iter);
}


typedef	struct	s_ifs_param
{
	char	len_base;
	char	len_trans;
	char	max_iter;
	char	max_pt;
}				t_ifs_param;


__kernel	void	define_color(__global char4 *col, __global t_ifs_param *p)
{
	// il faut calculer h, s, v
	// puis appeler gentiement la focnitn qui donne les couleurs
	float	hue, sat, val, iter;
	int	id;

	id = get_global_id(0);
	iter = get_iter(id, p[0].max_iter, p[0].len_trans, p[0].len_base);
	hue = ((float) id) / ((float) p[0].max_pt);
	sat = (iter / ((float) p[0].max_iter)) * 360;
	val = sat;
	col[id] = hsv_to_rgb(hue, sat, val);
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

__kernel	void	draw_line(__global int *img, __global float2 *pt, __global char4 *col, __global float2 *dim_ecr)
{
	float2	diff_pos;
	char4	diff_col;
	float2	unit_pos;
	char4	unit_col;
	float2	p;
	char4	c;
	int		indice;
	int		col_value;
	float	dist;
	int		nb_point;
	int		i;
	int		id;
	bool	is_inside;

	id = get_global_id(0);
	diff_pos = pt[id + 1] - pt[id];
	diff_col = col[id + 1] - col[id];
	dist = get_line_length(pt[id], pt[id + 1]);
	nb_point = dist;
	unit_pos = diff_pos / dist;
	unit_col = diff_col / dist;
	i = 0;
	p = pt[id];
	c = col[id];
	while(i < nb_point)
	{
		//	Il faudra ne pas ecrire dans le buffer si on sort de l'ecran
		
		indice = ((int) p.x) + ((int)(p.y * dim_ecr[0].x));
		col_value = (((int)c.x) << 16) | (((int)c.y) << 8) | (((int)c.z));
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
