/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 07:31:16 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/19 02:20:25 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#include <stdio.h>	
#include <stdlib.h>

#include <OpenCL/opencl.h>


int main()
{	
	init_ocl_error();
	run_rtv1();
	return 0;
}

