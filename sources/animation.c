/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 15:50:03 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/04 22:35:01 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_anime	lst_anime[MAX_NODE];

int				init_t_anime(t_anime *anime, t_border *b_anime, t_border *b_speed, t_border *b_offset);
void			init_lst_anime(t_env *e);
t_polygone		*init_ovaloid(t_border *b);

void	init_lst_anime(t_env *e)
{
	t_border	*bord_speed;
	t_border	*bord_offset;
	int			i;
	int			border = 7;
	int			height = 40;

	bord_speed = malloc(sizeof(t_border));
	bord_offset = malloc(sizeof(t_border));
	init_border(bord_offset, 2 * SIZE_PARAM_X / 3 + border, SIZE_PARAM_X - border,
							SIZE_PARAM_Y / 3 - height + border , SIZE_PARAM_Y / 3 - border);
	init_border(bord_speed, 2 * SIZE_PARAM_X / 3 + border, SIZE_PARAM_X - border,
							SIZE_PARAM_Y / 3 + border, SIZE_PARAM_Y / 3 + height - border);
	i = 0;
	while (i < MAX_NODE)
	{
		init_t_anime(lst_anime + i, &(e->border_p), bord_speed, bord_offset);
		i++;
	}
	e->border_speed = bord_speed;
}

int			init_t_anime(t_anime *anime, t_border *b_anime, t_border *b_speed, t_border *b_offset)
{
	t_matrix	*col_speed, *col_offset;

	if (!(col_speed = vect_new_vertfd(63, 205, 225))
		|| !(col_offset = vect_new_vertfd(63, 106, 225)))
		return (1);
	anime->ovaloide = init_ovaloid(b_anime);

	//	init_slider
	anime->speed = init_slider(col_speed, b_speed); 
	anime->offset = init_slider(col_offset, b_offset); 
	anime->speed->v1 = 0;
	anime->offset->v1 = 0;
	matrix_free(&col_speed);
	matrix_free(&col_offset);
	return (0);
}

//	pour mapper 
t_polygone		*init_ovaloid(t_border *b)
{
	t_polygone	*beg = NULL;
	t_matrix	*col = NULL;
	double	width, height, delta, mid_x, mid_y;

	col = vect_new_vertfd(50, 50, 50);
	width = b->x1 - b->x0;
	height = b->y1 - b->y0;
	mid_x = b->x0 + width / 2;
	mid_y = b->y0 + height / 2;
	delta = 30;

	beg = creat_node_fv(0, vect_new_vertfd(mid_x + delta, mid_y, 0), col);
	beg->next = creat_node_fv(0, vect_new_vertfd(mid_x, mid_y, 0), col);
	beg->next->next = creat_node_fv(0, vect_new_vertfd(mid_x, mid_y - delta, 0), col);
	return (beg);	
}

//	pour chaque node on dessine une preview du chemin
//
void		draw_preview_path(t_env *e)
{
	int	id_anime;
//	static	t_matrix	*col = NULL;

	id_anime = e->id_anime_clicked;
//	if (!col)
//		col = tsl_to_rvb_new(0,1,1);


	//	ovaloide
	draw_ellipsoide(e->param, lst_anime[id_anime].ovaloide);	
	draw_simple_polygone(e->param, lst_anime[id_anime].ovaloide);
	//	bouton
	draw_slider(e->param, lst_anime[id_anime].speed, 1);	
	draw_slider(e->param, lst_anime[id_anime].offset, 1);	
}

void		scrol_button_anime(t_win *w, t_anime *anime)
{
	//	si on a cliquer ET qu'on est dans la zone
	//	button speed
	if (w->button1 && mouse_in_border(anime->speed->border, w->mouse))	
		scroling_button(w, anime->speed, 0);
	else if (w->button1 && mouse_in_border(anime->offset->border, w->mouse))	
		scroling_button(w, anime->offset, 0);
}

//	utiliser move_the_node(t_env e, t_polygone *seg)
//	pour deplacer les segment
//
//	sinspire motion cursor dans new_hook
//
//t_matrix	*vect_new_vertfd(double a, double b, double c)
