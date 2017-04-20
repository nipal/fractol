/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_init_ifs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 05:18:36 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/20 07:48:05 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
	La on va faire tout les baille pas generique mais qui sont globale a tous les kernel du projet
*/

int	init_ifs(t_env *e, t_win *w)
{
 	size_t	size_buff_pt;
	size_t	size_colore;
	size_t	size_img;
	int		nb_pt;

	//	on a la taille max du system (pour un buffer)
	//		==> il faudra voir si on peu utiliser plusieur buffer
	//			ou si il y a une histoire de buf max en mem temps
	//	on en deduit le nombre de point max
	//	on en deduit la couleur
	//	ou si non on fait des buffeur tres tres gros et c'est plus tard que on gerera le reste
	
	size_img = w->size_x * e->size_y * sizeof(int);
	init_mem_calcul_ifs(e->ocl, e->ker[e_ifs_calcul_pt]);
	ocl_mem_creat_define_color(e->ker[e_define_color], size_colore)
	ocl_mem_creat_draw_line(e->ocl, e->ker[e_draw_line], size_img, size_buff_pt, t_ocl_mem *arg1, t_ocl_mem *arg2)
}
