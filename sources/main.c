/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 07:31:16 by fjanoty           #+#    #+#             */
/*   Updated: 2017/12/06 17:58:21 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "fractol.h"

t_env	*get_env(t_env *e)
{
	static	t_env	*env = NULL;

	if (e)
	{
		env = e;
	}
	return (env);
}

int		main(int ac, char **av)
{
	t_env				e;

	bzero(&e, sizeof(t_env));
	get_env(&e);
	env(&e);



	return (0);
}
