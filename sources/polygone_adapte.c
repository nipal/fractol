/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygone_adapte.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 03:46:55 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/30 05:19:45 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	ca c'est pour reorganiser les adresse des next des liste chianer recu par le reso
void	adapte_polygone_next(t_ifs_param *param)
{
	int	i;

	i = 0;
	while (i < MAX_NODE && param->transform[i]->next)
	{
		param->transform[i]->next = &(param->transform[i + 1]);
		i++;
	}
	param->transform[i]->next = NULL;

	i = 0;
	while (i < MAX_NODE && param->base[i]->next)
	{
		param->base[i]->next = &(param->base[i + 1]);
		i++;
	}
	param->base[i]->next = NULL;
}

t_ifs_param	creat_param_to_send(t_env *e)
{
	t_ifs_param	buffer;
	int			i;
	t_polygone	*node

	node = e->transform;
	for (i = 0; i < MAX_NODE; i++)
	{
		if (node)
		{
			
			node = node->next;
		}
	}

	node = e->transform;
}

