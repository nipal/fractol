/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useless_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 04:52:52 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/28 04:56:51 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	r[0] la distance du clique au centre du bouton
*/

//	
//	int			select_button(t_win *w, t_slider **tab)
//	{
//		double	dist;
//		double	pos_button[2];
//		double	delta[2];
//		double	val;
//		double	res[2];
//		double	min_dist;
//		int		i;
//	
//		i = 0;
//		while (tab[i / 2])
//		{
//			if (mouse_in_border(tab[i / 2]->border, w->mouse))
//			{
//				printf("OUIIIII:::::	=>%d\n", i);
//			}
//			draw_border(w, tab[i / 2]->border, tsl_to_rvb_new(120, 0.8, 0.7));
//			delta[0] = abs(tab[i / 2]->border->x1 - tab[i / 2]->border->x0);
//			delta[1] = abs(tab[i / 2]->border->y1 - tab[i / 2]->border->y0);
//			val = (i % 2) ? tab[i / 2]->v1 : tab[i / 2]->v2;
//			pos_button[0] = delta[0] * val + tab[i / 2]->border->x0;
//			pos_button[1] = delta[1] / 2 + + tab[i / 2]->border->y0;
//			res[0] = pos_button[0] - w->mouse->m[0];
//			res[1] = pos_button[1] - w->mouse->m[1];
//			dist = sqrt(res[0] * res[0] + res[1] * res[1]);
//			printf("delta__X:%f	delta__Y:%f\n", delta[0], delta[1]);
//			printf("button_X:%f	button_Y:%f\n", pos_button[0], pos_button[1]);
//			printf("mouse__X:%F	mouse__Y:%f\n", w->mouse->m[0], w->mouse->m[1]);
//			printf("dist:%f\n\n", dist);
//			if (dist <= delta[1] + 2)
//				return (i);
//			i++;
//		}
//		return (-1);
//	}
//	


