/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ovaloide.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 23:01:53 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/26 23:16:40 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	Il faudait en fait avoir [plusieur case] (genre max 8 ou 9)
**	pour chaque case, le fenetre de poreview permet de les parametrer, a terme ona  une mini preview dans les case
**	le but c'est de pouvoir associer ces petite case a des segemnt et davoir encore une autre preview general
**	
**	Il lui faudrai une [petite bordure] pour la fenetre de poreview/parametrage de l'animation 
**		- dedans on [reglerai] separement (la shape) et (l'ecouclement du temps) on pourrait aussi avoir des coef multiplicateur (x1 => lent || x30 => tres rapide)
**		- 
**	il faudrait en suite 
*/

/*
**	Un ovaloid c'est avant tout un segment:
**		-node0	->	centre
**		-node1	->	x1
**		-node2	->	y1
**
**	les vecteur sont plus ou moins lier:
**		- modifier l'angle de x1 fait varier l'angle de y1 (et inversement) ==> bonus??
**		- le module de x1 ne peu pas etre negatif pck c'est sur lui qu'on se base mais y1 ou pck il donne le sens de parcourt du cercle
**		- 
*/

/*
**	On va commencer par faire une bordure de preview
*/
