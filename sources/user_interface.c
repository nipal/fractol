/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 06:12:19 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/27 10:08:40 by fjanoty          ###   ########.fr       */
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
*/

void	print_anime_box(t_win *w, t_polygone *poly, t_anime *anime, t_border *b)
{

}
