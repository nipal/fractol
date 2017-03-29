/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 22:39:08 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/30 01:08:21 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# define STACK_SIZE 100
//	int				get_server_socket(int ss);
//	int				*get_all_open_sockets(int new_socket);
//	static	void	close_sockets(int s);
//	static	int		create_server(int port);
//	void			add_new_client(int new_sock);
//	static	void	wait_for_event(int sock, fd_set *active_fd);
//	


int	get_server_socket(int ss)
{
	static	int	server_socket = 0;

	if (ss == 0)
	{
		return (server_socket);
	}
	else
	{
		server_socket = ss;
		return (server_socket);
	}
}

int	*get_all_open_sockets(int new_socket)
{
	static	int	id_add = 0;
	static	int	all_client_socket[STACK_SIZE];

	if (new_socket > 0)
	{
		all_client_socket[id_add] = new_socket;
		id_add++;
	}
	return (all_client_socket);
}

void     close_sockets(int s)
{
	static	int	first_time = 1;
	int     ss;
	int     *socks;

	(void)s;
	if (!first_time)
		exit(0) ;
	first_time = 0;
	if ((ss = get_server_socket(0)))
		close(ss);
	socks = get_all_open_sockets(-1);
	for (int i = 0; socks[i]; i++)
	{
		printf("socket [%d] closed\n", socks[i]);
		shutdown(socks[0], 2);
	}
	ft_exit(get_env(NULL));
}


int          create_server(int port)
{
	int                 sock;
	struct protoent     *proto;
	struct sockaddr_in  sin;

	proto = getprotobyname("tcp");
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		printf("cant bind port: %i\n", port), exit(-1);
	printf("Server connected on port %i\n", port);
	listen(sock, STACK_SIZE);
	return (sock);
}

//	void	add_new_client(int new_sock)
//	{
//		get_all_open_sockets(new_sock);
//	}


/*
**	C'ette fonction serra appeler en boucle
*/
void     wait_for_event(int sock, fd_set *active_fd)
{
	struct			timeval timeout;
	struct          sockaddr_in clientname;
	socklen_t       size;
	fd_set          read_fd;
	int             new_sock;

	timeout.tv_sec = 0;
	timeout.tv_usec = 2000;
	read_fd = *active_fd;
	if (select(FD_SETSIZE, &read_fd, NULL, NULL, &timeout) < 0)
		perror("(fatal) select"), exit(-1);

	for (int i = 0; i < FD_SETSIZE; ++i)
		if (FD_ISSET (i, &read_fd))
		{
			if (i == sock)
			{
				size = sizeof(clientname);
				if ((new_sock = accept(sock, (struct sockaddr *)&clientname, &size)) < 0)
					perror ("accept"), exit(-1);
				printf("accepted connection: %i\n", new_sock);
				get_all_open_sockets(new_sock);
				FD_SET(new_sock, active_fd);
			}
			else
			{
				//	la on pourrai faire un read sur le fd i pout lire c qu'a a dire le client
				//	ou une autre fonction pour avoir des info en plus
			}
		}
}
