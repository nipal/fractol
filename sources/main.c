/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 07:31:16 by fjanoty           #+#    #+#             */
/*   Updated: 2017/06/15 17:11:17 by fjanoty          ###   ########.fr       */
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
	if (ac == 2)
	{
		e.status = SERVEUR;
//			signal(SIGINT, close_sockets);
		e.port = atoi(av[1]);
		e.sock = create_server(e.port);
		get_server_socket(e.sock);
		FD_ZERO(&(e.read_fd));
		FD_SET(e.sock, &(e.read_fd));
		get_env(&e);
		env(&e);
	}
	else if (ac == 3)
	{
		e.status = CLIENT;
		e.port = atoi(av[1]);
		e.sock = create_client(av[2], e.port);
		get_client_socket(e.sock);
		FD_ZERO(&(e.read_fd));
		FD_SET(e.sock, &(e.read_fd));
		get_env(&e);
		env(&e);
	}
	else
	{
		printf("usage serveur	:	%s	port_number\n", av[0]);
		printf("usage client	:	%s	port_number local_server_ip\n", av[0]);
	}

	return (0);
}
