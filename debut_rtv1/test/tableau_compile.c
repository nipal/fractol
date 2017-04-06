/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tableau_compile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 02:11:13 by fjanoty           #+#    #+#             */
/*   Updated: 2017/01/05 02:17:25 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#define NB_KERNEL 10

int	main()
{
	
	char		*names_kernel[NB_KERNEL];

	names_kernel[0] = "youpi";
	char	*str = names_kernel[0];
	printf("str:{%s}\n", str);
	printf("nk[0]:{%s}\n", names_kernel[0]);
	return (0);
}
