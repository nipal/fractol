/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reseau.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 04:10:48 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/29 04:20:25 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



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


#include "fractol.h"

//	a load tout seul avec juste les bon parametre
int         create_client(char *addr, int port)
{
	int                 sock;
	struct protoent     *proto;
	struct sockaddr_in  sin;

	if (port == 0)
		return (-1);
	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (!strcmp(addr, "localhost"))
		sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		error("Connection error !\n");
	return (sock);
}

// a load tout seul avec les bon parametre -->
// le mieux c'est de cree un serveur quand on a une connexion entrante
static int          create_server(int port)
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

// stac d'initilisation qui recupere les ctr+c pour fermer tout les client
int             main(int ac, char **av)
{
	int                 port;
	int                 sock;
	fd_set              read_fd;

	if (ac == 2)
	{
		signal(SIGINT, close_sockets);
		port = atoi(av[1]);
		sock = create_server(port);
		get_server_socket(sock);
		FD_ZERO(&read_fd);
		FD_SET(sock, &read_fd);
		//      FD_SET(0, &read_fd);
		while (42)
			wait_for_event(sock, &read_fd);
	}
	else
		usage(*av);
	return (0);
}


// (cote serveur) pour lire ce que les client envoie mais il faut avoir un parametre de timeout pour etre non bloquant
// c'est pareille cote client mais il faut juste pas le if au dessu du else
static void     wait_for_event(int sock, fd_set *active_fd)
{
	struct          sockaddr_in clientname;
	socklen_t       size;
	fd_set          read_fd;
	int             new_sock;

	read_fd = *active_fd;
	if (select(FD_SETSIZE, &read_fd, NULL, NULL, NULL) < 0)
		perror("(fatal) select"), exit(-1);

	for (int i = 0; i < FD_SETSIZE; ++i)
		if (FD_ISSET (i, &read_fd))
		{
			// uniquement pour le serveur (le if)
			if (i == sock)
			{
				size = sizeof(clientname);
				if ((new_sock = accept(sock, (struct sockaddr *)&clientname, &size)) < 0)
					perror ("accept"), exit(-1);
				printf("accepted connection: %i\n", new_sock);
				add_new_client(new_sock);// foncirton a recoder pour stoquer les socket (comme un fd) et pour apres fermer toutes les connexion d;uncoup
				FD_SET(new_sock, active_fd);
			}
			else // ca c'est aussi pour le client
			{
				if (read_from_client(i) < 0)
				{
					printf("%s closed !\n", get_client_info(i)->name);
					close (i);
					send_disconnected_client(i);
					remove_client(i);
					FD_CLR(i, active_fd);
				}
			}
		}
}

static void     close_sockets(int s)
{
	int     ss;
	int     *socks;

	(void)s;
	if ((ss = get_server_socket(0)))
		close(ss);
	socks = get_all_open_sockets();
	for (int i = 0; socks[i]; i++)
		close(socks[0]);
}

//	sockaddr_in pour adresse ip client
//	struct timeval parametrer  le timeout select (dernier param)
