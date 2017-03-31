/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 15:50:03 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/31 18:39:27 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_anime	lst_anime[MAX_NODE];

int				init_t_anime(t_anime *anime, t_border *b_anime, t_border *b_speed);
void			init_lst_anime(t_env *e);
t_polygone		*init_ovaloid(t_border *b);

void	init_lst_anime(t_env *e)
{
	t_border	*bord_speed;
	int			i;
	int			border = 5;
	int			height = 15;


	bord_speed = malloc(sizeof(t_border));
	init_border(bord_speed, 2 * SIZE_PARAM_X / 3 + border,
							SIZE_PARAM_X - border,
							SIZE_PARAM_Y / 3 - height,
							SIZE_PARAM_Y / 3 + height);
	i = 0;
	while (i < MAX_NODE)
	{
		init_t_anime(lst_anime + i, &(e->border_p), bord_speed);
		i++;
	}
}

int			init_t_anime(t_anime *anime, t_border *b_anime, t_border *b_speed)
{
	anime->ovaloide = init_ovaloid(b_anime);

	//	init_slider
	anime->speed = init_slider(NULL, b_speed); 
	return (0);
}

//	t_slider	*create_speed_slider(t_border *b)
//	{
//		return (NULL);	
//	}
//	
//	//	fonction de seleciton
//	
//	//	la on malloc a la bonne taille
//	t_polygone	*create_ovaloid()
//	{
//		return (NULL);	
//	}

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
void		draw_preview_path(t_anime *node_anime)
{
	t_matrix	*col;
}

//	utiliser move_the_node(t_env e, t_polygone *seg)
//	pour deplacer les segment
//
//	sinspire motion cursor dans new_hook
//
//t_matrix	*vect_new_vertfd(double a, double b, double c)
