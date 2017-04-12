/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:26:02 by fjanoty           #+#    #+#             */
/*   Updated: 2017/04/12 20:49:32 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_include.h"
#include <stdio.h>

int	main()
{
	t_ocl_core	core;
	t_ocl_ker	calcul_ifs;
//	t_ocl_ker	draw_line;
	int			ret_error;

	if((ret_error = init_ocl_core(&core, "test_kernel.cl")))
	{
		printf("error on initialisation opencl core:%d\n", ret_error);
		return (1);
	}
	else if ((ret_error = init_kernel(&core, &calcul_ifs, "calcul_ifs_point")))
	{
		printf("errpr on initialisation kernel\n");
		return (1);
	}
	else
	{
		printf("All is well\n");
	}
	return (0);
}

/*
 *	Donc la il faut continuer l'initialisation et et faire les truc d'allocation de memoir et de
 *	binding avec les argument et lancer les kernel et faire plein de truc donc dans pas trop longtemps
 *	integrer les fichier au fractole
 * */
