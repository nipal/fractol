/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 12:17:52 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/19 01:12:27 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_exit(t_env *e)
{
	(void)e;
	destroy_mem_ocl(&(e->mem_ocl));
	destroy_ocl(&(e->ocl));
	exit(0);
	return (0);
}