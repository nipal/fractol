/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 01:26:10 by fjanoty           #+#    #+#             */
/*   Updated: 2017/06/25 20:05:24 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fractol.h"

void		size_window_copy(double pos_low[4], double pos_height[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		pos_height[i] = pos_low[i];
		i++;
	}
}

void		play_mandel(int x, int y, t_env *e)
{
	e->zoom_finished = 0;
	e->zoom_on = 1;
	e->zoom_x = x;
	e->zoom_y = y;
}

void		init_pos_ecr(t_env *e)
{
	e->pos_low[0] = -2;
	e->pos_low[1] = -2;
	e->pos_low[2] = 2;
	e->pos_low[3] = 2;
	e->pos_height[0] = -2;
	e->pos_height[1] = -2;
	e->pos_height[2] = 2;
	e->pos_height[3] = 2;
}

/*
 * On va modifier un truc qui pourrait etre le truc de transformation en mode middle ware
 * du coup on va le lancer a chaque tour de boucle
*/
t_polygone	*apply_ellipse_anime(t_polygone *org)
{
	t_polygone	*node, *prev, *beg;
	t_matrix	*tmp, *pos, *col;
	int			i;
	double		the_time;

	beg = NULL;
	prev = NULL;
	the_time = (((double)(time_prg % periode))/(double) periode);
	if (!org || !(col = vect_new_vertfd(40, 170, 70)))
		return (NULL);
	i = 0;
	while (org)
	{
		if (!(tmp = ellipsoide_shape(lst_anime[i].ovaloide, get_time_ellipse_anime(get_env(NULL), lst_anime + i)))
			|| !(pos = matrix_add(tmp, org->pos)))
			return (NULL);
		node = creat_node(0, pos->m, col->m); 
		if (prev)
			prev->next = node;
		else
			beg = node;
		prev = node;
		org = org->next;
		matrix_free(&pos);
		matrix_free(&tmp);
		i++;
	}
	matrix_free(&col);
	return (beg);
}

//	la on va dessiner pour tout les anime_box disponible
void		draw_preview_anime(t_win *w)
{
	int	i;
	int	len;
	t_polygone	*node;

	len = get_polygone_len(w->e->trans_model);
	node = w->e->trans_model;
	i = 0;
	while (i < len && node)
	{
		draw_preview_one_anime(w, lst_anime + i, node->pos, get_time_ellipse_anime(w->e, lst_anime + i));
		node = node->next;
		i++;
	}
}

/*
**	On re desine surtout la fenetre de parametrage et on actualise les transformation
*/

void	draw_param_ui(t_env *e)
{
	t_polygone		*color;

	print_anime_box(e->param, e->trans_model, NULL, e->border_abox);
//	draw_preview_anime(e->param);
	
	/////////////

	color = NULL;	
	draw_the_2_border(e);
//		draw_simple_polygone(e->param, e->trans_model);
	draw_simple_polygone(e->param, e->base_model);
	if (mouse_in_border(&(e->border_b), e->param->mouse) && e->base_add > 0)
		color = get_closer_node(e->base_model, e->param->mouse, e->r_select);
	if (mouse_in_border(&(e->border_t), e->param->mouse) && e->trans_add > 0)
		color = get_closer_node(e->trans_model, e->param->mouse, e->r_select);
	if (color)
		print_circle2(color->pos, NULL, e->r_select, e->param);
	if (e->id_scrol >= 0)
		scroling_button(e->param, e->sliders[e->id_scrol / 2], e->id_scrol % 2);
		draw_the_sliders(e->param, e->sliders);
	(e->add_point && e->base_add && e->trans_add) ? draw_prewiew(e->param)
		: (void)e;
	//////////////
	draw_preview_path(e);	//	dans le care de preview (ou parametrage de la courbe)
	draw_preview_anime(e->param); // dans le carrer de frabrication de rransmodel on montrer les animation
	draw_simple_polygone(e->param, e->trans_model2);	// le segment de transformation moduler par l'animation
	scrol_button_anime(e->param, lst_anime + e->id_anime_clicked);
	//////////////
	actu_win_rest(e->param);
//	print_fractal(e);
//		draw_ellipsoide(e->param, e->base_model);
//		feature_testing(e);

}

float	cross(float x1, float y1,float x2, float y2)
{
	return (x1 * x2 + y1 * y2);
}

void	nrm(float vec[2], float fact)
{
	vec[0] *= fact;
	vec[1] *= fact;
}

void	print_direct_trans(t_env *e)
{
	t_polygone	*node;
	char		c;
	float		x, y;

	node = e->transform;
	printf("{");
	printf("{%f, %f}, ", 0.0, 0.0);
	while (node)
	{
		x = node->pos->m[0];
		y = node->pos->m[1];
		printf("{%f, %f} ", x, y);
		node = node->next;
	}
	printf("{%f, %f} ", 1.0, 0.0);
	printf("},\n");
}

