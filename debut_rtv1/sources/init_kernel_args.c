/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_kernel_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 09:54:57 by fjanoty           #+#    #+#             */
/*   Updated: 2017/01/05 10:08:24 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

typedef	struct	s_arg_info
{
	int			id;
	size_t		size;
	cl_mem		adrr;
	t_arg_info	*next;
}				t_arg_info;

typedef	struct	s_ker_args
{
	int			nb_arg;
	t_arg_info	*firts_arg;
	t_ker_args	*next;	
}				t_ker_args;

/*
**	il faudra determiner le type de memoir a initialiser et la taille.
**	 genre faire un truc scalable au niveau de la memoir.
**	il faudrai aussi essayer de faire passer des structure.
**	il faudrait aussi regarder ce qui se passe avec les commande queu
**	 si il ne faut pas les flush ou un truc du genre (pck il y a trop de fonction a utiliser pour les tuer)
**	on pourrai aussi envisager la liste chainer de ker_args en tableau
**	il faudrait aussi tres serieusement se repencher sur la question des liste chainer generique
*/

/*
**		En vrai pour l'instan je ne vais pas gerer le truc du rechargement des source dynamiquement.
**	parece que je vais encore tomber sur un sujet hyper interessant mais qui va me faire tomber sur d'autre truc
*/
