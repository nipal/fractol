/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 07:31:16 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/30 01:07:36 by fjanoty          ###   ########.fr       */
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
	int                 port;


	if (ac == 2)
	{
		bzero(&e, sizeof(t_env));

		signal(SIGINT, close_sockets);
		port = atoi(av[1]);
		e.sock = create_server(port);
		get_server_socket(e.sock);
		FD_ZERO(&(e.read_fd));
		FD_SET(e.sock, &(e.read_fd));
		get_env(&e);
		env(&e);
//			while (42)
//				wait_for_event(e.sock, &(e.read_fd));
	}
	else
	{
		printf("usage:	%s	port_number\n", av[0]);
	}

	return (0);
}
