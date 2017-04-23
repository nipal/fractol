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

typedef	struct	s_ifs_spec
{
	int		len_base;
	int		len_trans;
	int		max_iter;
	int		max_pt;
	int		ecr_x;
	int		ecr_y;
}				t_ifs_spec;


__kernel void test_image(__global int *time, __global int *data)
{
	int	id = get_global_id(0);
	int	val;
	
	val = (id + *time) % 256;
	data[id] = ((val * 7)% 256) << 16 | (256 - val) << 8 | abs(128 - val) * 2;
}
char4	hsv_to_rgb(__const float hue, __const float sat, __const float val);
float	get_iter(int id, __const char max_iter, __const char len_trans, __const char len_base);
float	get_line_length(float2 p1, float2 p2);
void	print_spec(t_ifs_spec *spec);

void	print_spec(t_ifs_spec *spec)
{
	printf("len_base:%d	len_trans:%d	max_iter:%d	max_pt:%d	ecr_x:%d	ecr_y:%d\n", spec->len_base, spec->len_trans, spec->max_iter, spec->max_pt, spec->ecr_x, spec->ecr_y);
}

char4	hsv_to_rgb(__const float hue, __const float sat, __const float val)
{
	float	c, x, m, rgb[3];
	char	id_x, id_c, id_0, i;

	c = val * sat;
	x = c * (1 - fabs(fmod(hue / 60, 2) - 1));
	m = val - c;
	i = val / 60;
	id_x = (7 - i) % 3;
	id_c = (2 + (i >> 1)) % 3;
	id_0 = 3 - (id_x + id_c);
	rgb[id_x] = (x + m) * 255;
	rgb[id_c] = (c + m) * 255;
	rgb[id_0] = (0 + m) * 255;
	return ((char4)(rgb[0], rgb[1], rgb[2], 0));
}

float	get_iter(int id, __const char max_iter, __const char len_trans, __const char len_base)
{
	char	iter;

	iter = 0;
	id /= (len_base - 1);
	while ((id % (len_trans + 1)) == 0 && iter < max_iter)
	{
		id = id / (len_trans + 1);
		iter++;
	}
	return ((float)iter);
}


__kernel	void	define_color(__global char4 *col, __global t_ifs_spec *spec)
{
	// puis appeler gentiement la focnitn qui donne les couleurs
	float	hue, sat, val, iter;
	int	id;

	id = get_global_id(0);
	iter = get_iter(id, spec[0].max_iter, spec[0].len_trans, spec[0].len_base);
	hue = ((float) id) / ((float) spec[0].max_pt);
	sat = (iter / ((float) spec[0].max_iter)) * 360;
	val = sat;
	col[id] = hsv_to_rgb(hue, sat, val);

//	printf("spec->ecrX:%d	spec->ecrY:%d\n", spec->ecr_x, spec->ecr_y);
}

float	get_line_length(float2 p1, float2 p2)
{
	int		id_max;
	int		max_p[2];

	max_p[0] = p1.x - p2.x;
	max_p[1] = p1.y - p2.y;
	max_p[0] *= (max_p[0] > 0) ? 1 : -1; 
	max_p[1] *= (max_p[1] > 0) ? 1 : -1; 
	id_max = (max_p[0] > max_p[1]) ? 0 : 1;

//	printf("p1:{%f, %f}	p2:{%f, %f}\n", p1.x, p1.y, p2.x, p2.y);
//	printf("max[0]:%d	max[1]:%d\n", max_p[0], max_p[1]);
	return (max_p[id_max]);
}

__kernel	void	draw_line(__global int *img, __global float2 *pt, __global char4 *col, __global t_ifs_spec *spec)
{
	float2	diff_pos;
	float4	diff_col;
	char4	dc;
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
	diff_pos = pt[id + 1] - pt[id];
	dc = col[id + 1] - col[id];
	diff_col = (float4)(dc.x, dc.y, dc.z, 0);
	dist = get_line_length(pt[id], pt[id + 1]);
	nb_point = dist;
	unit_pos = diff_pos / dist;
	unit_col = diff_col / dist;
	i = 0;
	p = pt[id];
	c = (float4)(col[id].x, col[id].y, col[id].z, 0);
	while(i <= nb_point)
	{
		indice = ((int) p.x) + (int)((int)(p.y) * spec->ecr_x);
		col_value = ((((int)c.x) & 0xFF) << 16) | ((((int)c.y) & 0xFF) << 8) | ((((int)c.z)) & 0xFF);
		is_inside = (p.x >= 0 && p.x < spec[0].ecr_x && p.y >= 0 && p.y < spec[0].ecr_y);	
		if (is_inside)
			img[indice] = col_value;
// printf("line[%d][%d]==>	ok(%d)	p.x:%f	p.y:%fcol:[%d][%d][%d]=%d\n", id, i, is_inside, p.x, p.y, ((int)c.x),  ((int)c.y),  ((int)c.z), col_value);
// printf("line[%d][%d]==>	ok(%d)	p.x:%f	p.y:%fcol:[%d][%d][%d]=%d\n", id, i, is_inside, p.x, p.y, ((int)c.x),  ((int)c.y),  ((int)c.z), col_value);
// printf("ecr_X:%f	ecr_Y:%f\n", spec->ecr_x, spec->ecr_y);
// printf("=========spec->ecrX:%d	spec->ecrY:%d\n", spec->ecr_x, spec->ecr_y);
		p += unit_pos;
		c += unit_col;
		i++;
	}
//printf("p1[%d]:{%f, %f};	p2[%d]:{%f, %f}\n", id, pt[id].x, pt[id].y, (id + 1), pt[id + 1].y, pt[id + 1].y);

//	printf("len_base:%d	len_trans:%d	max_iter:%d	max_pt:%d	ecr_x:%d	ecr_y:%d\n", spec->len_base, spec->len_trans, spec->max_iter, spec->max_pt, spec->ecr_x, spec->ecr_y);
//print_spec(spec);
//	printf("nb_point:%d\n", nb_point);		
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

__kernel	void	calcul_ifs_point(__global float2 *pt_ifs
									, __global float2 *transform
									, __global int *beg_data_id
									, __global int *trans_len
									, __global int *num_iter)
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
	id_trans = glob_id % (trans_len[0] + 1);
	id_parent = (glob_id / (trans_len[0] + 1)) + beg_data_id[num_iter[0]];
	id_now = glob_id + beg_data_id[num_iter[0]];

	ux = pt_ifs[id_parent + 1] - pt_ifs[id_parent];
	uy = (float2)(-ux.y, ux.x);

	pt_ifs[id_now] = pt_ifs[id_parent] + transform[id_trans].x * ux + transform[id_trans].y * uy;


	//printf("calcul:%d	========	dad_1:{%f, %f} dad_2:{%f, %f}	tr[%d]:{%f, %f}\n", glob_id, pt_ifs[id_parent - 1].x, pt_ifs[id_parent - 1].y, pt_ifs[id_parent].x, pt_ifs[id_parent].y, id_trans, transform[id_trans].x, transform[id_trans].y);

//	printf("glob_id:%d	id_current:%d	id_parent:%d	id_trans:%d		len_trans:%d	num_iter:%d\n", glob_id, id_now, id_parent, id_trans, trans_len[0], num_iter[0]);
}
