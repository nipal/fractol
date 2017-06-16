/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_printing_koch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nperrin <nperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 23:23:51 by fjanoty           #+#    #+#             */
/*   Updated: 2017/06/16 16:32:12 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void							print_fractal(t_env *e)
{

//	if (e->transform && e->base)
		ocl_render_run(e);
}

/*
	En gros on a besoin d'avoir un truc cool
	genre, une suter structure que j'envoie
	et en suite on la recup[ere proprement en opencl

	et puis on pre remplis le buffer de point avec au moins 4-5 iteration

	Hey mais cette structure a deja ete fait youpiiii


*/

