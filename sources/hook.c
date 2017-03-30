/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 01:26:10 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/30 05:01:35 by fjanoty          ###   ########.fr       */
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
**	On re desine surtout la fenetre de parametrage et on actualise les transformation
*/

void	draw_param_ui(t_env *e)
{
	t_polygone		*color;

	t_border border_abox;
	init_border(&border_abox, SIZE_PARAM_X / 3	, 2 * SIZE_PARAM_X / 3, 0, SIZE_PARAM_Y / 2);
	print_anime_box(e->param, e->trans_model, NULL, &border_abox);
	
	/////////////

	color = NULL;	
	draw_the_2_border(e);
	draw_simple_polygone(e->param, e->trans_model);
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
	actu_win_rest(e->param);

	draw_ellipsoide(e->param, e->base_model);
//		feature_testing(e);

}

int			main_work(t_env *e)
{


	// pour l'atente de nouveu client--> c'est aussi la qu'on peu les ecouter
	// ou pour l'atente de quoi ecrire pou enfin voila
	wait_for_event(e->sock, &(e->read_fd), e->status);
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
