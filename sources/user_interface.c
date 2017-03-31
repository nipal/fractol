/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 06:12:19 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/31 04:45:15 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	la on va implenter toute les 
*/

/*
**	bon moi la j'ai envie de desiner des rectangle dans une border
**	et puis de refaire toute l'interface avec les parametre d'animation
*/

/*
**	mon cas particulier des rectangle d'anime
**	- on dessinne auttant de rectagle que de node
**	--> Comment on fait l'association en cas d'ajout a l'interieur ?
**		--> peut etre qu'om ne gerera pas ca pck l'utilisateur ca serra moi?
**		--> si non l'ajout de node insert aussi 
**	- on dessine tout les rectangle avec un degrader de couleur
**	- on assosier aussi les node avec des petit rond de la meme couleur
**
**	il y a se systeme de faire que l'onglet actif (de base le premier)
**		soit celui a qui la zone de craft_shape et celle de define exec_time 
**		fassent reference
**
**	- IL FAUT AUSSI qu'il y ai une structure super badasse qui stoque
**		toute les info de parame de shape et de TOUT
**	
**	- IL FAUT AUSSI pouvoir faire la meme chose sur les truc
**
**	|
**	|
**	v
*/

/*
**	Les "anime" sont un tableau de structure qui stoque les param 

**	tout basiquement on va fair eun truc 
**	on veux dessinner des petit cercle plein sur le truc le segment de transformation
**	on veux aussi 
*/

//	en gros on n;aurra jamais plus que 16 si non artung
# define BOX_BY_LINE 4
# define LINE_BOX_MAX 4
# define MINI_CIRCLE 7 

//	pour changer l'id de l'anime_bix cliquer, il faut lui dir dans quel t_border elle est
int		select_anime_box(t_win *w, t_border *b)
{
	int		col, line, id, nb_anime_box;
	double	width, height, x, y, unite_x, unite_y;

	if (mouse_in_border(b, w->mouse))
	{
		nb_anime_box = get_polygone_len(w->e->trans_model);
		width = (b->x1 - b->x0);
		height = (b->y1 - b->y0);
		x = w->mouse->m[0] - b->x0;
		y = w->mouse->m[1] - b->y0;
		unite_x = width / BOX_BY_LINE;
		unite_y = width / LINE_BOX_MAX;

		col = (int)(x / unite_x); 
		line = (int)(y / unite_y); 
		id = col + line * BOX_BY_LINE;
		if (id < nb_anime_box)
			return (id);
	}
	return (0);
}

//	dessinner un carrer rouge autoure des truc selectioner, on peu le faire dans pab
void	print_anime_box(t_win *w, t_polygone *poly, t_anime *anime, t_border *b)
{
	int			nb_box;
	int			i;
	int			margin;
	double		value;
	int			unite_width;
	int			unite_height;
	t_matrix	*col;
	t_border	place;
	t_polygone	*node;
	


	//	la on dessine les rectangle dans la bordure qu'on nous envoie
	margin = 4;
	unite_width = (b->x1 - b->x0) / BOX_BY_LINE;
	unite_height = (b->y1 - b->y0) / LINE_BOX_MAX;
	nb_box = get_polygone_len(poly);
	node = poly;

	if (!(col = tsl_to_rvb_new(120, 0.9, 0.8)))
		return ;
	i = w->e->id_anime_clicked;
	place.x0 = ((i % BOX_BY_LINE) * unite_width) + b->x0;
	place.x1 = (((i % BOX_BY_LINE) + 1) * unite_width) + b->x0;
	place.y0 = (((i / BOX_BY_LINE)) * unite_height) + b->y0;
	place.y1 = (((i / BOX_BY_LINE) + 1) * unite_height) + b->y0;
	paint_rectangle(w, col, &place);
	matrix_free(&col);

	i = 0;
	while (i < nb_box && node && i < 16)
	{
		place.x0 = ((i % BOX_BY_LINE) * unite_width) + margin + b->x0;
		place.x1 = (((i % BOX_BY_LINE) + 1) * unite_width) - margin + b->x0;
		place.y0 = (((i / BOX_BY_LINE)) * unite_height)+ margin + b->y0;
		place.y1 = (((i / BOX_BY_LINE) + 1) * unite_height) - margin + b->y0;
		value = ((double)i + 1) / ((double)nb_box + 2);
		if (!(col = tsl_to_rvb_new(120, 0.3, value)))
			return ;
		paint_rectangle(w, col, &place);	// la on dessine le rectangle dans le cardre ou il faut 
		paint_circle(node->pos, col, MINI_CIRCLE, w); // la on dessinne le cercle associer
		matrix_free(&col);
		node = node->next;
		i++;
	}
	

}