void	print_param(t_env *e)
{
	int			i;
	int			end;
	float		beg_pos[MAX_NODE][2];
	float		norme_pos[MAX_NODE][2];
	float		rot[MAX_NODE][3][2];
	float		ux[2], uy[2], org[2], dist;
	t_polygone	*node;
	float tmp_x, tmp_y;

	i = 0;
	node = e->trans_model;
	if (node)
	{
		//	GET beg_pos
		while (node && i < MAX_NODE)
		{
			beg_pos[i][0] =  node->pos->m[0];
			beg_pos[i][1] =  node->pos->m[1];
//			printf("{%f, %f}, ", beg_pos[i][0], beg_pos[i][1]);
			node = node->next;
			i++;
		}
		end = i - 1;
//		printf("\n");
		//	Def ux, uy
		if (i >= 2)
		{
			org[0] = beg_pos[0][0];
			org[1] = beg_pos[0][1];
			ux[0] = beg_pos[end][0] - beg_pos[0][0];
			ux[1] = beg_pos[end][1] - beg_pos[0][1];
			dist = sqrt(ux[0] * ux[0] + ux[1] * ux[1]);
			nrm(ux, 1.0 / dist);
		//	nrm(uy, 1.0 / dist);
			uy[0] = -ux[1];
			uy[1] = ux[0];

//			printf("{%f, %f}, {%f, %f}\n", ux[0], ux[1], uy[0], uy[1]);
//			printf("---------->	");
			i = 0;
			while (i <= end)
			{

				norme_pos[i][0] = beg_pos[i][0] - org[0];
				norme_pos[i][1] = beg_pos[i][1] - org[1];
				tmp_x = cross(norme_pos[i][0], norme_pos[i][1], ux[0], ux[1]) / dist;
				tmp_y = cross(norme_pos[i][0], norme_pos[i][1], uy[0], uy[1]) / dist;
				norme_pos[i][0] = tmp_x;
				norme_pos[i][1] = tmp_y;
//				printf("{%f, %f}, ", norme_pos[i][0], norme_pos[i][1]);
				i++;
			}
//			printf("\n");

			
			for (i = 0; i <= end; i++)
			{
				//	on copie
				rot[i][0][0] = lst_anime[i].ovaloide->pos->m[0];
				rot[i][0][1] = lst_anime[i].ovaloide->pos->m[1];
				rot[i][1][0] = lst_anime[i].ovaloide->next->pos->m[0];
				rot[i][1][1] = lst_anime[i].ovaloide->next->pos->m[1];
				rot[i][2][0] = lst_anime[i].ovaloide->next->next->pos->m[0];
				rot[i][2][1] = lst_anime[i].ovaloide->next->next->pos->m[1];
			

				// on calcul
				rot[i][0][0] = (rot[i][0][0] - rot[i][1][0]) / dist;
				rot[i][0][1] = (rot[i][0][1] - rot[i][1][1]) / dist;

				rot[i][1][0] = (rot[i][2][0] - rot[i][1][0]) / dist;
				rot[i][1][1] = (rot[i][2][1] - rot[i][1][1]) / dist;

				// on change de repere
				
				tmp_x = cross(rot[i][0][0], rot[i][0][1], ux[0], ux[1]);
				tmp_y = cross(rot[i][0][0], rot[i][0][1], uy[0], uy[1]);
				rot[i][0][0] = tmp_x;
				rot[i][0][1] = tmp_y;

				tmp_x = cross(rot[i][1][0], rot[i][1][1], ux[0], ux[1]);
				tmp_y = cross(rot[i][1][0], rot[i][1][1], uy[0], uy[1]);
				rot[i][1][0] = tmp_x;
				rot[i][1][1] = tmp_y;
				float speed = (1 - (lst_anime[i].speed->v2 - lst_anime[i].speed->v1)) * 10;
				float offset = (1 - (lst_anime[i].offset->v2 - lst_anime[i].offset->v1));
				printf(" {%f, %f, %f, %f, %f, %f, %f, %f},\n", norme_pos[i][0], norme_pos[i][1], rot[i][0][0], rot[i][0][1], rot[i][1][0], rot[i][1][1], speed, offset);
			}
			printf("-----------------------------\n");
		}
//	-------------------- TRANS_POS normalized -------------------
		
		
	}
}


int time_prg = 0;	
int	periode = 10000;

int			main_work(t_env *e)
{
	gettimeofday(&(e->time),NULL);

	// pour l'atente de nouveu client--> c'est aussi la qu'on peu les ecouter
	// ou pour l'atente de quoi ecrire pou enfin voila
//	wait_for_event(e->sock, &(e->read_fd), e->status);

	/////////////////////////////
	polygone_destroy(&(e->trans_model2));
	e->trans_model2 = apply_ellipse_anime(e->trans_model);
	polygone_destroy(&(e->transform));
	e->transform = transform(e->trans_model2);
//	--------------------------
//	print_param(e);
//	--------------------------
	print_fractal(e);
	//////////////

	if (e->status == SERVEUR)
		draw_param_ui(e);
	else if (e->status == CLIENT)
	{
		// la il faudra faire les truc de dessin pour le client pck il n'a pas d'event
		// et puis oil n'as pas le droit de sessiner ce qu'il veut.
		// depuis quand le cient est roi?
	}
	return (1);
}
