/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actu_polygone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 05:06:00 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/31 20:56:37 by event100         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h" 

void					actu_polygone_io(t_env *e, t_win *w)
{
	int	r;

	if (!e->actif)
		e->actif = creat_node_fv(0, w->mouse, vect_new_vertfd(255, 255, 255));
	if ((r = check_border_io(e, w, &(e->border_b))) > 0 && (e->base_add) == 0)
		polygone_push_back(&(e->base_model), e->actif);
	else if (r < 0 && (e->base_add) == 0)
		polygone_forget_last(&(e->base_model));
	if ((r = check_border_io(e, w, &(e->border_t))) > 0 && (e->trans_add) == 0)
		polygone_push_back(&(e->trans_model), e->actif);
	else if (r < 0 && (e->trans_add) == 0)
		polygone_forget_last(&(e->trans_model));
}

void					complet_polygone(t_win *w)
{
	if (ft_strcmp(w->name, "param"))
		return ;
	if (mouse_in_border(&(w->e->border_b), w->mouse)
			&& (w->e->base_add) == 0)
		polygone_push_befor_last(&(w->e->base_model), copy_node(w->e->actif
																		, 0));
	if (mouse_in_border(&(w->e->border_t), w->mouse)
			&& (w->e->trans_add) == 0)
		polygone_push_befor_last(&(w->e->trans_model), copy_node(w->e->actif
																		, 0));
}
