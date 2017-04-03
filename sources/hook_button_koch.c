/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_buton.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 23:13:18 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/03 03:29:03 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		change_state_anime_box(int prev_id, t_win *w, t_border *b);

void	button_1_param(t_win *w)
{
	w->button1 = 1;
	w->e->id_scrol = select_button(w, w->e->sliders);
	//	la il faudra mettre un truc d'unestructure
	w->e->id_anime_clicked = change_state_anime_box(w->e->id_anime_clicked, w, w->e->border_abox);
	complet_polygone(w);
	if (w->e->add_point && w->e->base_add && w->e->trans_add)
		insert_adding_node(w);
}

void	button_2_param(t_win *w)
{
	int	to_nrm;

	if (mouse_in_border(&(w->e->border_b), w->mouse)
			&& (w->e->base_add++) == 0)
		to_nrm = polygone_forget_last(&(w->e->base_model))
				+ actu_base(w->e, w->e->base_model);
	if (mouse_in_border(&(w->e->border_t), w->mouse)
			&& (w->e->trans_add++) == 0)
		to_nrm = polygone_forget_last(&(w->e->trans_model))
				+ actu_transform(w->e, w->e->trans_model);
	if (w->e->trans_add && w->e->base_add)
		remove_one_node(w->e);
}

int		press_button(int button, int x, int y, t_win *w)
{
	if (button == 1 && !ft_strcmp(w->name, "param"))
	{
		button_1_param(w);
	}
	else if (button == 2 && !ft_strcmp(w->name, "param"))
	{
		button_2_param(w);
	}
//		if (!ft_strcmp(w->name, "fractal"))
//		{
//			if (button == 4 || button == 6)
//				zoom_border(&(w->e->base_cadre), x, y, 0.8);
//			else if (button == 5 || button == 7)
//				zoom_border(&(w->e->base_cadre), x, y, 1.25);
//			else if (button == 1)
//				w->e->move_set = 1;
//			actu_base(w->e, w->e->base_model);
//		}
	return (0);
}

int		release_button(int button, int x, int y, t_win *w)
{
	(void)(x + y);
	w->button1 = 0;
	if (button == 1 && !ft_strcmp("param", w->name))
	{
		if (w->e->id_scrol >= 0)
			actu_base(w->e, w->e->base_model);
		w->e->id_scrol = -1;
	}
//		if (button == 1 && !ft_strcmp(w->name, "fractal"))
//			w->e->move_set = 0;
	return (1);
}

void	actu_mouse_pos(t_win *w, int x, int y)
{
	w->prev_mouse->m[0] = w->mouse->m[0];
	w->prev_mouse->m[1] = w->mouse->m[1];
	w->mouse->m[0] = x;
	w->mouse->m[1] = y;
}
